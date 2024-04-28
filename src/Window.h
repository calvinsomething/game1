#pragma once

#include "pch.h"

#include "Exception.h"

// Exception Handling
#define THROW_IF_ERROR(is_error)                                                                                       \
    {                                                                                                                  \
        if (is_error)                                                                                                  \
        {                                                                                                              \
            throw get_windows_exception(GetLastError(), __FILE__, __LINE__);                                           \
        }                                                                                                              \
    }
#undef THROW_IF_FAILED
#define THROW_IF_FAILED(fn) THROW_IF_ERROR(FAILED(fn))
#define THROW_IF_FALSE(value) THROW_IF_ERROR(!value)

Exception get_windows_exception(HRESULT error_code, const char *file, unsigned line);

// Window
class Window
{
  protected:
    HINSTANCE hInstance;
    HWND hWnd;

  public:
    Window(const char *className, unsigned long windowExStyle, unsigned long windowStyle, WNDPROC wndProc,
           const char *iconName);
    virtual ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
};
