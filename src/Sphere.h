#pragma once

#include "Box.h"

#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "pch.h"

template <unsigned latitude_divisions> class Sphere : public Box
{
    static bool initialized;

    static std::vector<std::unique_ptr<Bindable>> bindables;
    static VertexShader *vs;

    static std::vector<Vertex> vertices;
    static std::vector<unsigned> indices;

    static constexpr DirectX::XMVECTOR face_colors[6] = {
        {1, 0, 0, 1}, {1, 1, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 1, 1},
    };

    void set_vertices()
    {
        using namespace DirectX;

        float radius = 1;

        unsigned latitude_lines = latitude_divisions + 1, longitude_divisions = latitude_divisions * 2;

        float z_radians = XM_PI / latitude_lines;
        XMMATRIX rotation_z = XMMatrixRotationZ(z_radians);
        XMMATRIX half_rotation_z = XMMatrixRotationZ(z_radians / 2);
        XMMATRIX rotation_y = XMMatrixRotationY(-XM_PI / latitude_divisions);

        vertices.emplace_back();
        XMStoreFloat3(&vertices.back().Position, XMVector4Transform({0, radius, 0, 1}, half_rotation_z));
        for (int i = 0; i < latitude_divisions; i++)
        {
            auto p = XMLoadFloat3(&vertices[i].Position);
            p = XMVector4Transform(p, rotation_z);

            vertices.emplace_back();

            XMStoreFloat3(&vertices.back().Position, p);
            XMStoreFloat3(&vertices.back().Normal, XMVector3Normalize(p));
        }

        unsigned vertices_to_rotate = (longitude_divisions - 1) * latitude_lines;
        for (int i = 0; i < vertices_to_rotate; i++)
        {
            auto p = XMLoadFloat3(&vertices[i].Position);
            p = XMVector4Transform(p, rotation_y);

            vertices.emplace_back();

            XMStoreFloat3(&vertices.back().Position, p);
            XMStoreFloat3(&vertices.back().Normal, XMVector3Normalize(p));
        }

        indices.reserve(latitude_divisions * (longitude_divisions + 1) * 6);

        for (int i = 0; i < vertices.size();)
        {
            int next_column = (i + latitude_lines) % vertices.size();

            indices.push_back(i + 1);
            indices.push_back(i);
            indices.push_back(next_column);

            indices.push_back(next_column);
            indices.push_back(next_column + 1);
            indices.push_back(++i);

            i += !((i + 1) % latitude_lines);
        }

        int top_pole = vertices.size();
        vertices.push_back(Vertex{{0, vertices[0].Position.y, 0}, {0, 1, 0}});

        int bottom_pole = top_pole + 1;
        vertices.push_back(Vertex{{0, -vertices[0].Position.y, 0}, {0, -1, 0}});

        for (int i = 0; i < longitude_divisions; i++)
        {
            int top = i * latitude_lines, next_column = (top + latitude_lines) % top_pole;

            indices.push_back(top);
            indices.push_back(top_pole);
            indices.push_back(next_column);

            indices.push_back(bottom_pole);
            indices.push_back(top + latitude_divisions);
            indices.push_back(next_column + latitude_divisions);
        }
    }

  public:
    Sphere(float radius, std::array<float, 6> deltas) : Box(radius, deltas)
    {
        if (!initialized)
        {
            set_vertices();

            bindables.reserve(4);
            bindables.push_back(
                std::make_unique<VertexBuffer<Vertex>>(vertices.data(), vertices.size() * sizeof(vertices[0])));
            bindables.push_back(std::make_unique<IndexBuffer>(indices.data(), indices.size() * sizeof(indices[0])));

            // VS
            bindables.push_back(std::make_unique<VertexShader>(
                L"shaders/vertex.cso", std::vector<ConstantBuffer>{sizeof(transform), sizeof(DirectX::XMMATRIX)}));
            Sphere::vs = dynamic_cast<VertexShader *>(bindables[2].get());

            vs->SetInputLayout({{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
                                 D3D11_INPUT_PER_VERTEX_DATA, 0}});

            // PS
            bindables.push_back(
                std::make_unique<PixelShader>(L"shaders/pixel.cso", std::vector<ConstantBuffer>({face_colors})));

            initialized = true;
        }
    }

    void Update(float dtime) override
    {
        assert(initialized && "Draw called on uninitialized Sphere.");

        move(dtime);

        vs->constant_buffers[0].Update(transform);
        vs->constant_buffers[1].Update(get_mat_vp());
    }

    void Draw() override
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
};

template <unsigned latitude_divisions> bool Sphere<latitude_divisions>::initialized;
template <unsigned latitude_divisions> std::vector<std::unique_ptr<Bindable>> Sphere<latitude_divisions>::bindables;
template <unsigned latitude_divisions> VertexShader *Sphere<latitude_divisions>::vs;

template <unsigned latitude_divisions> std::vector<Vertex> Sphere<latitude_divisions>::vertices;
template <unsigned latitude_divisions> std::vector<unsigned> Sphere<latitude_divisions>::indices;
