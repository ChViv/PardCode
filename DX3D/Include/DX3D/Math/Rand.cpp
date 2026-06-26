#include <DX3D/Math/Rand.h>

using namespace dx3d;

std::mt19937 Rand::s_rng(std::random_device{}());

float Rand::range(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(s_rng);
}

int Rand::range(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(s_rng);
}