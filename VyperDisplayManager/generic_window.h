#pragma once

using namespace std;

/// <summary>
/// Main starting WinPRoc
/// </summary>
LRESULT CALLBACK wnd_proc_generic(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param);

class generic_window
{
public:
	/// <summary>
	/// Ctor default
	/// </summary>
	generic_window() = default;
	/// <summary>
	/// Destructor default
	/// </summary>
	virtual ~generic_window() = default;
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
	/// <summary>
	/// Allows the current window position to be changed
	/// </summary>
	/// <param name="x">left</param>
	/// <param name="y">top</param>
	/// <param name="cx">width</param>
	/// <param name="cy">height</param>
	/// <param name="u_flags">window sizing and positioning flags</param>
	/// <param name="h_wnd_insert_after">https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos#parameters</param>
	/// <returns></returns>
	bool set_window_pos(const int x, const int y, const int cx, const int cy, UINT u_flags, const HWND h_wnd_insert_after = nullptr) const;
	/// <summary>
	/// Gets the HWND for this window
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] HWND get_window_handle() const;
protected:
	/// <summary>
	/// Used to get the wide string version of GetLastError()
	/// </summary>
	/// <param name="dw_error_code"></param>
	/// <returns>std::wstring</returns>
	static std::wstring get_last_error_string(DWORD const dw_error_code);
	/// <summary>
	/// CreateWindow or CreateWindowX have been called
	/// </summary>
	/// <param name="h_instance"></param>
	/// <param name="h_wnd"></param>
	/// <returns></returns>
	virtual LRESULT on_create_window(HINSTANCE h_instance, HWND h_wnd);
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
	[[nodiscard]] virtual int on_command(const WPARAM w_param, const LPARAM l_param) const;
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
	virtual LRESULT on_window_position_changing(LPARAM l_param);
	virtual LRESULT on_window_position_changed(LPARAM l_param);
	virtual LRESULT on_sizing(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_size(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_show(WPARAM w_param, LPARAM l_param);
	virtual LRESULT on_quit(WPARAM w_param);
	[[nodiscard]] virtual LRESULT on_mouse_wheel(unsigned short const f_keys, short const wheel_delta, int const x_pos, int const y_pos) const;
	[[nodiscard]] virtual LRESULT on_mouse_move(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	virtual LRESULT on_mouse_left_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos);
	virtual LRESULT on_mouse_right_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos);
	[[nodiscard]] virtual LRESULT on_mouse_left_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	[[nodiscard]] virtual LRESULT on_mouse_right_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	[[nodiscard]] virtual LRESULT on_mouse_left_double_click(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	[[nodiscard]] virtual LRESULT on_mouse_right_double_click(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	[[nodiscard]] virtual LRESULT on_default_mouse(const UINT msg, const WPARAM w_param, const LPARAM l_param) const;
	/// <summary>
	/// Can be used to process any other main messages that are not handled by default
	/// </summary>
	/// <param name="msg"></param>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_custom_message(const UINT msg, const WPARAM w_param, const LPARAM l_param) const;
	HWND h_wnd_;
};

