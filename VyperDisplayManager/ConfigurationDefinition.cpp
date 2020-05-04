// ReSharper disable CppClangTidyClangDiagnosticMissingBraces
#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include <fstream>  

#include "app_settings.h"
#include "FileChecker.h"

using namespace std;
using namespace json;

#pragma region Ctor and Dtor

configuration_definition::configuration_definition(const location& start_location)
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
	relative_location_ = start_location;
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
	ruler_size_ = app_settings::get_ruler_size();
	show_rulers_ = app_settings::show_rulers();
	ruler_major_size_ = app_settings::get_ruler_major_width();
	ruler_minor_size_ = app_settings::get_ruler_minor_width();
	relative_location_ = source.relative_location_;
}

configuration_definition::configuration_definition(configuration_definition&& source) noexcept 
{
	try
	{
		*this = source;
	}
	catch(...)
	{
		// TODO: Fix swallowed exception
		// swallow
	}
}

configuration_definition::~configuration_definition()
= default;


configuration_definition::configuration_definition(const LPCWSTR name, const location& start_location, const LPCWSTR file_path, const LPCWSTR file_name, const float opacity, const area& image_area, const area& cropping_area) :
	configuration_definition(start_location)
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

#pragma region to_string()

std::wstring configuration_definition::to_string() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << enabled_ << "N:" << name_ << "FP:" << file_path_ << "FN:" << file_name_ << L" at: " << relative_location_.to_string() << L" " << get_area().to_string() << std::endl;
	auto buffer = oss.str();
	return buffer;
}

#pragma endregion to_string()

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

HWND configuration_definition::get_window() const
{
	return h_wnd_;
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

#pragma region draw method

bool configuration_definition::draw(HWND h_wnd, HDC h_wnd_dc) const
{
	const auto full_path = get_full_path();
	Graphics graphics(h_wnd_dc);
	graphics.Flush();
	Image image(full_path.c_str());
	// Always relative to (0,0) from the client window
	const auto rect = Gdiplus::Rect(relative_location_.get_x(), relative_location_.get_y(), get_width(), get_height());
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
		const auto crop_area = get_cropping_area();
		graphics.DrawImage(&image, rect, crop_area.get_left(), crop_area.get_top(), crop_area.get_width(), crop_area.get_height(), UnitPixel, &image_att);
	}
	else
	{
		graphics.DrawImage(&image, rect, 0, 0, image.GetWidth(), image.GetHeight(), UnitPixel, &image_att);
	}

	if (show_rulers_)
	{
		show_ruler(&graphics);
	}
	
	return false;
}

void configuration_definition::show_ruler(Graphics *g) const
{
	const auto x_center = get_width() / 2;
	const auto y_center = get_height() / 2;
	Pen* pen = new Pen(Color::Red);
	FontFamily  fontFamily(L"Times New Roman");
	Font font(&fontFamily, 10, FontStyleBold, UnitPixel);
	SolidBrush  brush(Color(255, 255, 0, 0));

	g->SetCompositingMode(CompositingModeSourceOver);
	g->SetCompositingQuality(CompositingQualityHighSpeed);

#pragma warning( push )
#pragma warning( disable : 26812)
	g->DrawLine(pen, 0, y_center, get_width(), y_center);
	for (auto x = 0; x < get_width(); x++)
	{
		if (x % ruler_size_ == 0)
		{
			g->DrawLine(pen, x, y_center - ruler_minor_size_, x, y_center + ruler_minor_size_);
		}

		if (x % 100 == 0)
		{
			g->DrawLine(pen, x, y_center - ruler_major_size_, x, y_center + ruler_major_size_);
			const auto x_coord_label = std::to_wstring(x);
			auto string_origin = PointF(x - 10, y_center + 10);
			g->DrawString(x_coord_label.c_str(), x_coord_label.size(), &font, string_origin, &brush);
		}
	}
	g->DrawLine(pen, x_center, 0, x_center, get_height());
	for (auto y = 0; y < get_height(); y++)
	{
		if (y % ruler_size_ == 0)
		{
			g->DrawLine(pen, x_center - ruler_minor_size_, y, x_center + ruler_minor_size_, y);
		}

		if (y % 100 == 0)
		{
			g->DrawLine(pen, x_center - ruler_major_size_, y, x_center + ruler_major_size_, y);
			const auto y_coord_label = std::to_wstring(y);
			auto string_origin = PointF(x_center + 10, y - 7);
			g->DrawString(y_coord_label.c_str(), y_coord_label.size(), &font, string_origin, &brush);
		}
	}
#pragma warning( pop ) 
	delete pen;
}

#pragma endregion draw method

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

configuration_definition& configuration_definition::operator=(configuration_definition&& move) noexcept  
{
	*this = move;
	return *this;
}

configuration_definition& configuration_definition::operator=(const json::Object& object)
{
	json::Array sub_configurations;
	configuration_definition sub_configuration(location(0,0));
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

	// 
	if(property_exists(object, L"subConfigDef"))
	{

		sub_configurations = object[L"subConfigDef"];

		auto it = sub_configurations.begin();
		while (it != sub_configurations.end())
		{
			auto current_sub = static_cast<json::Object>(*it);
			auto current_image_config = current_sub;
			++it;
		}

		sub_configuration = sub_configurations[0];
	}
	
	return *this;
}

configuration_definition& configuration_definition::operator=(const location& new_location)
{
	relative_location_ = new_location;
	return *this;
}

bool configuration_definition::operator==(const configuration_definition& other) const
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
	return true;
}

bool configuration_definition::operator!=(const configuration_definition& other) const
{
	auto is_equal = name_ == other.name_;
	is_equal = is_equal && (file_path_ != other.file_path_);
	is_equal = is_equal && (file_name_ != other.file_name_);
	is_equal = is_equal && (module_name_ != other.module_name_);
	is_equal = is_equal && (enabled_ != other.enabled_);
	is_equal = is_equal && (throttle_type_ != other.throttle_type_);
	is_equal = is_equal && (ruler_name_ != other.ruler_name_);
	return !is_equal;
}

#pragma endregion operators



