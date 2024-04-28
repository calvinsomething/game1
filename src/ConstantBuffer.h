#pragma once

#include "Buffer.h"

template <D3D11_USAGE U> class ConstantBuffer : public Buffer
{
  public:
    template <typename T> ConstantBuffer(Graphics &gfx, T *data, unsigned byte_width);
};

template <>
template <typename T>
ConstantBuffer<D3D11_USAGE_DEFAULT>::ConstantBuffer(Graphics &gfx, T *data, unsigned byte_width) : Buffer(gfx)
{
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = data;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
}

template <>
template <typename T>
ConstantBuffer<D3D11_USAGE_DYNAMIC>::ConstantBuffer(Graphics &gfx, T *data, unsigned byte_width) : Buffer(gfx)
{
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = data;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
}
