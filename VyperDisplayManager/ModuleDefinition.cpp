#include "pch.h"
#include "globals.h"
#include  <map>
#include <fstream>
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include "log_level.h"
#include "file_logger.h"
#include "ModuleDefinition.h"

using namespace std;
using namespace json;

module_definition::module_definition()
= default;

module_definition::~module_definition()
= default;

module_definition::module_definition(const module_definition & source)
{
	name_ = source.name_;
	display_name_ = source.display_name_;
	file_path_ = source.file_path_;
	file_name_ = source.file_name_;

	for (auto it = source.configurations_.begin(); it != source.configurations_.end(); ++it)
	{
		auto config = *it;

		if (config.get_file_path().empty() && !file_path_.empty())
		{
			config.set_file_path(file_path_);
		}
		if (config.get_file_name().empty() && !file_name_.empty())
		{
			config.set_file_name(file_name_);
		}
		config.set_module_name(name_);

		add_configuration(config);
	}
}

module_definition::module_definition(module_definition&& source) noexcept  // NOLINT(bugprone-exception-escape)
{
	*this = std::move(source);
}

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

void module_definition::set_name(const std::wstring& name)
{
	name_ = name;
}

void module_definition::set_display_name(const std::wstring& display_name)
{
	display_name_ = display_name;
}

void module_definition::set_file_path(const std::wstring& file_path)
{
	file_path_ = file_path;
}

void module_definition::set_file_name(const std::wstring& file_name)
{
	file_name_ = file_name;
}

#pragma region atomic

bool module_definition::is_empty() const
{
	return name_.empty();
}

#pragma endregion atomic


#pragma region JSON

bool module_definition::from_json(std::wstringstream& stream)
{
	Object this_module;
	module_definition def;
	auto string_version = stream.str();
	Reader::Read(this_module, stream);
	auto modules = this_module[L"modules"];
	auto module = modules[0];
	def = module;
	*this = def;
	return *this == def;
}

std::wstringstream module_definition::to_json() const
{
	Object obj_document;
	Array module_array;

	std::wstringstream string_stream;
	const auto json_module = to_json_object();
	module_array.Insert(json_module);
	obj_document[L"modules"] = module_array;
	Writer::Write(obj_document, string_stream);
	auto json_string = string_stream.str();
	return string_stream;
}

void module_definition::from_json_object(const json::Object& object)
{
	if(property_exists(object, L"name"))
	{
		name_ = String(object[L"name"]).Value();
	}

	if (property_exists(object, L"displayName"))
	{
		display_name_ = String(object[L"displayName"]).Value();
	}

	if (property_exists(object, L"filePath"))
	{
		file_path_ = String(object[L"filePath"]).Value();
	}

	if (property_exists(object, L"fileName"))
	{
		file_name_ = String(object[L"fileName"]).Value();
	}
}

json::Object module_definition::to_json_object() const
{
	json::Object object;

	set_object_property(object, L"name", name_);
	set_object_property(object, L"displayName", display_name_);
	set_object_property(object, L"filePath", file_path_);
	set_object_property(object, L"fileName", file_name_);

	Array configuration_definitions;
	for (auto it = configurations_.begin(); it != configurations_.end(); ++it)
	{
		configuration_definitions.Insert(it->to_json_object());
	}

	// add the list of configurations
	object[L"configurations"] = configuration_definitions;
	return object;
}

#pragma endregion JSON


#pragma region operators

module_definition& module_definition::operator=(const module_definition& other)
{
	name_ = other.name_;
	display_name_ = other.display_name_;
	file_path_ = other.file_path_;
	file_name_ = other.file_name_;

	for (auto it = other.configurations_.begin(); it != other.configurations_.end(); ++it)
	{
		add_configuration(*it);
	}

	return *this;
}


module_definition& module_definition::operator=(module_definition&& other) 
{
	name_ = other.name_;
	display_name_ = other.display_name_;
	file_path_ = other.file_path_;
	file_name_ = other.file_name_;

	for (auto it = configurations_.begin(); it != configurations_.end(); ++it)
	{
		add_configuration(*it);
	}

	return *this;
}

module_definition& module_definition::operator=(const json::Object& object)
{
	if (json_check::property_exists(object, L"name"))
	{
		set_name(String(object[L"name"]));
	}

	if (json_check::property_exists(object, L"displayName"))
	{
		set_display_name(String(object[L"displayName"]));
	}

	if (json_check::property_exists(object, L"filePath"))
	{
		set_file_path(String(object[L"filePath"]));
	}

	if (json_check::property_exists(object, L"fileName"))
	{
		set_file_name(String(object[L"fileName"]));
	}

	if (json_check::property_exists(object, L"configurations"))
	{
		Array configurations = object[L"configurations"];
		for (auto it = configurations.begin(); it != configurations.end(); ++it)
		{
			Object& member = *it;
			configuration_definition def;
			def = member;
			add_configuration(def);
		}
	}

	return *this;
}

bool module_definition::operator==(const module_definition& other) const
{
	if (name_ != other.name_)
		return false;

	if (display_name_ != other.display_name_)
		return false;

	if (file_path_ != other.file_path_)
		return false;

	if (file_name_ != other.file_name_)
		return false;

	if (configurations_.size() != other.configurations_.size())
		return false;

	if (configurations_.empty() && other.configurations_.empty())
		return true;

	const auto is_same = are_configurations_equal(configurations_, other.configurations_);

	return is_same;
}

bool module_definition::operator!=(const module_definition& other) const
{
	auto is_equal = name_ == other.name_;
	is_equal = is_equal && (file_path_ != other.file_path_);
	is_equal = is_equal && (file_name_ != other.file_name_);
	is_equal = is_equal && (display_name_ != other.display_name_);

	const auto is_same = are_configurations_equal(configurations_, other.configurations_);

	return  !(is_equal && is_same);
}

wostream& operator<<(wostream& output, const module_definition& def)
{
	output << def.to_json().str();
	return output;
}

#pragma endregion operators 

#pragma region configuration management

bool module_definition::add_configuration(const configuration_definition& config)
{
	const auto size = configurations_.size();
	configurations_.push_back(config);
	return configurations_.size() == size + 1;
}

bool module_definition::are_configurations_equal(const std::list<configuration_definition>& list_a, const std::list<configuration_definition>& list_b)
{
	auto found = false;
	auto it = list_a.begin();
	while (it != list_a.end())
	{
		found = false;
		auto it_inner = list_b.begin();
		while (it_inner != list_b.end())
		{
			const auto other_config = static_cast<configuration_definition>(*it_inner);
			const auto outer = static_cast<configuration_definition>(*it);
			if (outer == other_config)
			{
				found = true;
				break;
			}
			++it_inner;
		}
		++it;
	}
	return found;
}

list<configuration_definition> module_definition::get_configurations() const
{
	return configurations_;
}

#pragma endregion configuration management





