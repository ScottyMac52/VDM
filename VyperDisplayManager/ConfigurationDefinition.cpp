#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ConfigurationDefinition.h"
#include <fstream>  
#include "FileChecker.h"

using namespace Json;
using namespace std;

configuration_definition::configuration_definition()
{
	name_ = L"";
	enabled_ = false;
	file_name_ = L"";
	file_path_ = L"";
	throttle_type_ = L"";
	ruler_name_ = L"";
	set_opacity(1.0F);
	set_width(100);
	set_height(100);
	set_location(location(0, 0));
}

configuration_definition::configuration_definition(const LPCWSTR name, const LPCWSTR file_path, const LPCWSTR file_name, const float opacity, const area& image_area, const area& cropping_area) : configuration_definition()
{
	name_ = name;
	file_path_ = file_path;
	file_name_ = file_name;
	set_x(image_area.get_left());
	set_y(image_area.get_top());
	set_width(image_area.get_width());
	set_opacity(opacity);
	set_area(image_area);
	set_cropping_area(cropping_area);
}

std::wstring configuration_definition::toString() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << enabled_ << "N:" << name_ << "FP:" << file_path_ << "FN:" << file_name_ << get_area().toString() << std::endl;
	auto buffer = oss.str();
	return buffer;
}

std::wstring configuration_definition::get_name() const
{
	return name_;
}

std::wstring configuration_definition::get_module_name() const
{
	return module_name_;
}

void configuration_definition::set_module_name(const std::wstring& name)
{
	module_name_ = name;
}

std::wstring configuration_definition::getFullPath() const
{
	std::wostringstream oss;
	oss << file_path_ << file_name_;
	auto buffer = oss.str();
	return buffer;
}

bool configuration_definition::draw(HWND h_wnd, HDC h_wnd_dc) const
{
	auto full_path = getFullPath();
	if (!file_checker::validate_file(full_path))
	{
		std::wostringstream oss;
		oss << L"The image does not exist:" << full_path;
		auto buffer = oss.str();
		::MessageBox(h_wnd, buffer.c_str(), L"Error with Configuration", MB_OK | MB_ICONERROR);
		// Delete the Mem DC
		return false;
	}

	Graphics graphics(h_wnd_dc);
	graphics.Flush();
	Image image(full_path.c_str());
	auto rect = Gdiplus::Rect(0, 0, get_width(), get_height());
	ColorMatrix color_matrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, get_opacity(), 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	// Create an ImageAttributes object and set its color matrix.
	ImageAttributes image_att;
	image_att.SetColorMatrix(&color_matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	if (get_cropping_area().get_square_area() > 0)
	{
		auto cropArea = get_cropping_area();
		graphics.DrawImage(&image, rect, cropArea.get_left(), cropArea.get_top(), cropArea.get_width(), cropArea.get_height(), UnitPixel, &image_att);
	}
	else
	{
		graphics.DrawImage(&image, rect, 0, 0, image.GetWidth(), image.GetHeight(), UnitPixel, &image_att);
	}
	return false;
}

HWND configuration_definition::get_window() const
{
	return h_wnd_;
}

Json::Value configuration_definition::to_json() const
{
	Json::Value value(Json::objectValue);
	value["moduleName"] = module_name_.c_str();
	value["name"] = name_.c_str();
	value["filepath"] = file_path_.c_str();
	value["filename"] = file_name_.c_str();
	value["enabled"] = enabled_;
	value["opacity"] = get_opacity();
	value["left"] = 0;
	value["top"] = 0;
	value["width"] = get_width();
	return value;
}

configuration_definition::~configuration_definition()
= default;

