#include "ConstantBuffer.h"

template <> D3D11_BUFFER_DESC ConstantBuffer<D3D11_USAGE_DEFAULT>::create_buffer_desc(unsigned byte_width)
{
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    return bd;
}

template <> D3D11_BUFFER_DESC ConstantBuffer<D3D11_USAGE_DYNAMIC>::create_buffer_desc(unsigned byte_width)
{
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = byte_width;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    return bd;
}
