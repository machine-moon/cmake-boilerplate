#ifdef TWIZ_GPU_RUNTIME_HIP
#include "Examples/gpu.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <tuple>
#include <hip/hip_runtime_api.h>
#include <stdio.h>
#include <stdlib.h>

#define HIP_ASSERT(c) {                               \
   if (c != hipSuccess){                              \
      printf("HIP Error : %s", hipGetErrorString(c)); \
      printf(" %s %d\n", __FILE__, __LINE__);         \
      exit(c);                                        \
   }                                                  \
}


namespace Twiz
{
    __global__ void vecAdd(const float* pa, const float* pb, float* pc, int size)
    {
        int i = (blockIdx.x * blockDim.x) + threadIdx.x;
        if (i < size)
        {
            pc[i] = pa[i] * pb[i];
        }
    }

    void VectorAdd(const float* pda, const float* pdb, float* pdc, int n)
    {
        float *da = nullptr, *db = nullptr, *dc = nullptr;
        HIP_ASSERT(hipMalloc(&da, n * sizeof(float)));
        HIP_ASSERT(hipMalloc(&db, n * sizeof(float)));
        HIP_ASSERT(hipMalloc(&dc, n * sizeof(float)));

        HIP_ASSERT(hipMemcpy(da, pda, n * sizeof(float), hipMemcpyHostToDevice));
        HIP_ASSERT(hipMemcpy(db, pdb, n * sizeof(float), hipMemcpyHostToDevice));

        int blockSize = 256;
        int gridSize = (n + blockSize - 1) / blockSize;
        vecAdd<<<gridSize, blockSize>>>(da, db, dc, n);
        HIP_ASSERT(hipDeviceSynchronize());

        HIP_ASSERT(hipMemcpy(pdc, dc, n * sizeof(float), hipMemcpyDeviceToHost));

        HIP_ASSERT(hipFree(da));
        HIP_ASSERT(hipFree(db));
        HIP_ASSERT(hipFree(dc));
    }

    std::tuple<float*, float*, float*> Generate(int size)
    {
        float* a = new float[size];
        float* b = new float[size];
        float* c = new float[size];

        for (int i = 0; i < size; ++i)
        {
            a[i] = static_cast<float>(i);
            b[i] = static_cast<float>(3 * i);
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
#endif // TWIZ_GPU_RUNTIME_HIP