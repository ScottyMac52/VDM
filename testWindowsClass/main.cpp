#include "pch.h"
#include "main.h"
#include "windowsx.h"
#include "framework.h"
#include <windows.h>

#include "display_main_window.h"

display_main_window* p_main_window;

// Global Variables:
HINSTANCE hInst;
#define MAX_LOADSTRING 100
WCHAR szMainTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szMainWindowClass[MAX_LOADSTRING];            // the main window class name

int APIENTRY wWinMain(  _In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR    lpCmdLine,
						_In_ int       nCmdShow)
{

	const auto h_accel_table = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

    MSG msg;

    main* main_app = new main();
    main_app->run(hInstance);

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, h_accel_table, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


void main::run(HINSTANCE hInstance)
{
    p_main_window = new display_main_window(this);
    std::wstring class_name = L"MainWindow";
    p_main_window->register_class(hInstance, class_name);
    p_main_window->create(hInstance, class_name);
    p_main_window->show();
}

void main::quit(int status)
{
	if(p_main_window != nullptr)
	{
        p_main_window->close();
	}
}
