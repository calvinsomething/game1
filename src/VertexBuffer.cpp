#include "VertexBuffer.h"

using namespace Microsoft::WRL;

VertexBuffer::VertexBuffer(Graphics &gfx, const Vec4 *vertices, unsigned byte_width) : Buffer(gfx)
{
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.StructureByteStride = sizeof(vertices[0]);

    D3D11_SUBRESOURCE_DATA sd{};
    sd.pSysMem = vertices;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
}
