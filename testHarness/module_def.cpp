#include <list>
#include <string>
#include "cajun/json/writer.h"
#include "cajun/json/elements.h"
#include <sstream>
#include "json_check.h"
#include "config_def.h"
#include "module_def.h"

#include <fstream>

using namespace std;
using namespace json;

#pragma region Ctor and Dtor

module_def::module_def()
= default;

module_def::module_def(const module_def& source)
{
	name_ = source.name_;
	display_name_ = source.display_name_;
	file_path_ = source.file_path_;
	file_name_ = source.file_name_;

	for (auto it = source.configuration_list_.begin(); it != source.configuration_list_.end(); ++it)
	{
		auto config = *it;

		if (config.get_file_path().empty() && !file_path_.empty())
		{
			config.set_file_path(file_path_);
		}
		if(config.get_file_name().empty() && !file_name_.empty())
		{
			config.set_file_name(file_name_);
		}
		config.set_module_name(name_);
		
		add_configuration(config);
	}
}

module_def::module_def(module_def&& source) noexcept  // NOLINT(bugprone-exception-escape)
{
	*this = std::move(source);
}

module_def::~module_def()
= default;

#pragma endregion Ctor and Dtor

#pragma region get_XXX

std::wstring module_def::get_name() const
{
	return name_;
}

std::wstring module_def::get_display_name() const
{
	return display_name_;
}

std::wstring module_def::get_file_path() const
{
	return file_path_;
}

std::wstring module_def::get_file_name() const
{
	return file_name_;
}

#pragma endregion get_XXX

#pragma region set_XXX

void module_def::set_name(const std::wstring& name)
{
	name_ = name;
}

void module_def::set_display_name(const std::wstring& display_name)
{
	display_name_ = display_name;
}

void module_def::set_file_path(const std::wstring& file_path)
{
	file_path_ = file_path;
}

void module_def::set_file_name(const std::wstring& file_name)
{
	file_name_ = file_name;
}

#pragma endregion set_XXX

#pragma region JSON

bool module_def::from_json(std::wstringstream& stream)
{
	Object this_module;
	module_def def;
	auto string_version = stream.str();
	Reader::Read(this_module, stream);
	auto modules = this_module[L"modules"];
	auto module = modules[0];
	def = module;
	*this = def;
	return *this == def;
}

std::wstringstream module_def::to_json() const
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

void module_def::from_json(const json::Object& object)
{
}

json::Object module_def::to_json_object() const
{
	Object json_module;

	json_module[L"name"] = String(name_);
	json_module[L"displayName"] = String(display_name_);
	json_module[L"filePath"] = String(file_path_);
	json_module[L"fileName"] = String(file_name_);

	Array configuration_defs;
	for (auto it = configuration_list_.begin(); it != configuration_list_.end(); ++it)
	{
		configuration_defs.Insert(it->to_json_object());
	}

	// add the list of configurations
	json_module[L"configurations"] = configuration_defs;
	return json_module;
}

#pragma endregion JSON

#pragma region atomic

bool module_def::is_empty() const
{
	return name_.empty();
}

#pragma endregion atomic

#pragma region operators

module_def& module_def::operator=(const module_def& other)
{
	name_ = other.name_;
	display_name_ = other.display_name_;
	file_path_ = other.file_path_;
	file_name_ = other.file_name_;

	for (auto it = other.configuration_list_.begin(); it != other.configuration_list_.end(); ++it)
	{
		add_configuration(*it);
	}

	return *this;
}


module_def& module_def::operator=(module_def && other) noexcept
{
	name_ = other.name_;
	display_name_ = other.display_name_;
	file_path_ = other.file_path_;
	file_name_ = other.file_name_;

	for (auto it = configuration_list_.begin(); it != configuration_list_.end(); ++it)
	{
		add_configuration(*it);
	}

	return *this;
}

module_def& module_def::operator=(json::Object object)
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
			config_def def;
			def = member;
			add_configuration(def);
		}
	}

	return *this;
}

bool module_def::operator==(const module_def& other) const
{
	if (name_ != other.name_)
		return false;

	if (display_name_ != other.display_name_)
		return false;

	if (file_path_ != other.file_path_)
		return false;

	if (file_name_ != other.file_name_)
		return false;

	if (configuration_list_.size() != other.configuration_list_.size())
		return false;

	if (configuration_list_.empty() && other.configuration_list_.empty())
		return true;

	const auto is_same = are_configurations_equal(configuration_list_, other.configuration_list_);

	return is_same;
}

bool module_def::operator!=(const module_def& other) const
{
	auto is_equal = name_ == other.name_;
	is_equal = is_equal && (file_path_ != other.file_path_);
	is_equal = is_equal && (file_name_ != other.file_name_);
	is_equal = is_equal && (display_name_ != other.display_name_);

	const auto is_same = are_configurations_equal(configuration_list_, other.configuration_list_);

	return  !(is_equal && is_same);
}

wostream& operator<<(wostream& output, const module_def& def)
{
	output << def.to_json().str();
	return output;
}

#pragma endregion operators 

#pragma region configuration management

std::list<config_def> module_def::get_configurations() const
{
	return configuration_list_;
}

bool module_def::add_configuration(const config_def& config)
{
	const auto size = configuration_list_.size();
	configuration_list_.push_back(config);
	return configuration_list_.size() == size + 1;
}

bool module_def::are_configurations_equal(const std::list<config_def>& list_a, const std::list<config_def>& list_b)
{
	auto found = false;
	auto it = list_a.begin();
	while(it!=list_a.end())
	{
		found = false;
		auto it_inner = list_b.begin();
		while(it_inner!=list_b.end())
		{
			const auto other_config = static_cast<config_def>(*it_inner);
			const auto outer = static_cast<config_def>(*it);
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

#pragma endregion configuration management

