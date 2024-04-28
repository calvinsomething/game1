#pragma once

#include "Buffer.h"

template <D3D11_USAGE U> class ConstantBuffer : public Buffer
{
  public:
    template <typename T> ConstantBuffer(Graphics &gfx, T *data, unsigned byte_width);
    D3D11_BUFFER_DESC create_buffer_desc(unsigned byte_width);
};

template <D3D11_USAGE U>
template <typename T>
ConstantBuffer<U>::ConstantBuffer(Graphics &gfx, T *data, unsigned byte_width) : Buffer(gfx)
{
    D3D11_BUFFER_DESC bd = create_buffer_desc(byte_width);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = data;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
}
