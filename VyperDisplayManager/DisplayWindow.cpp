#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include "resource.h"
#include "generic_window.h"
#include "DisplayWindow.h"

#include <windowsx.h>

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

bool display_window::create(HINSTANCE h_instance, std::wstring class_name, HWND const parent)
{
    // Initialize GDI+
    Gdiplus::GdiplusStartupInput gdiplus_startup_input;
    GdiplusStartup(&m_gdiplusToken, &gdiplus_startup_input, nullptr);

    //auto reg_status = register_class(h_instance, class_name, 0, IDC_ARROW, IDC_VYPERDISPLAYWINDOW);
    auto reg_status = register_class(h_instance, class_name, 0, IDC_ARROW, 0);

    h_wnd_ = ::CreateWindowExW(WS_EX_TOPMOST, class_name.c_str(), class_name.c_str(), WS_POPUP,
        p_config_->get_left(), p_config_->get_top(), p_config_->get_width(), p_config_->get_height(), parent,nullptr, h_instance, nullptr);

    if (h_wnd_ == nullptr)
    {
	    const auto dw_error = GetLastError();
        const auto error_message = get_last_error_string(dw_error);
        ::MessageBoxW(nullptr, error_message.c_str(), L"Error Creating Window", MB_ICONEXCLAMATION);
        return false;
    }

    return generic_window::on_create_window(h_instance, h_wnd_);
}

int display_window::on_paint()
{
    PAINTSTRUCT ps;
    const auto hdc = BeginPaint(h_wnd_, &ps);
    p_config_->draw(h_wnd_, hdc);
    return EndPaint(h_wnd_, &ps);
}

LRESULT display_window::on_close()
{
	return LRESULT();
}

int display_window::on_command(WPARAM w_param, LPARAM l_param) const
{
    BOOL b_result = false;
    RECT client_rect;

	const int wm_id = LOWORD(w_param);
    // Parse the menu selections:
    switch (wm_id)
    {
    case IDM_EXIT:
        b_result = DestroyWindow(h_wnd_);
        break;
    case ID_ADJUST_QUARTER:
        p_config_->set_area(p_config_->get_area() /= 4);
        GetClientRect(h_wnd_, &client_rect);
        b_result = InvalidateRect(h_wnd_, &client_rect, true);
        break;
    case ID_ADJUST_HALF:
        p_config_->set_area(p_config_->get_area() /= 2);
        GetClientRect(h_wnd_, &client_rect);
        b_result = InvalidateRect(h_wnd_, &client_rect, true);
        break;
    case ID_ADJUST_DOUBLE:
        p_config_->set_area(p_config_->get_area() *= 2);
        GetClientRect(h_wnd_, &client_rect);
        b_result = InvalidateRect(h_wnd_, &client_rect, true);
        break;
    default:
        break;
    }

    return b_result;
}

LRESULT display_window::on_mouse_move(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const
{
    RECT client_rect;

	if(b_button_down_)
	{
        if(p_config_ != nullptr)
        {
	        p_config_->set_location(location(x_pos, y_pos));
            GetClientRect(h_wnd_, &client_rect);
            return InvalidateRect(h_wnd_, &client_rect, true);
        }
	}
    return 0;
}

LRESULT display_window::on_mouse_left_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos)
{
    RECT client_rect;
    b_button_down_ = true;
    GetClientRect(h_wnd_, &client_rect);
    return InvalidateRect(h_wnd_, &client_rect, true);
}

LRESULT display_window::on_mouse_right_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos)
{
    RECT client_rect;
    b_button_down_ = false;
    GetClientRect(h_wnd_, &client_rect);
    return InvalidateRect(h_wnd_, &client_rect, true);
}

