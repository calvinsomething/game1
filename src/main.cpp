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
        while (is_running)
        {
            PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
            if (msg.message == WM_QUIT)
            {
                exit_code = msg.wParam;
                is_running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    // Worker window_thread = {MessagePump};
    is_running = true;
    while (!is_running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    try
    {
        MainWindow window{};
        p_window = &window;

        MSG msg = {};
        while (is_running)
        {
            PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
            if (msg.message == WM_QUIT)
            {
                exit_code = msg.wParam;
                is_running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            p_window->RenderFrame();
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
