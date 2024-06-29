#pragma once

#include "VertexShader.h"

#define TC(c1, c2)                                                                                                     \
    {                                                                                                                  \
        c1##.0f * 0.25f, c2##.0f * 0.333333f                                                                           \
    }

struct Vertex
{
    DirectX::XMVECTOR Position;
    DirectX::XMFLOAT2 TexCoord;
};

class Cube : protected GfxAccess
{
    static bool initialized;

    static std::vector<std::unique_ptr<Bindable>> bindables;
    static VertexShader *vs;

    static constexpr Vertex vertices[] = {
        {{1, 1, 1, 1}, TC(0, 1)},   {{-1, 1, 1, 1}, TC(1, 1)}, {{-1, 1, -1, 1}, TC(2, 1)}, {{-1, 1, 1, 1}, TC(2, 0)},
        {{1, 1, 1, 1}, TC(3, 0)},   {{1, 1, -1, 1}, TC(3, 1)}, {{1, 1, 1, 1}, TC(4, 1)},   {{1, -1, 1, 1}, TC(4, 2)},
        {{1, -1, -1, 1}, TC(3, 2)}, {{1, -1, 1, 1}, TC(3, 3)}, {{-1, -1, 1, 1}, TC(2, 3)}, {{-1, -1, -1, 1}, TC(2, 2)},
        {{-1, -1, 1, 1}, TC(1, 2)}, {{1, -1, 1, 1}, TC(0, 2)}};

    static constexpr unsigned indices[] = {0, 1, 12, 12, 13, 0, 1, 2, 11, 11, 12, 1, 2,  3, 4, 4, 5,  2,
                                           5, 6, 7,  7,  8,  5, 2, 5, 8,  8,  11, 2, 11, 8, 9, 9, 10, 11};

    static constexpr DirectX::XMVECTOR face_colors[] = {
        {1, 0, 0, 1}, {1, 1, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 1, 1},
    };

    DirectX::XMMATRIX transform;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

    float radius;
    float yaw, pitch, roll;
    float psi, theta, phi;

    std::array<float, 6> deltas;

  public:
    Cube(float radius, std::array<float, 6> deltas);

    void Draw();
    void Update(float dtime);
};
