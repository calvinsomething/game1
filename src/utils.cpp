#include "utils.h"

RFG &RFG::Get()
{
    static RFG self;
    return self;
}

long long RFG::make_key(float a, float b)
{
    struct
    {
        float x;
        float y;
    } bits;
    bits.x = a;
    bits.y = b;
    return *(reinterpret_cast<long long *>(&bits));
}

void RFG::Load(float min, float max)
{
    auto it = distributions.find(make_key(min, max));
    if (it == distributions.end())
    {
        auto result = distributions.emplace(make_key(min, max), std::uniform_real_distribution<float>(min, max));
        loaded = &result.first->second;
    }
    else
    {
        loaded = &it->second;
    }
}

float RFG::operator()(float min, float max)
{
    Load(min, max);
    return (*loaded)(engine);
}

float RFG::RunLoaded()
{
    return (*loaded)(engine);
}
