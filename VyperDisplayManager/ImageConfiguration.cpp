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

image_configuration::image_configuration(const image_configuration & copy) :
	offset_geometry(copy)
{
	name_ = copy.name_;
	file_path_ = copy.file_path_;
	file_name_ = copy.file_name_;
}

image_configuration::image_configuration(const image_configuration&& move) noexcept
{
	*this = move;
}

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

image_configuration& image_configuration::operator=(const image_configuration& ref)
{
	if (*this == ref)
		return *this;

	set_location(ref.get_location());
	set_area(ref.get_area());
	set_cropping_area(ref.get_cropping_area());
	set_opacity(ref.get_opacity());
	set_center(ref.get_center());
	set_use_as_switch(ref.get_use_as_switch());
	module_name_ = ref.module_name_;
	name_ = ref.name_;
	file_path_ = ref.file_path_;
	file_name_ = ref.file_name_;
	return *this;
}

image_configuration& image_configuration::operator=(image_configuration&& ref) noexcept
{
	*this = ref;
	return *this;
}
