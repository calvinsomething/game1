#include "pch.h"

#include "structs.h"

class Graphics {
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pCtx;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;

public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	void Clear(Color color);
	void EndFrame();
};
