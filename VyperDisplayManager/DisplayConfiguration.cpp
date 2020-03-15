#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include "ModuleDefinition.h"
#include "DisplayConfiguration.h"

using namespace std;
using namespace json;

std::wstring display_configuration::get_name() const
{
	return name_;
}

json::Object display_configuration::to_json_object() const
{
	auto object = offset_geometry::to_json_object();
	set_object_property(object, L"name", name_);
	return object;
}

void display_configuration::from_json_object(const json::Object& object)
{
	offset_geometry::from_json_object(object);
	if(property_exists(object, L"name"))
	{
		name_ = String(object[L"name"]).Value();
	}
}

list<display_configuration> display_configuration::from_json(std::wstringstream& stream) const
{
	list<display_configuration> display_list;
	Object this_module_list;
	module_definition def;
	Array modules;

	const auto str = stream.str();
	const auto find_string = L"displays";
	const auto size = str.find(find_string);
	const auto first_bracket = str.find_first_of(L'[');
	const auto has_modules = size != std::string::npos;
	const auto has_multiple = first_bracket == 0;

	if (has_modules)
	{
		Reader::Read(this_module_list, stream);
		modules = this_module_list[find_string];
	}
	else if (has_multiple)
	{
		Reader::Read(modules, stream);
	}
	else
	{
		Object module;
		Reader::Read(module, stream);
		modules.Insert(module);
	}

	auto it = modules.begin();
	while(it!=modules.end())
	{
		json::Object current_display = *it;
		display_configuration display_config;
		display_config.from_json_object(current_display);
		display_list.push_back(display_config);
		++it;
	}
	
	return display_list;
}

display_configuration& display_configuration::operator=(const json::Object& object)
{
	if (json_check::property_exists(object, L"name"))
	{
		name_ = String(object[L"name"]).Value();
	}
	offset_geometry::from_json_object(object);
	return *this;
}
