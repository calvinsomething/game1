#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() : initialized(false)
{
}

IndexBuffer::IndexBuffer(const unsigned *indices, size_t byte_width) : initialized(false)
{
    Init(indices, byte_width);
}

void IndexBuffer::Init(const unsigned *indices, size_t byte_width)
{
    assert(!initialized);
    initialized = true;

    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.StructureByteStride = sizeof(indices[0]);

    D3D11_SUBRESOURCE_DATA sd{};
    sd.pSysMem = indices;

    GFX_DEBUG(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
}

void IndexBuffer::Bind()
{
    assert(initialized && "attempt to bind uninitialized IndexBuffer");
    pCtx->IASetIndexBuffer(pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
