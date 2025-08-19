#ifdef TWIZ_GPU_RUNTIME_CUDA
#include "Examples/gpu.h"
#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>
#include <tuple>

#define CUDA_ASSERT(x)                                                                                                                                                                                 \
    do                                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
        cudaError_t result = (x);                                                                                                                                                                      \
        if (result != cudaSuccess)                                                                                                                                                                     \
        {                                                                                                                                                                                              \
            printf("CUDA Error: %s at %s:%d\n", cudaGetErrorString(result), __FILE__, __LINE__);                                                                                                       \
            exit(1);                                                                                                                                                                                   \
        }                                                                                                                                                                                              \
    } while (0)

namespace Twiz
{
    __global__ void vecAdd(const float* pa, const float* pb, float* pc, int size)
    {
        int i = (blockIdx.x * blockDim.x) + threadIdx.x;
        if (i < size)
        {
            pc[i] = pa[i] + pb[i];
        }
    }

    void VectorAdd(const float* pda, const float* pdb, float* pdc, int n)
    {
        float *da = nullptr, *db = nullptr, *dc = nullptr;
        CUDA_ASSERT(cudaMalloc(&da, n * sizeof(float)));
        CUDA_ASSERT(cudaMalloc(&db, n * sizeof(float)));
        CUDA_ASSERT(cudaMalloc(&dc, n * sizeof(float)));

        CUDA_ASSERT(cudaMemcpy(da, pda, n * sizeof(float), cudaMemcpyHostToDevice));
        CUDA_ASSERT(cudaMemcpy(db, pdb, n * sizeof(float), cudaMemcpyHostToDevice));

        int blockSize = 256;
        int gridSize = (n + blockSize - 1) / blockSize;
        vecAdd<<<gridSize, blockSize>>>(da, db, dc, n);
        CUDA_ASSERT(cudaDeviceSynchronize());

        CUDA_ASSERT(cudaMemcpy(pdc, dc, n * sizeof(float), cudaMemcpyDeviceToHost));

        CUDA_ASSERT(cudaFree(da));
        CUDA_ASSERT(cudaFree(db));
        CUDA_ASSERT(cudaFree(dc));
    }

    std::tuple<float*, float*, float*> Generate(int size)
    {
        float* a = new float[size];
        float* b = new float[size];
        float* c = new float[size];

        for (int i = 0; i < size; ++i)
        {
            a[i] = static_cast<float>(i);
            b[i] = static_cast<float>(2 * i);
            c[i] = 0.0f;
        }

        return std::make_tuple(a, b, c);
    }

    void Cleanup(float* pa, float* pb, float* pc)
    {
        delete[] pa;
        delete[] pb;
        delete[] pc;
    }
} // namespace Twiz
#endif // _GPU_RUNTIME_CUDA
