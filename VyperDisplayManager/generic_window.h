#pragma once

using namespace std;

/// <summary>
/// Main starting WinPRoc
/// </summary>
LRESULT CALLBACK wnd_proc_generic(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param);

/// <summary>
/// generic window class for all windows
/// </summary>
class generic_window
{
public:
	/// <summary>
	/// Ctor default
	/// </summary>
	generic_window() = default;
	/// <summary>
	/// copy ctor
	/// </summary>
	/// <param name="copy"></param>
	generic_window(const generic_window& copy);
	/// <summary>
	/// move ctor
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	generic_window(const generic_window&& move) noexcept;
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
	/// <summary>
	/// equality operator for HWND
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator==(const HWND& ref) const;
	/// <summary>
	/// inequality operator for HWND
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator!=(const HWND& ref) const;
	/// <summary>
	/// equality operator for generic_window
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator==(const generic_window& ref) const;
	/// <summary>
	/// inequality operator for generic_window
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator!=(const generic_window& ref) const;
	/// <summary>
	/// copy assignment operator for generic_window
	/// </summary>
	/// <param name="source"></param>
	/// <returns></returns>
	generic_window& operator=(const generic_window& source);
	/// <summary>
	/// move assignment operator for generic_window
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	generic_window& operator=(generic_window&& move) noexcept;
	/// <summary>
	/// copy assignment operator for HWND
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	generic_window& operator=(const HWND& ref);
	/// <summary>
	/// draws a line from one point to another in the current window
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="color"></param>
	/// <param name="pen_style"></param>
	/// <param name="thickness"></param>
	/// <returns></returns>
	bool draw_line(const location& from, const location& to, const COLORREF color, const int pen_style, const int thickness) const;
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
	/// <summary>
	/// WM_POSITION_CHANGING
	/// </summary>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_window_position_changing(LPARAM l_param);
	/// <summary>
	/// WM_POSITIONED_CHANGED
	/// </summary>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_window_position_changed(LPARAM l_param);
	/// <summary>
	/// WM_SIZING
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_sizing(WPARAM w_param, LPARAM l_param);
	/// <summary>
	/// WM_SIZE
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_size(WPARAM w_param, LPARAM l_param);
	/// <summary>
	/// WM_SHOW
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	virtual LRESULT on_show(WPARAM w_param, LPARAM l_param);
	/// <summary>
	/// WM_QUIT
	/// </summary>
	/// <param name="w_param"></param>
	/// <returns></returns>
	virtual LRESULT on_quit(WPARAM w_param);
	/// <summary>
	/// WM_MOUSE_WHEEL
	/// </summary>
	/// <param name="f_keys"></param>
	/// <param name="wheel_delta"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_mouse_wheel(unsigned short const f_keys, short const wheel_delta, int const x_pos, int const y_pos) const;
	/// <summary>
	/// WM_MOUSE_MOVE
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_mouse_move(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	/// <summary>
	/// WM_LBUTTONDOWN
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	virtual LRESULT on_mouse_left_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos);
	/// <summary>
	/// WM_RBBUTTONDOWN
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	virtual LRESULT on_mouse_right_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos);
	/// <summary>
	/// WM_LBBUTTONUP
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_mouse_left_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	/// <summary>
	/// WM_RBBUTTONUP
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_mouse_right_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	/// <summary>
	/// WM_LBDBLCLICK
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_mouse_left_double_click(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	/// <summary>
	/// WM_RBDBLCLICK
	/// </summary>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <param name="x_pos"></param>
	/// <param name="y_pos"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_mouse_right_double_click(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const;
	/// <summary>
	/// The default mouse when the others are not overridden
	/// </summary>
	/// <param name="msg"></param>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_default_mouse(const UINT msg, const WPARAM w_param, const LPARAM l_param) const;
	/// <summary>
	/// Can be used to process any other main messages that are not handled by default
	/// </summary>
	/// <param name="msg"></param>
	/// <param name="w_param"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	[[nodiscard]] virtual LRESULT on_custom_message(const UINT msg, const WPARAM w_param, const LPARAM l_param) const;
	/// <summary>
	/// Handle to the window
	/// </summary>
	HWND h_wnd_ = nullptr;
};

class generic_window_impl : public generic_window
{
protected:
	virtual int on_paint() override;
	[[nodiscard]] virtual LRESULT on_mouse_right_up(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const override;
public:
	
};

