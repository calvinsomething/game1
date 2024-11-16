#pragma once

#include "pch.h"

class RNG
{
    std::mt19937 engine;

    std::unordered_map<uint64_t, std::uniform_real_distribution<float>> r_distributions;
    std::unordered_map<uint64_t, std::uniform_int_distribution<int>> i_distributions;

    std::uniform_real_distribution<float> *r_loaded;
    std::uniform_int_distribution<int> *i_loaded;

    RNG() : engine(std::random_device{}())
    {
    }

    template <typename T> uint64_t make_key(T a, T b)
    {
        static_assert(sizeof(T) == 4, "RNG::make_key requires a 4-byte type.");
        struct
        {
            T x;
            T y;
        } bits;
        bits.x = a;
        bits.y = b;
        return *(reinterpret_cast<uint64_t *>(&bits));
    }

  public:
    RNG(const RNG &) = delete;
    RNG operator=(const RNG &) = delete;

    static RNG &Get();

    void Load(float min, float max);
    void Load(int min, int max);

    float operator()(float min, float max);
    int operator()(int min, int max);

    float GetNextFloat();
    int GetNextInt();
};

template <typename T> bool abs_compare(T a, T b)
{
    const T diff = a - b;
    const T sum = a + b;
    return (diff > 0 && sum > 0) || (diff < 0 && sum < 0);
}
