#include "MainWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow)
{
	int exitCode = 0;
	try {
		MainWindow window{};

		MSG msg{};
		while ((exitCode = GetMessageA(&msg, NULL, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			window.RenderFrame();
		}
	} catch (const std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Exception Thrown", MB_OK | MB_TASKMODAL);
	} catch (...) {
		MessageBoxA(nullptr, "Unknown error occurred.", "Exception Thrown", MB_OK);
	}
	return exitCode;
}
