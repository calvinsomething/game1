#include "SamplerState.h"

SamplerState::SamplerState()
{
    D3D11_SAMPLER_DESC sd = {};
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    GFX_DEBUG(pDevice->CreateSamplerState(&sd, pSS.GetAddressOf()));
}

void SamplerState::Bind()
{
    pCtx->PSSetSamplers(0, 1, pSS.GetAddressOf());
}
