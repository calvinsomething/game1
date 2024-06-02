#include "Cube.h"

#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

using namespace Microsoft::WRL;
using namespace DirectX;

bool Cube::initialized = false;

std::vector<std::unique_ptr<Buffer>> Cube::buffers;
std::vector<std::unique_ptr<Shader>> Cube::shaders;

Cube::Cube()
{
    if (!initialized)
    {
        buffers.reserve(2);
        buffers.push_back(std::make_unique<VertexBuffer<XMVECTOR>>(vertices, sizeof(vertices)));
        buffers.push_back(std::make_unique<IndexBuffer>(indices, sizeof(indices)));

        shaders.reserve(2);

        // VS
        shaders.push_back(
            std::make_unique<VertexShader>(L"shaders/vertex.cso", std::vector<ConstantBuffer>{sizeof(transform)}));
        shaders[0]->SetInputLayout(
            {{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}});

        // PS
        shaders.push_back(
            std::make_unique<PixelShader>(L"shaders/pixel.cso", std::vector<ConstantBuffer>{{face_colors}}));

        initialized = true;
    }
}

void Cube::Draw()
{
    assert(initialized && "Draw called on uninitialized Cube.");

    transform = XMMatrixMultiplyTranspose(XMMatrixRotationX(0.9) * XMMatrixRotationY(0.5),
                                          XMMatrixTranslation(0, 0, 7) * XMMatrixPerspectiveLH(1, 0.75, 1, 10));

    shaders[0]->constant_buffers[0].Update(transform);

    for (auto &s : shaders)
    {
        s->Bind();
    }
    for (auto &b : buffers)
    {
        b->Bind();
    }

    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    CHECK_ERRORS();

    pCtx->DrawIndexed(std::size(indices), 0, 0);
    CHECK_ERRORS();
}
