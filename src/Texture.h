#pragma once

#include <WICTextureLoader.h>

#include "Graphics.h"

class Texture
{
        ComPtr<ID3D11ShaderResourceView> pView;
public:
    Texture(const wchar_t* file_name)
    {
        using namespace Microsoft::WRL;

        THROW_IF_FAILED(D3DX11CreateTextureFromFile(
            _In_  ID3D11Device           *pDevice,
            _In_  LPCTSTR                pSrcFile,
            _In_  D3DX11_IMAGE_LOAD_INFO *pLoadInfo,
            _In_  ID3DX11ThreadPump      *pPump,
            _Out_ ID3D11Resource         **ppTexture,
            _Out_ HRESULT                *pHResult
        ));


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

void* load_file(const wchar_t* file_name)
{
    // ------
    THROW_IF_FAILED(CoCreateInstance(
        [in]  REFCLSID  rclsid,
        [in]  LPUNKNOWN pUnkOuter,
        [in]  DWORD     dwClsContext,
        [in]  REFIID    riid,
        [out] LPVOID    *ppv
    ));

    ComPtr<IWICBitmapDecoder> pBitmapDecoder;

    THROW_IF_FAILED(CreateDecoderFromFilename(
        file_name,
        [in]          const GUID        *pguidVendor,
        [in]          DWORD             dwDesiredAccess,
        [in]          WICDecodeOptions  metadataOptions,
        pBitmapDecoder.GetAddressOf()
    ));

    ComPtr<IWICBitmapFrameDecode> pFrameDecode;

    THROW_IF_FAILED(GetFrame(
        [in]  UINT                  index,
        pFrameDecode.GetAddressOf()
    ));

    WICPixelFormatGUID pixelFormat;

    THROW_IF_FAILED(pFrameDecode->GetPixelFormat(*pixelFormat));
}
