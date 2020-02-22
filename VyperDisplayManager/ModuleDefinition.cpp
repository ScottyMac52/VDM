#include "pch.h"
#include "globals.h"
#include  <map>
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ConfigurationDefinition.h"
#include "ModuleDefinition.h"

using namespace std;

module_definition::module_definition()
= default;

module_definition::~module_definition()
= default;

std::wstring module_definition::get_name() const
{
	return name_;
}

std::wstring module_definition::get_display_name() const
{
	return display_name_;
}

std::wstring module_definition::get_file_path() const
{
	return file_path_;
}

std::wstring module_definition::get_file_name() const
{
	return file_name_;
}

Json::Value module_definition::to_json() const
{
	Json::Value value(Json::objectValue);
	value["name"] = name_.c_str();
	value["displayName"] = display_name_.c_str();
	value["filePath"] = file_path_.c_str();
	value["fileName"] = file_name_.c_str();

	// TODO: Add processing for ConfigurationDefinition vector

	return value;
}

void module_definition::add_configuration(const configuration_definition& config)
{
	// TODO: add the pre-processing code for the configuration

	configurations_.push_back(config);
}

vector<configuration_definition> module_definition::get_configurations() const
{
	return configurations_;
}

void module_definition::json_save(const std::wstring json)
{
}

void module_definition::json_load(const std::wstring json)
{
	
}
