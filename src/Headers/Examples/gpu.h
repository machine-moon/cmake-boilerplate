#pragma once
#include <tuple>

namespace Twiz
{
    std::tuple<float*, float*, float*> Generate(int size);
    void VectorAdd(const float* pda, const float* pdb, float* pdc, int n);
    void Cleanup(float* pa, float* pb, float* pc);
} // namespace Twiz