#pragma once

#include "pch.h"

#include "structs.h"

#ifndef NDEBUG
#include "GfxDebug.h"
#endif

class Graphics {
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pCtx;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;

#ifndef NDEBUG
	GfxDebug debug;
#endif

public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	void Clear(Color color);
	void EndFrame();
	void DrawTriangle();
};
