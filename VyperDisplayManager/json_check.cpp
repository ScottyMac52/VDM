#include "pch.h"
#include "globals.h"
#include "json_check.h"

using namespace std;
using namespace json;

#pragma region checks

json::Array json_check::to_json_array()
{
	return json::Array();
}

void json_check::from_json_array(const json::Array& array)
{
}

bool json_check::property_exists(const json::Object& object, const std::wstring& name)
{
	try
	{
		auto test = object[name];
		return true;
	}
	catch (...)
	{
	}
	return false;
}

#pragma endregion checks

#pragma region safe set_XXX by type

bool json_check::set_object_property(json::Object& object, const std::wstring& name, const std::wstring& value)
{
	const auto new_value = String(value);
	object[name] = new_value;
	return object[name] == new_value;
}

bool json_check::set_object_property(json::Object& object, const std::wstring& name, const bool& value)
{
	const auto new_value = Boolean(value);
	object[name] = new_value;
	return object[name] == new_value;
}

bool json_check::set_object_property(json::Object& object, const std::wstring& name, const double& value)
{
	const auto new_value = Number(value);
	object[name] = new_value;
	return object[name] == new_value;
}

bool json_check::set_object_property(json::Object& object, const std::wstring& name, const int& value)
{
	const auto new_value = Integer(value);
	object[name] = new_value;
	return object[name] == new_value;
}


#pragma endregion safe set_XXX by type
