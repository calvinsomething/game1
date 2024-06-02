#pragma once

#include "interfaces.h"

#include "ConstantBuffer.h"

class Shader : public Bindable
{
  protected:
    Microsoft::WRL::ComPtr<ID3DBlob> pByteCode;
    Microsoft::WRL::ComPtr<IUnknown> pDxShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

  public:
    Shader(const wchar_t *file_name);
    Shader(const wchar_t *file_name, std::vector<ConstantBuffer> &&constant_buffers);

    template <size_t N> void SetInputLayout(D3D11_INPUT_ELEMENT_DESC (&&ied)[N])
    {
        THROW_IF_FAILED(pDevice->CreateInputLayout(ied, N, pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(),
                                                   pInputLayout.GetAddressOf()));
    }

    std::vector<ConstantBuffer> constant_buffers;
    std::vector<ID3D11Buffer *> dx_constant_buffers;
};
