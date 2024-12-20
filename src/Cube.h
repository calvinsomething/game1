#pragma once

#include "Box.h"

#include "VertexShader.h"

class Cube : public Box
{
    struct Vertex
    {
        DirectX::XMFLOAT3 Position;
        DirectX::XMFLOAT3 Normal;
        DirectX::XMFLOAT2 TexCoord;
    };

    DirectX::XMMATRIX transform;

    static std::vector<std::unique_ptr<Bindable>> bindables;
    static VertexShader *vs;

    static bool initialized;

    static Vertex vertices[];

    static constexpr unsigned indices[] = {0, 1, 12, 12, 13, 0, 1, 2, 11, 11, 12, 1, 2,  3, 4, 4, 5,  2,
                                           5, 6, 7,  7,  8,  5, 2, 5, 8,  8,  11, 2, 11, 8, 9, 9, 10, 11};

  public:
    Cube(float radius, std::array<float, 6> deltas);

    void Update(float dtime) override;
    void Draw() override;
};
