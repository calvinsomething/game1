#include <windows.h>

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

		EndPaint(hWnd, &ps);
		return 0;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow)
{
	const char* windowClassName = "MainWindow";

	WNDCLASSA wc{};
	
	wc.hInstance = hInstance;
	wc.lpszClassName = windowClassName;
	wc.lpfnWndProc = wndProc;
	
	RegisterClassA(&wc);

	unsigned long windowExStyle = 0,
				  windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE;

	HWND hwnd = CreateWindowExA(
		windowExStyle, windowClassName, windowClassName, windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, nullptr, nullptr
	);

	if (!hwnd)
	{
		return 0;
	}

	MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}
