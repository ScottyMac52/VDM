#pragma once

class generic_window;
class display_manager;
class main;

class display_main_window :
	public generic_window
{
protected:
	int on_paint() override;
public:
	explicit display_main_window(main* app);
	virtual bool create(HINSTANCE h_instance, std::wstring class_name, HWND parent = nullptr) override;
	virtual bool close() override;
protected:
	virtual LRESULT on_close() override;
	bool draw_status_text(const HDC h_wnd_dc, const LPCWSTR selected_text, const bool is_locked) const;
	bool draw_bitmap(const HDC h_win_dc, const configuration_definition& cd) const;
	virtual LRESULT on_create_window(HINSTANCE h_instance, HWND h_wnd) override;
	virtual LRESULT on_size(WPARAM w_param, LPARAM l_param) override;
private:
	main* app_;
	display_manager* p_display_manager;
	area* p_client_area_;
	int current_height_;
	int current_width_;
};


