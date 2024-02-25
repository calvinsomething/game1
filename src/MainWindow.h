#include "Window.h"

class MainWindow: public Window {
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	MainWindow();
	~MainWindow();
};
