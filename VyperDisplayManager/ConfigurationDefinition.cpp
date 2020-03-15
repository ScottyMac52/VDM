#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include <fstream>  
#include "FileChecker.h"

using namespace std;
using namespace json;

#pragma region Ctor and Dtor

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

configuration_definition::configuration_definition(const configuration_definition& source)
	: offset_geometry(source)
{
	name_ = source.name_;
	module_name_ = source.module_name_;
	file_path_ = source.file_path_;
	file_name_ = source.file_name_;
	throttle_type_ = source.throttle_type_;
	ruler_name_ = source.ruler_name_;
	enabled_ = source.enabled_;
	set_location(source.get_location());
	set_area(source.get_area());
	set_cropping_area(source.get_cropping_area());
	set_opacity(source.get_opacity());
	set_center(source.get_center());
}

configuration_definition::configuration_definition(configuration_definition&& source) noexcept 
{
	*this = source;
}

configuration_definition::~configuration_definition()
= default;


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

#pragma endregion Ctor and Dtor

std::wstring configuration_definition::to_string() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << enabled_ << "N:" << name_ << "FP:" << file_path_ << "FN:" << file_name_ << get_area().to_string() << std::endl;
	auto buffer = oss.str();
	return buffer;
}

#pragma region get_XXX 

std::wstring configuration_definition::get_name() const
{
	return name_;
}

std::wstring configuration_definition::get_module_name() const
{
	return module_name_;
}

std::wstring configuration_definition::get_file_path() const
{
	return file_path_;
}

std::wstring configuration_definition::get_file_name() const
{
	return file_name_;
}

std::wstring configuration_definition::get_full_path() const
{
	std::wostringstream oss;
	oss << file_path_ << L"\\" << file_name_;
	auto buffer = oss.str();
	return buffer;
}

#pragma endregion get_XXX

#pragma region set_XXX

void configuration_definition::set_name(const std::wstring& name)
{
	name_ = name;
}

void configuration_definition::set_module_name(const std::wstring& name)
{
	module_name_ = name;
}

void configuration_definition::set_file_path(const wstring& file_path)
{
	file_path_ = file_path;
}

void configuration_definition::set_file_name(const std::wstring& file_name)
{
	file_name_ = file_name;
}

void configuration_definition::set_enabled(const bool enable)
{
	enabled_ = enable;
}

#pragma endregion set_XXX

bool configuration_definition::draw(HWND h_wnd, HDC h_wnd_dc) const
{
	auto full_path = get_full_path();
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
		const auto cropArea = get_cropping_area();
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

#pragma region JSON

json::Object configuration_definition::to_json_object() const
{
	auto json_module = offset_geometry::to_json_object();
	set_object_property(json_module, L"filePath", file_path_);
	set_object_property(json_module, L"fileName", file_name_);
	set_object_property(json_module, L"moduleName", module_name_);
	set_object_property(json_module, L"name", name_);
	set_object_property(json_module, L"enabled", enabled_);
	return json_module;
}

void configuration_definition::from_json_object(const json::Object& object)
{
	offset_geometry::from_json_object(object);

	if (property_exists(object, L"filePath"))
	{
		file_path_ = String(object[L"filePath"]).Value();
	}

	if (property_exists(object, L"fileName"))
	{
		file_name_ = String(object[L"fileName"]).Value();
	}

	if (property_exists(object, L"name"))
	{
		name_ = String(object[L"name"]).Value();
	}

	if (property_exists(object, L"moduleName"))
	{
		module_name_ = String(object[L"moduleName"]).Value();
	}

	if (property_exists(object, L"enabled"))
	{
		enabled_ = Boolean(object[L"enabled"]).Value();
	}
}

configuration_definition& configuration_definition::operator=(const display_configuration& current_display)
{
	set_area(current_display.get_area());
	set_center(current_display.get_center());
	set_cropping_area(current_display.get_cropping_area());
	set_opacity(current_display.get_opacity());
	set_use_as_switch(current_display.get_use_as_switch());
	return *this;
}

#pragma endregion JSON

#pragma region operators

configuration_definition& configuration_definition::operator=(const configuration_definition& source)
= default;

configuration_definition& configuration_definition::operator=(const json::Object object)
{
	offset_geometry::from_json_object(object);
	
	if (property_exists(object, L"name"))
	{
		set_name(json::String(object[L"name"]));
	}

	if (property_exists(object, L"filePath"))
	{
		set_file_path(json::String(object[L"filePath"]));
	}

	if (property_exists(object, L"fileName"))
	{
		set_file_name(json::String(object[L"fileName"]));
	}

	if (property_exists(object, L"moduleName"))
	{
		set_module_name(json::String(object[L"moduleName"]));
	}

	if (property_exists(object, L"enabled"))
	{
		set_enabled(json::Boolean(object[L"enabled"]));
	}
	/*
	if (property_exists(object, L"useAsSwitch"))
	{
		set_use_as_switch(json::Boolean(object[L"useAsSwitch"]));
	}
	if (property_exists(object, L"makeOpaque"))
	{
		set_make_opaque(json::Boolean(object[L"makeOpaque"]));
	}
	if (property_exists(object, L"center"))
	{
		set_use_center(json::Boolean(object[L"center"]));
	}
	*/
	return *this;
}

bool configuration_definition::operator==(const configuration_definition & other) const
{
	if (name_ != other.name_)
		return false;
	if (file_path_ != other.file_path_)
		return false;
	if (file_name_ != other.file_name_)
		return false;
	if (module_name_ != other.module_name_)
		return false;
	if (enabled_ != other.enabled_)
		return false;
	if (throttle_type_ != other.throttle_type_)
		return false;
	if (ruler_name_ != other.ruler_name_)
		return false;
	/*
	if (use_center_ != other.use_center_)
		return false;
	if (make_opaque_ != other.make_opaque_)
		return false;
	if (use_as_switch_ != other.use_as_switch_)
		return false;
	*/
	return true;
}

bool configuration_definition::operator!=(const configuration_definition & other) const
{
	auto is_equal = name_ == other.name_;
	is_equal = is_equal && (file_path_ != other.file_path_);
	is_equal = is_equal && (file_name_ != other.file_name_);
	is_equal = is_equal && (module_name_ != other.module_name_);
	is_equal = is_equal && (enabled_ != other.enabled_);
	is_equal = is_equal && (throttle_type_ != other.throttle_type_);
	is_equal = is_equal && (ruler_name_ != other.ruler_name_);
	/*
	is_equal = is_equal && (use_center_ != other.use_center_);
	is_equal = is_equal && (use_as_switch_ != other.use_as_switch_);
	is_equal = is_equal && (make_opaque_ != other.make_opaque_);
	*/
	return !is_equal;
}

#pragma endregion operators



