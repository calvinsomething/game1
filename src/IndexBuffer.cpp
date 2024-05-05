#include "IndexBuffer.h"

using namespace Microsoft::WRL;

IndexBuffer::IndexBuffer(Graphics &gfx, const unsigned *indices, unsigned byte_width) : Buffer(gfx)
{
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.StructureByteStride = sizeof(indices[0]);

    D3D11_SUBRESOURCE_DATA sd{};
    sd.pSysMem = indices;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
}
