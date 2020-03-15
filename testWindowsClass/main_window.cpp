#include "pch.h"
#include "main_window.h"
#include <string>

using namespace std;

LRESULT CALLBACK wnd_proc_generic(const HWND h_wnd, const UINT message, const WPARAM w_param, const LPARAM l_param)
{
    auto me = reinterpret_cast<main_window*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA));
    if (me) return me->real_wnd_proc(h_wnd, message, w_param, l_param);
    return DefWindowProc(h_wnd, message, w_param, l_param);
}

ATOM main_window::register_class(HINSTANCE const h_instance, std::wstring& class_name, const int icon_id, const LPCWSTR cursor_id, const int menu_id, LPCWSTR icon_small_id, const int background_color)
{
    WNDCLASSEXW wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = wnd_proc_generic;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = h_instance;
    wcex.hIcon = icon_id == 0 ? nullptr : LoadIcon(h_instance, MAKEINTRESOURCE(icon_id));
    wcex.hCursor = LoadCursor(nullptr, cursor_id);
    wcex.hbrBackground = reinterpret_cast<HBRUSH>(background_color);
    wcex.lpszMenuName = menu_id == 0 ? nullptr : MAKEINTRESOURCE(menu_id);
    wcex.lpszClassName = class_name.c_str();
    wcex.hIconSm = icon_small_id == nullptr ? nullptr : LoadIcon(h_instance, MAKEINTRESOURCE(icon_small_id));
    return ::RegisterClassExW(&wcex);
}

std::wstring main_window::get_last_error_string(DWORD const dw_error_code)
{
    //Get the error message, if any.
    if (dw_error_code == 0)
        return std::wstring(); //No error message has been recorded

    LPWSTR message_buffer = nullptr;
    const size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, dw_error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&message_buffer), 0, nullptr);

    std::wstring message(message_buffer, size);

    //Free the buffer.
    LocalFree(message_buffer);

    return message;
}

LRESULT main_window::real_wnd_proc(const HWND h_window, const UINT msg, const WPARAM w_param, const LPARAM l_param)
{

	switch (msg)
    {
    case WM_COMMAND:
        return on_command(w_param, l_param);
        break;
    case WM_CREATE:
        return on_create_window(l_param);
        break;
    case WM_CLOSE:
        return on_close();
        break;
    case WM_ENABLE:
        return on_enable(w_param);
        break;
    case WM_DESTROY:
        return on_destroy();
        break;
    case WM_PAINT:
        return on_paint();
        break;
    case WM_CHILDACTIVATE:
        return on_child_activate();
        break;
    case WM_CANCELMODE:
        return on_cancel_mode();
        break;
    default:
        return DefWindowProc(h_window, msg, w_param, l_param);
    }
}

bool main_window::create(HINSTANCE h_instance, std::wstring class_name, HWND parent)
{
    auto reg_status = register_class(h_instance, class_name, 0, 0, 0, 0, COLOR_WINDOW + 1);

    // Standard window  creation
    h_wnd_ = ::CreateWindowW(class_name.c_str(), class_name.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, h_instance, nullptr);

    if (h_wnd_ == nullptr)
    {
        const auto last_error = GetLastError();
        const auto error_message = get_last_error_string(last_error);
        ::MessageBoxW(nullptr, error_message.c_str(), L"Error", MB_ICONEXCLAMATION);
        return false;
    }

    // Save the this pointer 
    SetWindowLongPtr(h_wnd_, GWLP_USERDATA, reinterpret_cast<long>(this));
    auto me = reinterpret_cast<main_window*>(GetWindowLongPtr(h_wnd_, GWLP_USERDATA));
    return true;
}

bool main_window::show()
{
    ::ShowWindow(h_wnd_, SW_SHOW);
    return ::UpdateWindow(h_wnd_);
}

bool main_window::close()
{
    return ::CloseWindow(h_wnd_);
}

LRESULT main_window::on_create_window(LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_CREATE, 0, l_param);
}

LRESULT main_window::on_close()
{
    return DefWindowProc(h_wnd_, WM_CLOSE, 0, 0);
}

LRESULT main_window::on_enable(WPARAM w_param)
{
    return DefWindowProc(h_wnd_, WM_ENABLE, w_param, 0);
}

LRESULT main_window::on_destroy()
{
    return DefWindowProc(h_wnd_, WM_DESTROY, 0, 0);
}

int main_window::on_command(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_COMMAND, w_param, l_param);
}

LRESULT main_window::on_child_activate()
{
    return DefWindowProc(h_wnd_, WM_CHILDACTIVATE, 0, 0);
}

LRESULT main_window::on_cancel_mode()
{
    return DefWindowProc(h_wnd_, WM_CANCELMODE, 0, 0);
};

LRESULT main_window::on_activate_app(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_ACTIVATEAPP, w_param, l_param);
}

LRESULT main_window::on_input_language_change_request(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_INPUTLANGCHANGEREQUEST, w_param, l_param);
}

LRESULT main_window::on_window_position_changing(LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_WINDOWPOSCHANGING, 0, l_param);
}

LRESULT main_window::on_window_position_changed(LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_WINDOWPOSCHANGED, 0, l_param);
}

LRESULT main_window::on_sizing(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_SIZING, 0, l_param);
}

LRESULT main_window::on_size(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_SIZE, w_param, l_param);
}

LRESULT main_window::on_show(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_SHOWWINDOW, w_param, l_param);
}

LRESULT main_window::on_quit(WPARAM w_param)
{
    return DefWindowProc(h_wnd_, WM_QUIT, w_param, 0);
}

LRESULT main_window::on_custom_message(UINT msg, WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, msg, w_param, l_param);
}
