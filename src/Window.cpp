#include "Window.h"

// Exception Handling
Exception get_windows_exception(HRESULT error_code, const char* file, unsigned line)
{
	char *buffer = nullptr;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<char*>(&buffer), 0, nullptr);
	Exception e(buffer, error_code, file, line);
	LocalFree(buffer);
	return e;
}

// Window
Window::Window(
	const char* className, unsigned long windowExStyle, unsigned long windowStyle, WNDPROC wndProc, const char* iconName
)
{
	WNDCLASSA wc{};
	
	wc.hInstance = GetModuleHandleA(nullptr);
	wc.lpszClassName = className;
	wc.lpfnWndProc = wndProc;

	if (iconName)
	{
		wc.hIcon = LoadIconA(GetModuleHandleA(nullptr), iconName);
	}
	
	THROW_IF_FALSE(RegisterClassA(&wc));

	hWnd = CreateWindowExA(
		windowExStyle, className, className, windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, wc.hInstance, nullptr
	);
	THROW_IF_FALSE(hWnd);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

