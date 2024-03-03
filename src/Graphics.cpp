#include "Graphics.h"

#include <exception>

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd{};

	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
  	scd.BufferDesc.RefreshRate.Numerator = 0;
  	scd.BufferDesc.RefreshRate.Denominator = 1;
  	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pCtx
	);

	if (FAILED(hr))
	{
		throw std::exception("DXGI_SWAP_EFFECT_DISCARD error");
	}

	ID3D11Resource* pSurface = nullptr;

	hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(&pSurface)
	); 

	if (FAILED(hr))
	{
	}

	pDevice->CreateRenderTargetView(pSurface, nullptr, &pTarget);

	pSurface->Release();
}

Graphics::~Graphics()
{
	pSwapChain->Release();
	pDevice->Release();
	pCtx->Release();
}

void Graphics::Clear(Color color)
{
	color.alpha = 1;
	pCtx->ClearRenderTargetView(pTarget, reinterpret_cast<float*>(&color));
}

void Graphics::EndFrame()
{
	pSwapChain->Present(1, 0);
}
