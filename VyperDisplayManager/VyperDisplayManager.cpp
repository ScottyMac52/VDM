// VyperDisplayManager.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "windowsx.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ConfigurationDefinition.h"
#include "DisplayManager.h"
#include "VyperDisplayManager.h"

#define MAX_LOADSTRING 100
#define UPDATE_SPEED 1.0F

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szMainTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szMainWindowClass[MAX_LOADSTRING];            // the main window class name

configuration_definition *pdef;
display_manager* pDisplayManager;
bool isButtonDown = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProcMain(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szMainTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VYPERDISPLAYMANAGER, szMainWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VYPERDISPLAYMANAGER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProcMain;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VYPERDISPLAYMANAGER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VYPERDISPLAYMANAGER);
    wcex.lpszClassName  = szMainWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szMainWindowClass, szMainTitle, WS_DLGFRAME,
      1000, 770, 200, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

bool DrawStatusText(HWND hWnd, HDC hWndDC, LPCWSTR selectedText, bool isLocked)
{
    RECT rect;

    if (isLocked)
    {
        SetTextColor(hWndDC, RGB(0x00, 0xFF, 0x00));
    }
    else
    {
        SetTextColor(hWndDC, RGB(0xFF, 0x00, 0x00));
    }

    ::SetBkMode(hWndDC, TRANSPARENT);
    ::GetClientRect(hWnd, &rect);
    rect.left = 110;
    rect.top = 150;
    ::DrawText(hWndDC, selectedText, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
    return true;
}

bool DrawBitmap(HWND hWnd, HDC hWinDC, configuration_definition cd)
{
    return cd.draw(hWnd, hWinDC);
}


void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    EndPaint(hWnd, &ps);
}

LRESULT OnLeftButtonDown(WPARAM wParam, int xPos, int yPos)
{
    pdef->set_location(location(xPos, yPos));
    return 0;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT clientRect;
    int x, y;

    switch (message)
    {
    case WM_LBUTTONDBLCLK:
    {
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        LRESULT result = OnLeftButtonDown(wParam, xPos, yPos);
        GetClientRect(hWnd, &clientRect);
        InvalidateRect(hWnd, &clientRect, true);
        return result;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        isButtonDown = true;
        GetClientRect(hWnd, &clientRect);
        InvalidateRect(hWnd, &clientRect, true);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        isButtonDown = false;
        GetClientRect(hWnd, &clientRect);
        InvalidateRect(hWnd, &clientRect, true);
    }
    break;
    case WM_MOUSEMOVE:
    {
        if (isButtonDown)
        {
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            pdef->set_location(location(x, y));
            GetClientRect(hWnd, &clientRect);
            InvalidateRect(hWnd, &clientRect, true);
        }
        return 0;
    }
    break;
    case WM_CREATE:
    {
        pDisplayManager = new display_manager();
        pDisplayManager->ReadConfigurations();
        pDisplayManager->create_configurations(hInst, hWnd);
        pDisplayManager->show_all();
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_ADJUST_QUARTER:
                pdef->set_area(pdef->get_area() /= 4);
                GetClientRect(hWnd, &clientRect);
                InvalidateRect(hWnd, &clientRect, true);
                break;
            case ID_ADJUST_HALF:
                pdef->set_area(pdef->get_area() /= 2);
                GetClientRect(hWnd, &clientRect);
                InvalidateRect(hWnd, &clientRect, true);
                break;
            case ID_ADJUST_DOUBLE:
                pdef->set_area(pdef->get_area() *= 2);
                GetClientRect(hWnd, &clientRect);
                InvalidateRect(hWnd, &clientRect, true);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            OnPaint(hWnd);
        }
        break;
    case WM_DESTROY:
        delete pDisplayManager;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
