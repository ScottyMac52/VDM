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
#include "DisplayConfiguration.h"
#include "ModuleDefinition.h"
#include "module_list.h"

using namespace std;
using namespace json;

#pragma region ctor and dtor

module_list::module_list()
= default;

module_list::module_list(const module_list & source)
{
	modules_.clear();
	for (auto it = source.modules_.begin(); it != source.modules_.end(); ++it)
	{
		modules_.push_back(*it);
	}
}

module_list::module_list(module_list && source) noexcept
{
	std::move(source);  // NOLINT(clang-diagnostic-unused-result)
}

module_list::~module_list()
= default;

#pragma endregion ctor and dtor

#pragma region file

module_list& module_list::from_file(const std::wstring& path)
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



bool module_list::to_file(const std::wstring& file_name) const
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

#pragma endregion file

#pragma region json

module_list& module_list::from_json(std::wstringstream& stream)
{
	Object this_module_list;
	module_definition def;
	Array modules;

	const auto str = stream.str();
	const auto find_string = L"modules";
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

	modules_.clear();
	*this << modules;
	return *this;
}

json::Array module_list::to_json_object() const
{
	json::Array array;
	*this >> array;
	return array;
}

#pragma endregion json

#pragma region operator

module_definition module_list::operator[](const std::wstring& name_key)
{
	auto it = modules_.begin();
	while (it != modules_.end())
	{
		if (it->get_name() == name_key)
		{
			return *it;
		}
		++it;
	}
	auto def = module_definition();
	return def;
}

module_list& module_list::operator<<(const json::Array& array)
{
	auto it = array.begin();
	while (it != array.end())
	{
		*this << static_cast<json::Object>(*it);
		++it;
	}
	return *this;
}

module_list& module_list::operator<<(const json::Object& object)
{
	module_definition def;
	def = object;
	modules_.push_back(def);
	return *this;
}

json::Array& operator>>(const module_list& list, json::Array& array)
{
	auto it = list.modules_.begin();
	while (it != list.modules_.end())
	{
		array.Insert(static_cast<module_definition>(*it).to_json_object());
		++it;
	}
	return array;
}

#pragma endregion operator