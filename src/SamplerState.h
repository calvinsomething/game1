#pragma once

#include "interfaces.h"

class SamplerState : public Bindable
{
    Microsoft::WRL::ComPtr<ID3D11SamplerState> pSS;

  public:
    SamplerState();

    void Bind() override;
};
