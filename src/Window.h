#include "pch.h"

class Window
{
protected:
	HINSTANCE hInstance;
	HWND hWnd;

public:
	Window(const char* className, unsigned long windowExStyle, unsigned long windowStyle, WNDPROC wndProc, const char* iconName);
	virtual ~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};
