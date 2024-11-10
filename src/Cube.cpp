#include "Cube.h"

#include "IndexBuffer.h"
#include "PixelShader.h"
#include "SamplerState.h"
#include "Texture.h"
#include "VertexBuffer.h"

using namespace Microsoft::WRL;
using namespace DirectX;

bool Cube::initialized = false;

VertexShader *Cube::vs;
std::vector<std::unique_ptr<Bindable>> Cube::bindables;

Cube::Vertex Cube::vertices[] = {{{1, 1, 1}, {}, TC(0, 1)},   {{-1, 1, 1}, {}, TC(1, 1)},  {{-1, 1, -1}, {}, TC(2, 1)},
                                 {{-1, 1, 1}, {}, TC(2, 0)},  {{1, 1, 1}, {}, TC(3, 0)},   {{1, 1, -1}, {}, TC(3, 1)},
                                 {{1, 1, 1}, {}, TC(4, 1)},   {{1, -1, 1}, {}, TC(4, 2)},  {{1, -1, -1}, {}, TC(3, 2)},
                                 {{1, -1, 1}, {}, TC(3, 3)},  {{-1, -1, 1}, {}, TC(2, 3)}, {{-1, -1, -1}, {}, TC(2, 2)},
                                 {{-1, -1, 1}, {}, TC(1, 2)}, {{1, -1, 1}, {}, TC(0, 2)}};

Cube::Cube(float radius, std::array<float, 6> deltas) : Box(radius, deltas)
{
    Box::transform = &transform;
    if (!initialized)
    {
        // set normals
        for (auto &v : vertices)
        {
            auto p = DirectX::XMLoadFloat3(&v.Position);
            DirectX::XMStoreFloat3(&v.Normal, DirectX::XMVector3Normalize(p));
        }

        bindables.reserve(6);
        bindables.push_back(std::make_unique<VertexBuffer<Vertex>>(vertices, sizeof(vertices)));
        bindables.push_back(std::make_unique<IndexBuffer>(indices, sizeof(indices)));

        // VS
        bindables.push_back(std::make_unique<VertexShader>(
            L"shaders/v_texture.cso", std::vector<ConstantBuffer>{sizeof(transform), sizeof(DirectX::XMMATRIX)}));
        Cube::vs = dynamic_cast<VertexShader *>(bindables[2].get());

        vs->SetInputLayout({{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                            {"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
                             D3D11_INPUT_PER_VERTEX_DATA, 0},
                            {"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
                             D3D11_INPUT_PER_VERTEX_DATA, 0}});

        // PS
        bindables.push_back(std::make_unique<PixelShader>(L"shaders/p_texture.cso"));

        bindables.push_back(std::make_unique<Texture>(L"assets/textures/di.png"));
        bindables.push_back(std::make_unique<SamplerState>());

        initialized = true;
    }
}

void Cube::Update(float dtime)
{
    assert(initialized && "Draw called on uninitialized Cube.");

    move(dtime);

    vs->constant_buffers[0].Update(transform);
    vs->constant_buffers[1].Update(get_mat_vp());
}

void Cube::Draw()
{
    for (auto &b : bindables)
    {
        b->Bind();
    }

    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    CHECK_ERRORS();

    pCtx->DrawIndexed(std::size(indices), 0, 0);
    CHECK_ERRORS();
}
