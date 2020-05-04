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
	display_list_.Clear();
	auto it = display_list_.begin();
	while (it != display_list_.end())
	{
		display_list_.Insert(*it);
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
		Object this_module_list;
		display_configuration def;
		Array displays;

		const auto str = w_string_stream.str();
		const auto find_string = L"displays";
		const auto size = str.find(find_string);
		const auto first_bracket = str.find_first_of(L'[');
		const auto has_modules = size != std::string::npos;
		const auto has_multiple = first_bracket == 0;

		if (has_modules)
		{
			Reader::Read(this_module_list, w_string_stream);
			displays = this_module_list[find_string];
		}
		else if (has_multiple)
		{
			Reader::Read(displays, w_string_stream);
		}
		else
		{
			Object module;
			Reader::Read(module, w_string_stream);
			displays.Insert(module);
		}

		display_list_.Clear();
		display_list_ = displays;
		return true;
	}
	return false;
 }


#pragma endregion file

#pragma region json

display_list& display_list::from_json(std::wstringstream& stream)
{
	Object object;
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

	display_list_.Clear();
	display_list_ = displays;
	return *this;
}

void display_list::from_json_object(const json::Object& object)
{
}

json::Object display_list::to_json_object() const
{
	return json::Object();
}

bool display_list::find_partial_match(const wstring& partial_key, json::Object& current_display)
{
	auto found = false;
	auto it = display_list_.begin();
	while (it != display_list_.end())
	{
		if (property_exists(*it, L"key"))
		{
			auto current_display_name = String((*it)[L"key"]);
			if (partial_key.find(current_display_name) != std::wstring::npos)
			{
				current_display = *it;
				found = true;
				break;
			}
			++it;
		}
	}
	
	return found;
}

#pragma endregion json

