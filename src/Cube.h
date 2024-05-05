#pragma once

#include "Buffer.h"
#include "ConstantBuffer.h"
#include "Graphics.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "structs.h"

class Cube
{
    ID3D11Device *pDevice;
    ID3D11DeviceContext *pCtx;
#ifndef NDEBUG
    GfxDebug &debug;
#endif

    std::vector<std::unique_ptr<Buffer>> buffers;
    std::vector<std::unique_ptr<Shader>> shaders;

    static constexpr Vec4 vertices[8] = {
        {-1, 1, -1, 1}, {1, 1, -1, 1}, {1, -1, -1, 1}, {-1, -1, -1, 1},
        {-1, 1, 1, 1},  {1, 1, 1, 1},  {1, -1, 1, 1},  {-1, -1, 1, 1},
    };

    static constexpr unsigned indices[36] = {5, 4, 7, 7, 6, 5, 4, 5, 1, 1, 0, 4, 1, 5, 6, 6, 2, 1,
                                             4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 0, 1, 2, 2, 3, 0};

    IndexBuffer ib;
    VertexBuffer vb;
    VertexShader vs;
    PixelShader ps;

    ID3D11Buffer *vertex_buffers[1] = {vb.GetDxBuffer()};
    ID3D11Buffer *ps_c_buffers[1] = {psColors.GetDxBuffer()};
    ID3D11Buffer *vs_c_buffers[1] = {vsTransform.GetDxBuffer()};

    ConstantBuffer<D3D11_USAGE_DYNAMIC> vsTransform;
    ConstantBuffer<D3D11_USAGE_DEFAULT> psColors;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

  public:
    Cube(Graphics &gfx);

    void Draw();
};
