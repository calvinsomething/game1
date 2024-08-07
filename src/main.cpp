#include "MainWindow.h"
#include "Worker.h"

static bool is_running = false;
static int exit_code = 0;
static std::exception input_thread_exception = {};
static bool input_thread_did_throw = false;

MainWindow *p_window;

void MessagePump()
{
    try
    {
        MainWindow window{};
        p_window = &window;

        is_running = true;

        MSG msg = {};
        BOOL result;
        while (is_running)
        {
            if ((result = GetMessageA(&msg, NULL, 0, 0)) != 0)
            {
                if (result == -1)
                {
                    throw Exception("Invalid HWND.", result, __FILE__, __LINE__);
                }
                else if (msg.message == WM_QUIT)
                {
                    exit_code = msg.wParam;
                    is_running = false;
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                is_running = 0;
            }
        }
    }
    catch (std::exception &e)
    {
        input_thread_exception = e;
        input_thread_did_throw = true;
        is_running = false;
    }
    catch (...)
    {
        input_thread_exception = std::exception("unknown input thread exception");
        input_thread_did_throw = true;
        is_running = false;
    }
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *pCmdLine, int nCmdShow)
{
    Worker window_thread = {MessagePump};
    while (!is_running && !input_thread_did_throw)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    try
    {
        while (is_running)
        {
            p_window->RenderFrame();
        }
        if (input_thread_did_throw)
        {
            throw input_thread_exception;
        }
    }
    catch (const std::exception &e)
    {
        is_running = false;
        MessageBoxA(nullptr, e.what(), "Exception Thrown", MB_OK | MB_TASKMODAL);
    }
    catch (...)
    {
        is_running = false;
        MessageBoxA(nullptr, "Unknown error occurred.", "Exception Thrown", MB_OK);
    }
    return exit_code;
}
