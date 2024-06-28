#pragma once

#include "Buffer.h"

class VertexBufferBase : public Buffer
{
    friend class VertexBuffers;

  protected:
    VertexBufferBase(size_t stride);

    unsigned stride;
    unsigned offset;

  public:
    void Bind() override;
};

template <typename T> class VertexBuffer : public VertexBufferBase
{
  public:
    VertexBuffer(const T *vertices, size_t byte_width) : VertexBufferBase(sizeof(T))
    {
        D3D11_BUFFER_DESC bd{};
        bd.ByteWidth = byte_width;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.StructureByteStride = sizeof(T);

        D3D11_SUBRESOURCE_DATA sd{};
        sd.pSysMem = vertices;

        GFX_DEBUG(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
    }
};

class VertexBuffers : public Bindable
{
    bool initialized;

    std::vector<ID3D11Buffer *> vertex_buffers;
    std::vector<unsigned> strides, offsets;

  public:
    VertexBuffers() = default;
    VertexBuffers(std::initializer_list<VertexBufferBase *> vertex_buffers);

    void Set(std::initializer_list<VertexBufferBase *> input);

    void Bind() override;
};
