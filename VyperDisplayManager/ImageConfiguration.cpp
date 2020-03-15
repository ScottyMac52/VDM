#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"

using namespace json;
using namespace std;

image_configuration::image_configuration()
= default;

image_configuration::image_configuration(const LPCWSTR name, const LPCWSTR file_path, const LPCWSTR file_name, const float opacity, const area& image_area, const area& cropping_area)
{
	name_ = name;
	file_path_ = file_path;
	file_name_ = file_name;
	set_opacity(opacity);
	set_area(image_area);
	cropping_area_ = cropping_area;
}

image_configuration::~image_configuration()
= default;

std::wstring image_configuration::to_string() const
{
	auto string_result = L"name: " + name_ + offset_geometry::to_string();
	return string_result;
}

json::Object image_configuration::to_json_object() const
{
	auto object = offset_geometry::to_json_object();
	set_object_property(object, L"name", name_);
	return object;
}

void image_configuration::from_json_object(const json::Object& object)
{
	offset_geometry::from_json_object(object);
	if(property_exists(object, L"name"))
	{
		name_ = String(object[L"name"]).Value();
	}
}
