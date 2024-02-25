#include "Window.h"

Window::Window(
	const char* className, unsigned long windowExStyle, unsigned long windowStyle, WNDPROC wndProc
)
{
	WNDCLASSA wc{};
	
	wc.hInstance = GetModuleHandleA(nullptr);
	wc.lpszClassName = className;
	wc.lpfnWndProc = wndProc;
	
	unsigned short ret = RegisterClassA(&wc);
	if (!ret)
	{
		unsigned long errCode = GetLastError(); 
		throw std::exception("RegisterClass failed with error code:", errCode);
		return;
	}

	hWnd = CreateWindowExA(
		windowExStyle, className, className, windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, wc.hInstance, nullptr
	);

	if (!hWnd)
	{
		throw(std::exception("CreateWindow failed with return value:"));
		return;
	}
}

Window::~Window()
{
	DestroyWindow(hWnd);
}
