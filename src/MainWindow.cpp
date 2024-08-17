#include "MainWindow.h"

#include "Cube.h"
#include "Sphere.h"
#include "utils.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Static
LRESULT CALLBACK MainWindow::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    MainWindow &w = *reinterpret_cast<MainWindow *>(GetWindowLongPtrA(hWnd, 0));
    switch (msg)
    {
    case WM_NCCREATE: {
        CREATESTRUCT *cs = reinterpret_cast<CREATESTRUCT *>(lParam);
        SetWindowLongPtrA(hWnd, 0, reinterpret_cast<long long>(cs->lpCreateParams));
        break;
    }
    case WM_INPUT: {
        unsigned size;
        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)))
        {
            break;
        }

        void *ri = alloca(size);
        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, ri, &size, sizeof(RAWINPUTHEADER)) != size)
        {
            break;
        }

        const RAWINPUT &raw_input = *reinterpret_cast<RAWINPUT *>(ri);

        if (!w.pGUI->WantCaptureMouse())
        {
            w.mouse.left_button_down =
                (w.mouse.left_button_down || (raw_input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)) &&
                !(raw_input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP);
            w.mouse.Delta.x = raw_input.data.mouse.lLastX;
            w.mouse.Delta.y = raw_input.data.mouse.lLastY;
        }

        break;
    }
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

// Methods
MainWindow::MainWindow()
    : Window("MainWindow", 0, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, wndProc,
             "world_icon", 1280, 720, this),
      pGfx(std::make_unique<Graphics>(hWnd)), pGUI(std::make_unique<GUI>(hWnd)), mouse(InputDevices::GetMouse())

{
    auto &rng = RNG::Get();

    boxes.reserve(20);

    for (int i = 0; i < boxes.capacity() / 2; i++)
    {
        boxes.push_back(std::make_unique<Cube>(rng(1.0f, 15.0f), std::array<float, 6>{
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                 }));
        boxes.push_back(std::make_unique<Sphere<10>>(rng(1.0f, 15.0f), std::array<float, 6>{
                                                                           rng(0.0f, 1.0f),
                                                                           rng(0.0f, 1.0f),
                                                                           rng(0.0f, 1.0f),
                                                                           rng(0.0f, 1.0f),
                                                                           rng(0.0f, 1.0f),
                                                                           rng(0.0f, 1.0f),
                                                                       }));
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::RenderFrame()
{
    pGfx->Clear({0.3f, 0.6f, 0.4f});

    {
        const float mouse_speed = 0.04f * mouse.left_button_down;
        camera.Revolve(mouse_speed * mouse.Delta.x, mouse_speed * mouse.Delta.y);
        mouse.Delta = {};
    }

    // auto s = spheres.begin();
    for (auto b = boxes.begin(); b != boxes.end(); b++)
    {
        (*b)->Update(0.03f);
        (*b)->Draw();
        pGUI->Render();
    }

    pGfx->EndFrame();
}
