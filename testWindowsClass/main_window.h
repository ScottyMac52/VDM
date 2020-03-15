#pragma once
#include <string>

using namespace std;

LRESULT CALLBACK wnd_proc_generic(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param);

class main_window
{
public:
	main_window() = default;
	virtual ~main_window() = default;
	/// <summary>
	/// Window Proc for this class
	/// </summary>
	/// <param name="h_window"></param>
	/// <param name="msg"></param>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT CALLBACK real_wnd_proc(HWND h_window, UINT msg, WPARAM w_param, LPARAM l_param);
	/// <summary>
	/// Registers a class for use by the CreateWindow or CreateWindowEx calls
	/// </summary>
	/// <param name="h_instance">Instance handle</param>
	/// <param name="class_name">Name of the class</param>
	/// <param name="icon_id">ID of the icon to use</param>
	/// <param name="cursor_id">ID of the cursor to use</param>
	/// <param name="menu_id">ID of the menu to use</param>
	/// <param name="icon_small_id">ID of the small icon to use</param>
	/// <param name="background_color">Window background color default</param>
	/// <returns>ATOM</returns>
	virtual ATOM register_class(HINSTANCE const h_instance, std::wstring& class_name, const int icon_id = 0, const LPCWSTR cursor_id = nullptr, const int menu_id = 0, LPCWSTR icon_small_id = nullptr, const int background_color = COLOR_WINDOW + 1);
	/// <summary>
	/// Creates the Window
	/// </summary>
	/// <param name="h_instance"></param>
	/// <param name="class_name"></param>
	/// <param name="parent"></param>
	/// <returns></returns>
	virtual bool create(HINSTANCE h_instance, std::wstring class_name, HWND parent = nullptr);
	/// <summary>
	/// Shows the Window
	/// </summary>
	/// <returns></returns>
	virtual bool show();
	/// <summary>
	/// Closes the Window
	/// </summary>
	/// <returns></returns>
	virtual bool close();
protected:
	/// <summary>
	/// Used to get the wide string version of GetLastError()
	/// </summary>
	/// <param name="dw_error_code"></param>
	/// <returns>std::wstring</returns>
	static std::wstring get_last_error_string(DWORD const dw_error_code);
	/// <summary>
	/// Process WM_CREATE
	/// </summary>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_create_window(LPARAM l_param);
	/// <summary>
	/// Process WM_ClOSE
	/// </summary>
	/// <returns></returns>
	virtual LRESULT on_close();
	/// <summary>
	/// Process WM_ENABLE
	/// </summary>
	/// <param name="w_param"></param>
	/// <returns></returns>
	virtual LRESULT on_enable(WPARAM w_param);
	/// <summary>
	/// Process WM_DESTROY
	/// </summary>
	/// <returns></returns>
	virtual LRESULT on_destroy();
	/// <summary>
	/// Process WM_PAINT, forces the class to be abstract since derived classes MUSt implement it
	/// </summary>
	/// <returns></returns>
	virtual int on_paint() = 0;
	/// <summary>
	/// Process WM_COMMAND
	/// Callers should create their own processing hierarchy of the WM_COMMAND messages
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual int on_command(WPARAM w_param, LPARAM l_param);
	// ReSharper disable once CommentTypo
	/// <summary>
	/// Process WM_CHILDACTIVATE
	/// </summary>
	/// <returns></returns>
	virtual LRESULT on_child_activate();
	// ReSharper disable once CommentTypo
	/// <summary>
	/// Process WM_CANCELMODE
	/// </summary>
	/// <returns></returns>
	virtual LRESULT on_cancel_mode();
	// ReSharper disable once CommentTypo
	/// <summary>
	/// Process WM_ACTIVATEAPP
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_activate_app(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_input_language_change_request(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_window_position_changing(LPARAM l_param);
	virtual LRESULT on_window_position_changed(LPARAM l_param);
	virtual LRESULT on_sizing(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_size(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_show(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_quit(WPARAM w_param);
	/// <summary>
	/// Can be used to process any other main messages that are not handled by default
	/// </summary>
	/// <param name="msg"></param>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_custom_message(UINT msg, WPARAM w_param, LPARAM l_param);
	HWND h_wnd_;
};


