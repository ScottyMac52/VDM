#pragma once
#include "ImageConfiguration.h"

using namespace std;

/// <summary>
/// Image configuration map
/// </summary>
typedef std::map<std::wstring, image_configuration*> ImageConfigMap;

/// <summary>
/// Image configuration mapping pair
/// </summary>
typedef std::pair<std::wstring, image_configuration*> ImageConfigPair;

/// <summary>
/// Encapsulates a Configuration definition
/// </summary>
class configuration_definition : 
	public offset_geometry
{
public:
	configuration_definition();
	configuration_definition(LPCWSTR name, LPCWSTR file_path, LPCWSTR file_name, float opacity, const area& image_area, const area& cropping_area);
	~configuration_definition();
	virtual std::wstring toString() const override;
	std::wstring get_name() const;
	std::wstring get_module_name() const;
	void set_module_name(const std::wstring& name);
	std::wstring getFullPath() const;
	bool draw(HWND h_wnd, HDC h_wnd_dc) const;
	HWND get_window() const;
	Json::Value to_json() const;
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
	ImageConfigMap image_map_;
};

