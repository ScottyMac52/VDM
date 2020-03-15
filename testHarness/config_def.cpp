#include <string>
#include "cajun/json/elements.h"

using namespace std;
using namespace json;

#include "json_check.h"
#include "config_def.h"

#pragma region Ctor and Dtor

config_def::config_def()
= default;

config_def::config_def(const config_def& source)
{
	name_ = source.name_;
	module_name_ = source.module_name_;
	file_path_ = source.file_path_;
	file_name_ = source.file_name_;
	throttle_type_ = source.throttle_type_;
	ruler_name_ = source.ruler_name_;
	enabled_ = source.enabled_;
	make_opaque_ = source.make_opaque_;
	use_center_ = source.use_center_;
	use_as_switch_ = source.use_as_switch_;
}

config_def::config_def(config_def&& source) noexcept
{
	*this = source;
}

config_def::~config_def()
= default;

#pragma endregion Ctor and Dtor

#pragma region get_XXX 

std::wstring config_def::get_name() const
{
	return name_;
}

std::wstring config_def::get_module_name() const
{
	return module_name_;
}

std::wstring config_def::get_file_name() const
{
	return file_name_;
}

std::wstring config_def::get_file_path() const
{
	return file_path_;
}

std::wstring config_def::get_full_path() const
{
	return file_path_ + L"\\" + file_name_;
}

bool config_def::get_enabled() const
{
	return enabled_;
}

bool config_def::get_use_as_switch() const
{
	return use_as_switch_;
}

bool config_def::get_make_opaque() const
{
	return make_opaque_;
}

bool config_def::get_use_center() const
{
	return use_center_;
}

#pragma endregion get_XXX 

#pragma region set_XXX

void config_def::set_name(const std::wstring& name)
{
	name_ = name;
}

void config_def::set_module_name(const std::wstring& name)
{
	module_name_ = name;
}

void config_def::set_file_path(const std::wstring& path)
{
	file_path_ = path;
}

void config_def::set_file_name(const std::wstring& file_name)
{
	file_name_ = file_name;
}

void config_def::set_enabled(const bool enable)
{
	enabled_ = enable;
}

void config_def::set_use_as_switch(const bool use_switch)
{
	use_as_switch_ = use_switch;
}

void config_def::set_make_opaque(const bool is_opaque)
{
	make_opaque_ = is_opaque;
}

void config_def::set_use_center(const bool use_center)
{
	use_center_ = use_center;
}

#pragma endregion set_XXX

#pragma region JSON

json::Object config_def::to_json_object() const
{
	json::Object json_module;
	set_object_property(json_module, L"name", name_);
	set_object_property(json_module, L"filePath", file_path_);
	set_object_property(json_module, L"fileName", file_name_);
	set_object_property(json_module, L"moduleName", module_name_);
	set_object_property(json_module, L"enabled", enabled_);
	set_object_property(json_module, L"useAsSwitch", use_as_switch_);
	set_object_property(json_module, L"makeOpaque", make_opaque_);
	set_object_property(json_module, L"center", use_center_);
	return json_module;
}

#pragma endregion JSON

#pragma region operators

config_def& config_def::operator=(const config_def& source)
= default;

config_def& config_def::operator=(const json::Object object)
{
	if(property_exists(object, L"name"))
	{
		set_name(json::String(object[L"name"]));
	}

	if(property_exists(object, L"filePath"))
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
	return *this;
}

bool config_def::operator==(const config_def& other) const
{
	if(name_ != other.name_)
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
	if (use_center_ != other.use_center_)
		return false;
	if (make_opaque_ != other.make_opaque_)
		return false;
	if (use_as_switch_ != other.use_as_switch_)
		return false;
	return true;
}

bool config_def::operator!=(const config_def& other) const
{
	auto is_equal = name_ == other.name_;
	is_equal = is_equal && (file_path_ != other.file_path_);
	is_equal = is_equal && (file_name_ != other.file_name_);
	is_equal = is_equal && (module_name_ != other.module_name_);
	is_equal = is_equal && (enabled_ != other.enabled_);
	is_equal = is_equal && (throttle_type_ != other.throttle_type_);
	is_equal = is_equal && (ruler_name_ != other.ruler_name_);
	is_equal = is_equal && (use_center_ != other.use_center_);
	is_equal = is_equal && (use_as_switch_ != other.use_as_switch_);
	is_equal = is_equal && (make_opaque_ != other.make_opaque_);
	return !is_equal;
}

void config_def::from_json(const json::Object& object)
{
}

#pragma endregion operators

