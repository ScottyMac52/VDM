#pragma once

using namespace std;

ATOM RegisterClass(HINSTANCE h_instance, const std::wstring& class_name);
LRESULT CALLBACK WndProc(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param);
std::wstring get_last_error_as_string();

class display_window
{
public:
	explicit display_window(const configuration_definition& config);
	~display_window();
	bool create(HINSTANCE h_instance, const std::wstring& class_name, HWND const parent = nullptr);
	configuration_definition get_configuration_definition() const;
	LRESULT CALLBACK real_wnd_proc(HWND h_hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	std::wstring get_configuration_name() const;
	bool show() const;
	bool close() const;
protected:
	void on_paint(HWND h_wnd) const;
	static void on_create(HWND h_wnd);
private:
	/// <summary>
	/// Pointer to the ConfigurationDefinition
	/// </summary>
	configuration_definition *p_config_;
	HWND h_wnd_;
};

