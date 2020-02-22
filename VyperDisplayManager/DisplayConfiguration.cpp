#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "DisplayConfiguration.h"

std::wstring display_configuration::get_name() const
{
	return name_;
}

Json::Value display_configuration::to_json() const
{
	Json::Value value(Json::objectValue);
	value["name"] = name_.c_str();
	value["opacity"] = get_opacity();
	value["left"] = 0;
	value["top"] = 0;
	value["width"] = get_width();
	value["height"] = get_height();
	value["useAsSwitch"] = get_use_as_switch();
	value["center"] = get_center();
	value["offsets"] = get_cropping_area().to_json();
	return value;
}

void display_configuration::json_save(const std::wstring json)
{
	std::wostringstream oss;
	oss << json;
	auto buffer = oss.str();
}

void display_configuration::json_load(const std::wstring json)
{
}
