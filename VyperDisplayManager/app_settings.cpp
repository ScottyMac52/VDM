#include "pch.h"
#include "globals.h"
#include <fstream>
#include "json_check.h"
#include "app_settings.h"


using namespace std;
using namespace json;

app_settings::app_settings(const app_settings& copy)
{
}

json::Object app_settings::to_json_object() const
{
	json::Object json_module;
	set_object_property(json_module, L"DisplayConfigurationFile", display_config_file_);
	set_object_property(json_module, L"filePath", file_path_);
	set_object_property(json_module, L"SaveCroppedImages", save_cropped_images_);
	set_object_property(json_module, L"ShowTooltips", show_tool_tips_);
	set_object_property(json_module, L"ShowRulers", show_rulers_);
	set_object_property(json_module, L"RulerSize", ruler_size_);
	set_object_property(json_module, L"fileSpec", file_spec_);
	set_object_property(json_module, L"UseCougar", use_cougar_);
	set_object_property(json_module, L"TurnOffCache", turn_off_cache_);
	set_object_property(json_module, L"filePath", file_path_);
	return json_module;
}

app_settings& app_settings::operator<<(const json::Object& object)
{
	from_json_object(object);
	return *this;
}


void app_settings::from_json_object(const json::Object& object)
{
	display_config_file_ = L"displays.json";
	if (property_exists(object, L"DisplayConfigurationFile"))
	{
		display_config_file_ = String(object[L"DisplayConfigurationFile"]);
	}
	if (property_exists(object, L"filePath"))
	{
		file_path_ = String(object[L"filePath"]);
	}
	if (property_exists(object, L"SaveCroppedImages"))
	{
		save_cropped_images_ = Boolean(object[L"SaveCroppedImages"]);
	}
	if (property_exists(object, L"ShowTooltips"))
	{
		show_tool_tips_ = Boolean(object[L"ShowTooltips"]);
	}
	if (property_exists(object, L"ShowRulers"))
	{
		show_rulers_ = Boolean(object[L"ShowRulers"]);
	}
	if (property_exists(object, L"RulerSize"))
	{
		ruler_size_ = Integer(object[L"RulerSize"]);
	}
	if (property_exists(object, L"RulerMajorSize"))
	{
		ruler_major_width_ = Integer(object[L"RulerMajorSize"]);
	}
	if (property_exists(object, L"RulerMinorSize"))
	{
		ruler_minor_width_ = Integer(object[L"RulerMinorSize"]);
	}
	if (property_exists(object, L"fileSpec"))
	{
		file_spec_ = String(object[L"fileSpec"]);
	}
	if (property_exists(object, L"UseCougar"))
	{
		use_cougar_ = Boolean(object[L"UseCougar"]);
	}
	if (property_exists(object, L"TurnOffCache"))
	{
		turn_off_cache_ = Boolean(object[L"TurnOffCache"]);
	}
	if(property_exists(object, L"ShowConfigurationMenu"))
	{
		show_configuration_menu_ = Boolean(object[L"ShowConfigurationMenu"]);
	}
}

app_settings& app_settings::from_file(const std::wstring& path)
{
	std::wifstream in_file;
	std::wstringstream w_string_stream;

	in_file.open(path, std::wifstream::in);
	if (in_file.is_open())
	{
		w_string_stream << in_file.rdbuf();
		in_file.close();
	}

	Object settings;
	const auto str = w_string_stream.str();
	Reader::Read(settings, w_string_stream);
	*this << settings;
	return *this;
}

bool app_settings::to_file(const std::wstring& file_name) const
{
	return false;
}
