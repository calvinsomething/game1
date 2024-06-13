#include "utils.h"

const RFG& RFG::Get()
{
	static RFG self;
	return self;
}

long long RFG::make_key(float a, float b)
{
    long long key = 0;
    key |= *(reinterpret_cast<int*>(&a));
    key <<= 32;
    key |= *(reinterpret_cast<int*>(&b));
    return key;
}

void RFG::Load(float min, float max)
{
    auto result = distributions.emplace(make_key(min, max), std::uniform_real_distribution<T>(min, max));
    loaded = result.first;
}

float RFG::operator()(float min, float max)
{
    auto d = distributions.find({min, max});
    if (d == distributions.end())
    {
        Load(min, max);
        d = static_cast<std::uniform_real_distribution<float>*>(loaded);
    }

    return (*d)(engine);
}

float RFG::RunLoaded()
{
    assert(loaded && "RFG::RunLoaded called with no loaded distribution");
    return (*loaded)(engine);
}
