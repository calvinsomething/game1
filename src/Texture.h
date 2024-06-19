#pragma once

#include "Graphics.h"

class Texture
{
        ComPtr<ID3D11ShaderResourceView> pView;
public:
    Texture(const char* file_name)
    {
        using namespace Microsoft::WRL;

        D3D11_TEXTURE2D_DESC td = {};
        td.Width = 0;
        td.Height = 0;
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.Format = DXGI_FORMAT_TEXTURE2D;
        td.Usage = DXGI_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        td.CPUAccessFlags = 0;
        // td.MiscFlags;
        td.SampleDesc.Count = 1;
        // td.SampleDesc.Quality;

        D3D11_SUBRESOURCE_DATA srd = {};
        srd.pSysMem = 0;
        srd.SysMemPitch = 0;

        ComPtr<ID3D11Texture2D> pTex;
        pDevice->CreateTexture2D(&td, &srd, pTex.GetAddressOf());

        D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
        srvd.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvd.Texture2D.MostLevels = 1;
        // srvd.Texture2D.MostDetailedMip;

        pDevice->CreateShaderResourceView(&pTex.Get(), &srvd, pView.GetAddressOf());
    }
};
