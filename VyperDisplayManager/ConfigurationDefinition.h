#pragma once
#include "DisplayConfiguration.h"

/// <summary>
/// Image configuration map
/// </summary>
typedef std::map<std::wstring, image_configuration*> image_config_map;

/// <summary>
/// Image configuration mapping pair
/// </summary>
typedef std::pair<std::wstring, image_configuration*> image_config_pair;

/// <summary>
/// Encapsulates a Configuration definition
/// </summary>
class configuration_definition : 
	public offset_geometry
{
public:
	configuration_definition();
	configuration_definition(const configuration_definition& source);
	configuration_definition(configuration_definition&& source) noexcept;
	configuration_definition(LPCWSTR name, LPCWSTR file_path, LPCWSTR file_name, float opacity, const area& image_area, const area& cropping_area);
	~configuration_definition();
	[[nodiscard]] std::wstring to_string() const override;
	[[nodiscard]] std::wstring get_name() const;
	[[nodiscard]] std::wstring get_module_name() const;
	void set_module_name(const std::wstring& name);
	[[nodiscard]] std::wstring get_full_path() const;
	void set_name(const std::wstring& name);
	bool draw(HWND h_wnd, HDC h_wnd_dc) const;
	[[nodiscard]] HWND get_window() const;
	configuration_definition& operator=(const configuration_definition& source);
	configuration_definition& operator=(json::Object object);
	bool operator==(const configuration_definition& other) const;
	bool operator!=(const configuration_definition& other) const;
	[[nodiscard]] std::wstring get_file_path() const;
	void set_file_path(const wstring& file_path);
	[[nodiscard]] std::wstring get_file_name() const;
	void set_file_name(const wstring& file_name);
	void set_enabled(bool enable);
	[[nodiscard]] virtual json::Object to_json_object() const override;
	virtual void from_json_object(const json::Object& object) override;
	configuration_definition& operator=(const display_configuration& current_display);
protected:
private:
	std::wstring module_name_;
	std::wstring name_;
	std::wstring file_name_;
	std::wstring file_path_;
	std::wstring throttle_type_;
	std::wstring ruler_name_;
	bool enabled_ = false;
	HWND h_wnd_{};
	image_config_map image_map_;
};

