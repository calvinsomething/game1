#include <d3d11.h>

#include "structs.h"

class Graphics {
	IDXGISwapChain* pSwapChain;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pCtx;
	ID3D11RenderTargetView* pTarget;

public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	void Clear(Color color);
	void EndFrame();
};
