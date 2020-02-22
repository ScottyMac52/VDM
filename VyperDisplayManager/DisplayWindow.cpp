#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ConfigurationDefinition.h"
#include "resource.h"
#include "DisplayWindow.h"

using namespace Gdiplus;
ULONG_PTR m_gdiplusToken;

display_window::display_window(const configuration_definition& config)
{
    h_wnd_ = nullptr;
    p_config_ = new configuration_definition(config);
}

display_window::~display_window()
{
    delete p_config_;
}

ATOM RegisterClass(HINSTANCE const h_instance, const std::wstring& class_name)
{
    WNDCLASSEXW wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = h_instance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = class_name.c_str();
    return ::RegisterClassExW(&wcex);
}

bool display_window::create(HINSTANCE h_instance, const std::wstring& class_name, HWND const parent)
{
    // Initialize GDI+
    Gdiplus::GdiplusStartupInput gdiplus_startup_input;
    GdiplusStartup(&m_gdiplusToken, &gdiplus_startup_input, nullptr);

    auto reg_status = RegisterClass(h_instance, class_name);

    h_wnd_ = ::CreateWindowExW(WS_EX_TOPMOST, class_name.c_str(), class_name.c_str(), WS_POPUP,
        p_config_->get_left(), p_config_->get_top(), p_config_->get_width(), p_config_->get_height(), parent, nullptr, h_instance, nullptr);
	
    if (h_wnd_ == nullptr)
    {
	    const auto error_message = get_last_error_as_string();
        ::MessageBoxW(nullptr, error_message.c_str(), L"Error", MB_ICONEXCLAMATION);
        return false;
    }

    // Save the this pointer 
    SetWindowLongPtr(h_wnd_, GWLP_USERDATA, reinterpret_cast<long>(this));
    auto me = reinterpret_cast<display_window*>(GetWindowLongPtr(h_wnd_, GWLP_USERDATA));
    return true;
}

configuration_definition display_window::get_configuration_definition() const
{
    return *p_config_;
}

std::wstring display_window::get_configuration_name() const
{
    std::wostringstream oss;
    oss << p_config_->get_module_name() << L"-" << p_config_->get_name();
    auto buffer = oss.str();
    return buffer;
}

bool display_window::show() const
{
	::ShowWindow(h_wnd_, SW_SHOW);
    return ::UpdateWindow(h_wnd_);
}

bool display_window::close() const
{
	const auto close_status = ::CloseWindow(h_wnd_);
    return close_status;
}

void display_window::on_paint(HWND h_wnd) const
{
    PAINTSTRUCT ps;
    const auto hdc = BeginPaint(h_wnd, &ps);
    p_config_->draw(h_wnd, hdc);
    EndPaint(h_wnd, &ps);
}

void display_window::on_create(const HWND h_wnd)
{
    ::ShowWindow(h_wnd, SW_SHOW);
    ::UpdateWindow(h_wnd);
}

LRESULT CALLBACK WndProc(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param)
{
	auto me = reinterpret_cast<display_window*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA));
    if (me) return me->real_wnd_proc(h_wnd, message, w_param, l_param);
    return DefWindowProc(h_wnd, message, w_param, l_param);
}

std::wstring get_last_error_as_string()
{
    //Get the error message, if any.
    const auto error_message_id = ::GetLastError();
    if (error_message_id == 0)
        return std::wstring(); //No error message has been recorded

    LPWSTR messageBuffer = nullptr;
    size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, error_message_id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&messageBuffer), 0, nullptr);

    std::wstring message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);

    return message;
}

LRESULT CALLBACK display_window::real_wnd_proc(HWND h_hwnd, UINT msg, WPARAM w_param, LPARAM l_param) 
{
    
    RECT clientRect;
    
    switch (msg)
    {
    case WM_COMMAND:
    {
	    const int wm_id = LOWORD(w_param);
        // Parse the menu selections:
        switch (wm_id)
        {
        case IDM_EXIT:
            DestroyWindow(h_hwnd);
            break;
        case ID_ADJUST_QUARTER:
            p_config_->set_area(p_config_->get_area() /= 4);
            GetClientRect(h_hwnd, &clientRect);
            InvalidateRect(h_hwnd, &clientRect, true);
            break;
        case ID_ADJUST_HALF:
            p_config_->set_area(p_config_->get_area() /= 2);
            GetClientRect(h_hwnd, &clientRect);
            InvalidateRect(h_hwnd, &clientRect, true);
            break;
        case ID_ADJUST_DOUBLE:
            p_config_->set_area(p_config_->get_area() *= 2);
            GetClientRect(h_hwnd, &clientRect);
            InvalidateRect(h_hwnd, &clientRect, true);
            break;
        default:
            return DefWindowProc(h_hwnd, msg, w_param, l_param);
        }
    }
    break;
    case WM_PAINT:
    {
        on_paint(h_hwnd);
    }
    break;
    case WM_CLOSE:
    {
        Gdiplus::GdiplusShutdown(m_gdiplusToken);
        return close();
    }
    break;
    case WM_CREATE:
    {
        on_create(h_hwnd);
    }
    break;
    default:
        return DefWindowProc(h_hwnd, msg, w_param, l_param);
    }
    return 0;
}

