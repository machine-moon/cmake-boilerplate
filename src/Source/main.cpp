#include "Constants.h"
#include "Examples/gpu.h"
#include <iostream>

int main()
{
    std::cout << "appversion: " << Constants::appVersion << '\n';

    constexpr int n = 100;

    for (int i = 1; i <= 1; i++)
    {
        int size = n * i;

        float *a = nullptr, *b = nullptr, *c = nullptr;
        std::tie(a, b, c) = Twiz::Generate(size);

        Twiz::VectorAdd(a, b, c, size);

        for (int j = 0; j < size; ++j)
        {
            std::cout << a[j] << " " << b[j] << " " << c[j] << '\n';
        }

        Twiz::Cleanup(a, b, c);
    }
    return 0;
}
