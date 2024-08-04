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

    static std::vector<DirectX::XMVECTOR> vertices;
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
        XMMATRIX rotation_y = XMMatrixRotationY(XM_PI / latitude_divisions);

        vertices.push_back(XMVector4Transform(XMVECTOR{0, radius, 0, 1}, half_rotation_z));
        for (int i = 0; i < latitude_divisions; i++)
        {
            vertices.push_back(XMVector4Transform(vertices[i], rotation_z));
        }

        unsigned vertices_to_rotate = (longitude_divisions - 1) * latitude_lines;
        for (int i = 0; i < vertices_to_rotate; i++)
        {
            vertices.push_back(XMVector4Transform(vertices[i], rotation_y));
        }

        indices.reserve(latitude_divisions * (longitude_divisions + 1) * 6);

        for (int i = 0; i < vertices.size();)
        {
            int next_row = (i + latitude_lines) % vertices.size();

            indices.push_back(i + 1);
            indices.push_back(i);
            indices.push_back(next_row);

            indices.push_back(next_row);
            indices.push_back(next_row + 1);
            indices.push_back(++i);

            i += !((i + 1) % latitude_lines);
        }

        int top_pole = vertices.size();
        vertices.push_back(XMVECTOR{0, XMVectorGetY(vertices[0]), 0, 1});

        int bottom_pole = top_pole + 1;
        vertices.push_back(XMVECTOR{0, -XMVectorGetY(vertices[0]), 0, 1});

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
            bindables.push_back(std::make_unique<VertexBuffer<DirectX::XMVECTOR>>(
                vertices.data(), vertices.size() * sizeof(vertices[0])));
            bindables.push_back(std::make_unique<IndexBuffer>(indices.data(), indices.size() * sizeof(indices[0])));

            // VS
            bindables.push_back(
                std::make_unique<VertexShader>(L"shaders/vertex.cso", std::vector<ConstantBuffer>{sizeof(transform)}));
            Sphere::vs = dynamic_cast<VertexShader *>(bindables[2].get());

            vs->SetInputLayout({{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}});

            // PS
            bindables.push_back(
                std::make_unique<PixelShader>(L"shaders/pixel.cso", std::vector<ConstantBuffer>({face_colors})));

            initialized = true;
        }
    }

    void Update(float dtime)
    {
        assert(initialized && "Draw called on uninitialized Sphere.");

        move(dtime);

        vs->constant_buffers[0].Update(transform);
    }

    void Draw()
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

template <unsigned latitude_divisions> std::vector<DirectX::XMVECTOR> Sphere<latitude_divisions>::vertices;
template <unsigned latitude_divisions> std::vector<unsigned> Sphere<latitude_divisions>::indices;
