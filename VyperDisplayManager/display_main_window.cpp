#include "pch.h"
#include "globals.h"
#include "main.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "generic_window.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include "display_main_window.h"
#include <cwctype>
#include "FileChecker.h"
#include "DisplayManager.h"
#include "input_parser.h"
#include "resource.h"

using namespace  std;

int display_main_window::on_paint()
{
	PAINTSTRUCT ps;
	const auto hdc = BeginPaint(h_wnd_, &ps);
	wstring status_text = L"Width: ";
	status_text.append(std::to_wstring(current_width_));
	status_text.append(L" Height: ");
	status_text.append(std::to_wstring(current_height_));
	draw_status_text(hdc, status_text.c_str(), false);
	EndPaint(h_wnd_, &ps);
	return 0;
}

display_main_window::display_main_window(main* app)
{
	app_ = app;
	p_display_manager = nullptr;
	p_client_area_ = new area(100, 100, 400, 200);
	current_width_ = p_client_area_->get_width();
	current_height_ = p_client_area_->get_height();
}

bool display_main_window::close()
{
	if(p_display_manager != nullptr)
	{
		p_display_manager->close_all();
		delete p_display_manager;
		p_display_manager = nullptr;
	}
	PostQuitMessage(0);
	return false;
}

LRESULT display_main_window::on_close()
{
	if (app_ != nullptr)
	{
		app_->quit(1);
	}
	return LRESULT();
}

bool display_main_window::draw_status_text(const HDC h_wnd_dc, const LPCWSTR selected_text, const bool is_locked) const
{
	RECT rect;

	if (is_locked)
	{
		SetTextColor(h_wnd_dc, RGB(0x00, 0xFF, 0x00));
	}
	else
	{
		SetTextColor(h_wnd_dc, RGB(0xFF, 0x00, 0x00));
	}

	SetBkMode(h_wnd_dc, TRANSPARENT);
	GetClientRect(h_wnd_, &rect);
	rect.left = 10;
	rect.top = 10;
	::DrawText(h_wnd_dc, selected_text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
	return true;
}

bool display_main_window::draw_bitmap(const HDC h_win_dc, const configuration_definition& cd) const
{
	return cd.draw(h_wnd_, h_win_dc);
}

LRESULT display_main_window::on_create_window(const HINSTANCE h_instance, HWND h_wnd)
{
	const auto on_create_result = generic_window::on_create_window(h_instance, h_wnd_);
	if (!on_create_result)
	{
		const auto error_id = ::GetLastError();
		const auto error_message = get_last_error_string(error_id);
		::MessageBox(h_wnd_, error_message.c_str(), L"Error in on_create_window calling on_create_window", MB_ICONEXCLAMATION);
		return false;
	}
	const auto set_window_result = set_window_pos(p_client_area_->get_left(), p_client_area_->get_top(), current_width_, current_height_, SWP_SHOWWINDOW, nullptr);
	if(!set_window_result)
	{
		const auto error_id = ::GetLastError();
		const auto error_message = get_last_error_string(error_id);
		::MessageBox(h_wnd_, error_message.c_str(), L"Error in on_create_window calling set_window_pos", MB_ICONEXCLAMATION);
		return false;
	}
	p_display_manager = new display_manager();
	p_display_manager->run(h_instance, h_wnd_, app_->get_command_line());
	return true;
}

LRESULT display_main_window::on_size(WPARAM w_param, LPARAM l_param)
{
	current_width_ = LOWORD(l_param);
	current_height_ = HIWORD(l_param);
	tagRECT client_rect{};
	::GetClientRect(h_wnd_, &client_rect);
	::InvalidateRect(h_wnd_, &client_rect, true);
	return 0;
}

bool display_main_window::create(const HINSTANCE h_instance, std::wstring class_name, const HWND parent)
{
	auto reg_status = register_class(h_instance, class_name, 0, nullptr, IDC_VYPERDISPLAYWINDOW, nullptr, COLOR_WINDOW + 1);

	// Extended window  creation
	h_wnd_ = ::CreateWindowExW(WS_EX_TOPMOST | WS_EX_WINDOWEDGE, class_name.c_str(), class_name.c_str(), WS_CAPTION | WS_SYSMENU,
		p_client_area_->get_left(), p_client_area_->get_top(), p_client_area_->get_width(), p_client_area_->get_height(), parent, nullptr, h_instance, nullptr);


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
