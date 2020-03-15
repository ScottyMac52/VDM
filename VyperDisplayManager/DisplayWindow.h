#pragma once

class display_window :
	public generic_window
{
public:
	explicit display_window(const configuration_definition& config);
	~display_window();
	[[nodiscard]] configuration_definition get_configuration_definition() const;
	[[nodiscard]] std::wstring get_configuration_name() const;
	bool create(HINSTANCE h_instance, std::wstring class_name, HWND parent) override;
protected:
	int on_paint() override;
	LRESULT on_close() override;
	[[nodiscard]] int on_command(const WPARAM w_param, const LPARAM l_param) const override;
	[[nodiscard]] LRESULT on_mouse_move(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) const override;
	LRESULT on_mouse_left_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) override;
	LRESULT on_mouse_right_down(const WPARAM w_param, const LPARAM l_param, const int x_pos, const int y_pos) override;
private:
	/// <summary>
	/// Pointer to the ConfigurationDefinition
	/// </summary>
	configuration_definition *p_config_;
	bool b_button_down_ = false;
};

