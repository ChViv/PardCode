#pragma once

#include <random>

namespace dx3d
{
    class Rand
    {
    public:
        static float range(float min, float max);
        static int range(int min, int max);

    private:
        static std::mt19937 s_rng;
    };
}

