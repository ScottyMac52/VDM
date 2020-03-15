#include "pch.h"
#include "pch.h"
#include "globals.h"
#include <string>
#include <fstream>
#include "json_check.h"
#include "Location.h"
#include "area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include "ModuleDefinition.h"
#include "DisplayConfiguration.h"
#include "display_list.h"

using namespace std;
using namespace json;

#pragma region ctor and dtor


display_list::display_list()
= default;

display_list::display_list(const display_list& source)
{
	displays_.clear();
	auto it = displays_.begin();
	while(it!=displays_.end())
	{
		displays_.push_back(*it);
		++it;
	}
}

display_list::display_list(display_list&& source) noexcept
{
	std::move(source);
}

display_list::~display_list()
= default;

#pragma endregion ctor and dtor

#pragma region file

display_list& display_list::from_file(const std::wstring& path)
{
	std::wifstream in_file;
	std::wstringstream w_string_stream;

	in_file.open(path, std::wifstream::in);
	if (in_file.is_open())
	{
		w_string_stream << in_file.rdbuf();
		in_file.close();
	}
	from_json(w_string_stream);

	return *this;
}

bool display_list::to_file(const std::wstring& file_name) const
{
	std::wofstream out_file;
	std::wstringstream w_string_stream;

	out_file.open(file_name, ios_base::out);
	if (out_file.is_open())
	{
		const auto object_list = to_json_object();
		Writer::Write(object_list, out_file);
		out_file.close();
	}
	return true;
}

bool display_list::displays_from_file(const std::wstring& path)
{
	std::wifstream in_file;
	std::wstringstream w_string_stream;
	list<display_configuration> display_list;

	in_file.open(path, std::wifstream::in);
	if (in_file.is_open())
	{
		w_string_stream << in_file.rdbuf();
		in_file.close();
	}

	Object this_module_list;
	display_configuration def;
	Array modules;

	const auto str = w_string_stream.str();
	const auto find_string = L"displays";
	const auto size = str.find(find_string);
	const auto first_bracket = str.find_first_of(L'[');
	const auto has_modules = size != std::string::npos;
	const auto has_multiple = first_bracket == 0;

	if (has_modules)
	{
		Reader::Read(this_module_list, w_string_stream);
		modules = this_module_list[find_string];
	}
	else if (has_multiple)
	{
		Reader::Read(modules, w_string_stream);
	}
	else
	{
		Object module;
		Reader::Read(module, w_string_stream);
		modules.Insert(module);
	}

	auto it = modules.begin();
	while (it != modules.end())
	{
		json::Object current_display = *it;
		display_configuration display_config;
		display_config.from_json_object(current_display);
		displays_.push_back(display_config);
		++it;
	}
	return true;
 }


#pragma endregion file

#pragma region json

display_list& display_list::from_json(std::wstringstream& stream)
{
	Object object;
	display_configuration display_config;
	Array displays;

	const auto str = stream.str();
	const auto find_string = L"displays";
	const auto size = str.find(find_string);
	const auto first_bracket = str.find_first_of(L'[');
	const auto has_modules = size != std::string::npos;
	const auto has_multiple = first_bracket == 0;

	if (has_modules)
	{
		Reader::Read(object, stream);
		displays = object[find_string];
	}
	else if (has_multiple)
	{
		Reader::Read(displays, stream);
	}
	else
	{
		Object module;
		Reader::Read(module, stream);
		displays.Insert(module);
	}

	displays_.clear();
	*this << displays;
	return *this;
}

json::Array display_list::to_json_array()
{
	json::Array array;
	*this >> array;
	return array;
}

void display_list::from_json_array(const json::Array& array)
{
	*this << array;
}


void display_list::from_json_object(const json::Object& object)
{
}

json::Object display_list::to_json_object() const
{
	return json::Object();
}

bool display_list::find_partial_match(const wstring& partial_key, display_configuration& current_display)
{
	auto found = false;
	auto it = displays_.begin();
	while (it != displays_.end())
	{
		auto current_display_name = it->get_name();
		if (partial_key.find(current_display_name) != std::wstring::npos)
		{
			current_display = *it;
			found = true;
			break;
		}
		++it;
	}
	
	return found;
}

#pragma endregion json

#pragma region operators

display_configuration display_list::operator[](const std::wstring& name_key)
{
	auto it = displays_.begin();
	while (it != displays_.end())
	{
		if (it->get_name() == name_key)
		{
			return *it;
		}
		++it;
	}
	auto def = display_configuration();
	return def;
}

display_list& display_list::operator<<(const json::Array& array)
{
	auto it = array.begin();
	while (it != array.end())
	{
		*this << static_cast<json::Object>(*it);
		++it;
	}
	return *this;
}

display_list& display_list::operator<<(const json::Object& object)
{
	display_configuration config;
	config = object;
	displays_.push_back(config);
	return *this;
}

json::Array& operator>>(const display_list& list, json::Array& array)
{
	auto it = list.displays_.begin();
	while (it != list.displays_.end())
	{
		array.Insert(static_cast<display_configuration>(*it).to_json_object());
		++it;
	}
	return array;
}

#pragma endregion operators
