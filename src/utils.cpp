#include "utils.h"

RNG &RNG::Get()
{
    static RNG self;
    return self;
}

void RNG::Load(float min, float max)
{
    auto it = r_distributions.find(make_key(min, max));
    if (it == r_distributions.end())
    {
        auto result = r_distributions.emplace(make_key(min, max), std::uniform_real_distribution<float>(min, max));
        r_loaded = &result.first->second;
    }
    else
    {
        r_loaded = &it->second;
    }
}

void RNG::Load(int min, int max)
{
    auto it = i_distributions.find(make_key(min, max));
    if (it == i_distributions.end())
    {
        auto result = i_distributions.emplace(make_key(min, max), std::uniform_int_distribution<int>(min, max));
        i_loaded = &result.first->second;
    }
    else
    {
        i_loaded = &it->second;
    }
}

float RNG::operator()(float min, float max)
{
    Load(min, max);
    return (*r_loaded)(engine);
}

int RNG::operator()(int min, int max)
{
    Load(min, max);
    return (*i_loaded)(engine);
}

float RNG::GetNextFloat()
{
    return (*r_loaded)(engine);
}

int RNG::GetNextInt()
{
    return (*i_loaded)(engine);
}
