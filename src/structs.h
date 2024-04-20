#pragma once

struct Color
{
    float red;
    float green;
    float blue;
    float alpha;
};

struct Vertex
{
    struct
    {
        float x;
        float y;
        float z;
        float w;
    } pos;
    struct
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } color;
};
