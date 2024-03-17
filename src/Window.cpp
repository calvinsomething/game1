#include "Window.h"

#include "Exception.h"

#define THROW_IF_FAILED(fn)\
{\
	HRESULT hr = fn;\
	if (FAILED(hr))\
	{\
		throw Exception("Window class error.", hr, __FILE__, __LINE__);\
	}\
}
#define THROW_IF_FALSE(value)\
{\
	if (!value)\
	{\
		char *buffer = nullptr;\
		int code = GetLastError();\
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,\
				nullptr, code, 0, reinterpret_cast<char*>(&buffer), 0, nullptr);\
		Exception e(buffer, code, __FILE__, __LINE__);\
		LocalFree(buffer);\
		throw e;\
	}\
}

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
