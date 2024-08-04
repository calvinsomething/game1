#pragma once

#include "Box.h"

#include "VertexShader.h"

#define TC(c1, c2)                                                                                                     \
    {                                                                                                                  \
        c1##.0f * 0.25f, c2##.0f * 0.333333f                                                                           \
    }

class Cube : public Box
{
    struct Vertex
    {
        DirectX::XMVECTOR Position;
        DirectX::XMFLOAT2 TexCoord;
    };

    static std::vector<std::unique_ptr<Bindable>> bindables;
    static VertexShader *vs;

    static bool initialized;

    static constexpr Vertex vertices[] = {
        {{1, 1, 1, 1}, TC(0, 1)},   {{-1, 1, 1, 1}, TC(1, 1)}, {{-1, 1, -1, 1}, TC(2, 1)}, {{-1, 1, 1, 1}, TC(2, 0)},
        {{1, 1, 1, 1}, TC(3, 0)},   {{1, 1, -1, 1}, TC(3, 1)}, {{1, 1, 1, 1}, TC(4, 1)},   {{1, -1, 1, 1}, TC(4, 2)},
        {{1, -1, -1, 1}, TC(3, 2)}, {{1, -1, 1, 1}, TC(3, 3)}, {{-1, -1, 1, 1}, TC(2, 3)}, {{-1, -1, -1, 1}, TC(2, 2)},
        {{-1, -1, 1, 1}, TC(1, 2)}, {{1, -1, 1, 1}, TC(0, 2)}};

    static constexpr unsigned indices[] = {0, 1, 12, 12, 13, 0, 1, 2, 11, 11, 12, 1, 2,  3, 4, 4, 5,  2,
                                           5, 6, 7,  7,  8,  5, 2, 5, 8,  8,  11, 2, 11, 8, 9, 9, 10, 11};

  public:
    Cube(float radius, std::array<float, 6> deltas);

    void Update(float dtime) override;
    void Draw() override;
};
