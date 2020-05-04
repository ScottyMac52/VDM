#pragma once

class json_check
{
public:
	json_check() = default;
	virtual ~json_check() = default;
	/// <summary>
	/// Pure virtual to_json_object() makes class abstract
	/// </summary>
	/// <returns>json::Object of the current class</returns>
	[[nodiscard]] virtual json::Object to_json_object() const = 0;
	/// <summary>
	/// pure virtual from_json_object() makes class abstract
	/// </summary>
	/// <param name="object"></param>
	virtual void from_json_object(const json::Object& object) = 0;
	/// <summary>
	/// can be overriden to return a json Array, default returns an empty one
	/// </summary>
	/// <returns></returns>
	virtual json::Array to_json_array();
	/// <summary>
	/// Can be overridden to set vales from a json Array, default is NoOp
	/// </summary>
	/// <param name="array"></param>
	virtual void from_json_array(const json::Array& array);
	/// <summary>
	/// Checks to see if named property exists in json Object
	/// </summary>
	/// <param name="object"></param>
	/// <param name="name"></param>
	/// <returns></returns>
	static bool property_exists(const json::Object& object, const std::wstring& name);
	/// <summary>
	/// Sets a string value property safely
	/// </summary>
	/// <param name="object"></param>
	/// <param name="name"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	static bool set_object_property(json::Object& object, const std::wstring& name, const std::wstring& value);
	/// <summary>
	/// Sets a bool value property safely
	/// </summary>
	/// <param name="object"></param>
	/// <param name="name"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	static bool set_object_property(json::Object& object, const std::wstring& name, const bool& value);
	/// <summary>
	/// Sets a double value property safely
	/// </summary>
	/// <param name="object"></param>
	/// <param name="name"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	static bool set_object_property(json::Object& object, const std::wstring& name, const double& value);
	/// <summary>
	/// Sets an int value property safely
	/// </summary>
	/// <param name="object"></param>
	/// <param name="name"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	static bool set_object_property(json::Object& object, const std::wstring& name, const int& value);
};

