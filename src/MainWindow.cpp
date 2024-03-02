#include "MainWindow.h"

// Static
LRESULT CALLBACK MainWindow::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

// Methods
MainWindow::MainWindow()
	: Window("MainWindow", 0, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, wndProc, "world_icon")
{
}

MainWindow::~MainWindow()
{
	Window::~Window();
}
