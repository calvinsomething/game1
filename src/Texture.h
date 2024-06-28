#pragma once

#include "interfaces.h"

class Texture : public Bindable
{
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pView;

  public:
    Texture(const wchar_t *file_name);

    void Bind() override;
};
