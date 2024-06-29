#include "Cube.h"

#include "IndexBuffer.h"
#include "PixelShader.h"
#include "SamplerState.h"
#include "Texture.h"
#include "VertexBuffer.h"

using namespace Microsoft::WRL;
using namespace DirectX;

bool Cube::initialized = false;

std::vector<std::unique_ptr<Bindable>> Cube::bindables;
VertexShader *Cube::vs;

Cube::Cube(float radius, decltype(deltas) deltas)
    : radius(radius), deltas(deltas), yaw(), pitch(), roll(), psi(), theta(), phi()
{
    if (!initialized)
    {
        bindables.reserve(6);
        bindables.push_back(std::make_unique<VertexBuffer<Vertex>>(vertices, sizeof(vertices)));
        bindables.push_back(std::make_unique<IndexBuffer>(indices, sizeof(indices)));

        // VS
        bindables.push_back(
            std::make_unique<VertexShader>(L"shaders/v_texture.cso", std::vector<ConstantBuffer>{sizeof(transform)}));
        Cube::vs = dynamic_cast<VertexShader *>(bindables[2].get());

        vs->SetInputLayout({{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                            {"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
                             D3D11_INPUT_PER_VERTEX_DATA, 0}});

        // PS
        bindables.push_back(std::make_unique<PixelShader>(L"shaders/p_texture.cso"));
        // std::make_unique<PixelShader>(L"shaders/p_texture.cso", std::vector<ConstantBuffer>{{face_colors}}));

        bindables.push_back(std::make_unique<Texture>(L"assets/textures/di.png"));
        bindables.push_back(std::make_unique<SamplerState>());

        initialized = true;
    }
}

void Cube::Update(float dtime)
{
    assert(initialized && "Draw called on uninitialized Cube.");

    yaw += dtime * deltas[0];
    pitch += dtime * deltas[1];
    roll += dtime * deltas[2];
    psi += dtime * deltas[3];
    theta += dtime * deltas[4];
    phi += dtime * deltas[5];

    transform = ToNDCSpace(XMMatrixRotationRollPitchYaw(yaw, pitch, roll) * XMMatrixTranslation(radius, 0.0f, 0.0f) *
                           XMMatrixRotationRollPitchYaw(psi, theta, phi));

    vs->constant_buffers[0].Update(transform);
}

void Cube::Draw()
{
    assert(initialized && "Draw called on uninitialized Cube.");

    for (auto &b : bindables)
    {
        b->Bind();
    }

    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    CHECK_ERRORS();

    pCtx->DrawIndexed(std::size(indices), 0, 0);
    CHECK_ERRORS();
}
