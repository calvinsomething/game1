#pragma once

template <typename T> struct Color
{
    T r;
    T g;
    T b;
    T a;
};

struct Vec4
{
    float x;
    float y;
    float z;
    float w;
};

template <unsigned N, unsigned M> struct Matrix
{
    float elements[N][M];
};
