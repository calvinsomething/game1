#pragma once

#include "pch.h"

template <typename T> struct Color
{
    T r;
    T g;
    T b;
    T a;
};

struct Vertex
{
    DirectX::XMVECTOR Position;
    DirectX::XMVECTOR Normal;
};

template <unsigned N, unsigned M> struct Matrix
{
    float elements[N][M];
};

struct MouseInput
{
    struct
    {
        short x;
        short y;
    } Position;
    struct
    {
        short x;
        short y;
    } Delta;

    bool LeftButtonDown;
};
