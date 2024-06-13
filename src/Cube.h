#pragma once

#include "Buffer.h"
#include "Shader.h"

class Cube : protected GfxAccess
{
    static bool initialized;

    static std::vector<std::unique_ptr<Buffer>> buffers;
    static std::vector<std::unique_ptr<Shader>> shaders;

    static constexpr DirectX::XMVECTOR vertices[8] = {
        {-1, 1, -1, 1}, {1, 1, -1, 1}, {1, -1, -1, 1}, {-1, -1, -1, 1},
        {-1, 1, 1, 1},  {1, 1, 1, 1},  {1, -1, 1, 1},  {-1, -1, 1, 1},
    };

    static constexpr unsigned indices[36] = {5, 4, 7, 7, 6, 5, 4, 5, 1, 1, 0, 4, 1, 5, 6, 6, 2, 1,
                                             4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 0, 1, 2, 2, 3, 0};

    static constexpr DirectX::XMVECTOR face_colors[] = {
        {1, 0, 0, 1}, {1, 1, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 1, 1},
    };

    DirectX::XMMATRIX transform;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

	float radius;
	float roll, pitch, yaw;
	float theta, phi, chi;
	
	std::array<float, 6> deltas;

  public:
    Cube(float radius, std::array<float, 6> deltas);

    void Draw();
};
