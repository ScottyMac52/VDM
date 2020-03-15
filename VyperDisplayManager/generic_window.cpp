#include "pch.h"
#include "globals.h"
#include "generic_window.h"

#include <windowsx.h>

using namespace std;

LRESULT CALLBACK wnd_proc_generic(const HWND h_wnd, const UINT message, const WPARAM w_param, const LPARAM l_param)
{
    auto me = reinterpret_cast<generic_window*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA));
    if (me) return me->real_wnd_proc(h_wnd, message, w_param, l_param);
    return DefWindowProc(h_wnd, message, w_param, l_param);
}

ATOM generic_window::register_class(HINSTANCE const h_instance, std::wstring& class_name, const int icon_id, const LPCWSTR cursor_id, const int menu_id, LPCWSTR icon_small_id, const int background_color) 
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

std::wstring generic_window::get_last_error_string(DWORD const dw_error_code)
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

LRESULT generic_window::on_mouse_wheel(unsigned short const f_keys, short const wheel_delta, int const x_pos, int const y_pos) const
{
    return 0;
}

LRESULT generic_window::real_wnd_proc(const HWND h_window, const UINT msg, const WPARAM w_param, const LPARAM l_param)
{
    switch(msg)
    {
    case WM_COMMAND:
        return on_command(w_param, l_param);
        break;
    case WM_ACTIVATEAPP:
        return on_activate_app(w_param, l_param);
        break;
    case WM_MOUSEWHEEL:
	    {
			auto const f_keys = GET_KEYSTATE_WPARAM(w_param);
			auto const wheel_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            auto const x_pos = GET_X_LPARAM(l_param);
            auto const y_pos = GET_Y_LPARAM(l_param);

            return on_mouse_wheel(f_keys, wheel_delta, x_pos, y_pos);
	    }
        break;
    case WM_MOUSEMOVE:
	    {
    			
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_move(w_param, l_param, x_pos, y_pos);
	    }
	    break;
    case WM_LBUTTONDOWN:
	    {
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_left_down(w_param, l_param, x_pos, y_pos);
	    }
        break;
    case WM_RBUTTONDOWN:
	    {
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_right_down(w_param, l_param, x_pos, y_pos);
	    }
        break;
    case WM_LBUTTONUP:
	    {
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_left_up(w_param, l_param, x_pos, y_pos);
	    }
        break;
    case WM_RBUTTONUP:
	    {
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_right_up(w_param, l_param, x_pos, y_pos);
	    }
        break;
    case WM_LBUTTONDBLCLK:
	    {
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_left_double_click(w_param, l_param, x_pos, y_pos);
	    }
        break;
    case WM_RBUTTONDBLCLK:
	    {
	        auto const x_pos = GET_X_LPARAM(l_param);
	        auto const y_pos = GET_Y_LPARAM(l_param);
	        return on_mouse_right_double_click(w_param, l_param, x_pos, y_pos);
	    }
        break;
    case WM_CLOSE:
        return on_close();
        break;
    case WM_SIZE:
        return on_size(w_param, l_param);
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

bool generic_window::create(HINSTANCE h_instance, std::wstring class_name, HWND parent)
{
    auto reg_status = register_class(h_instance, class_name, 0, 0, 0, 0, COLOR_WINDOW+1);

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
    on_create_window(h_instance, h_wnd_);
    return true;
}

bool generic_window::show()
{
    ::ShowWindow(h_wnd_, SW_SHOW);
    return ::UpdateWindow(h_wnd_);
}

bool generic_window::close()
{
    return ::CloseWindow(h_wnd_);
}

bool generic_window::set_window_pos(const int x, const int y, const int cx, const int cy, UINT u_flags,
	const HWND h_wnd_insert_after) const
{
    return ::SetWindowPos(h_wnd_, h_wnd_insert_after, x, y, cx, cy, u_flags);
}

HWND generic_window::get_window_handle() const
{
    return h_wnd_;
}


LRESULT generic_window::on_create_window(HINSTANCE h_instance, const HWND h_wnd)
{
    // Save the this pointer 
    SetWindowLongPtr(h_wnd, GWLP_USERDATA, reinterpret_cast<long>(this));
    const auto me = reinterpret_cast<generic_window*>(GetWindowLongPtr(h_wnd_, GWLP_USERDATA));
    return me != nullptr;
}

LRESULT generic_window::on_close()
{
    return DefWindowProc(h_wnd_, WM_CLOSE, 0, 0);
}

LRESULT generic_window::on_enable(WPARAM w_param)
{
    return DefWindowProc(h_wnd_, WM_ENABLE, w_param, 0);
}

LRESULT generic_window::on_destroy()
{
    return DefWindowProc(h_wnd_, WM_DESTROY, 0, 0);
}

int generic_window::on_command(const WPARAM w_param, const LPARAM l_param) const
{
    return DefWindowProc(h_wnd_, WM_COMMAND, w_param, l_param);
}

LRESULT generic_window::on_child_activate()
{
    return DefWindowProc(h_wnd_, WM_CHILDACTIVATE, 0, 0);
}

LRESULT generic_window::on_cancel_mode()
{
    return DefWindowProc(h_wnd_, WM_CANCELMODE, 0, 0);
};

LRESULT generic_window::on_activate_app(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_ACTIVATEAPP, w_param, l_param);
}

LRESULT generic_window::on_window_position_changing(LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_WINDOWPOSCHANGING, 0, l_param);
}

LRESULT generic_window::on_window_position_changed(LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_WINDOWPOSCHANGED, 0, l_param);
}

LRESULT generic_window::on_sizing(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_SIZING, 0, l_param);
}

LRESULT generic_window::on_size(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_SIZE, w_param, l_param);
}

LRESULT generic_window::on_show(WPARAM w_param, LPARAM l_param)
{
    return DefWindowProc(h_wnd_, WM_SHOWWINDOW, w_param, l_param);
}

LRESULT generic_window::on_quit(WPARAM w_param)
{
    return DefWindowProc(h_wnd_, WM_QUIT, w_param, 0);
}

LRESULT generic_window::on_default_mouse(const UINT msg, const WPARAM w_param, const LPARAM l_param) const
{
    return DefWindowProc(h_wnd_, msg, w_param, l_param);
}

LRESULT generic_window::on_custom_message(const UINT msg, const WPARAM w_param, const LPARAM l_param) const
{
    return DefWindowProc(h_wnd_, msg, w_param, l_param);
}

LRESULT generic_window::on_mouse_move(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const
{
    return on_default_mouse(WM_MOUSEMOVE, w_param, l_param);
}

LRESULT generic_window::on_mouse_left_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) 
{
    return on_default_mouse(WM_LBUTTONDOWN, w_param, l_param);
}

LRESULT generic_window::on_mouse_right_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos)
{
    return on_default_mouse(WM_RBUTTONDOWN, w_param, l_param);
}

LRESULT generic_window::on_mouse_left_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const
{
    return on_default_mouse(WM_LBUTTONUP, w_param, l_param);
}

LRESULT generic_window::on_mouse_right_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const
{
    return on_default_mouse(WM_RBUTTONUP, w_param, l_param);
}

LRESULT generic_window::on_mouse_left_double_click(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const
{
    return on_default_mouse(WM_LBUTTONDBLCLK, w_param, l_param);
}

LRESULT generic_window::on_mouse_right_double_click(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const
{
    return on_default_mouse(WM_RBUTTONDBLCLK, w_param, l_param);
}
