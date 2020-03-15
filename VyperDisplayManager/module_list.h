#pragma once

class module_list
{
public:
	module_list();
	module_list(const module_list& source);
	module_list(module_list&& source) noexcept;
	~module_list();
	/// <summary>
	/// read the content from a file
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	module_list& from_file(const std::wstring& path);
	/// <summary>
	/// read the json object into a framework object
	/// </summary>
	/// <param name="stream"></param>
	/// <returns></returns>
	module_list& from_json(std::wstringstream& stream);
	/// <summary>
	/// write the content to a file
	/// </summary>
	/// <param name="file_name"></param>
	/// <returns></returns>
	bool to_file(const std::wstring& file_name) const;
	/// <summary>
	/// convert the list to a json array object
	/// </summary>
	/// <returns></returns>
	json::Array to_json_object() const;
	/// <summary>
	/// Array index operator returns modules by name
	/// </summary>
	/// <param name="name_key"></param>
	/// <returns></returns>
	module_definition operator[](const std::wstring& name_key);
	/// <summary>
	/// >> operator is used to fill a json::Array from a module list
	/// </summary>
	friend json::Array& operator>>(const module_list& list, json::Array& array);
	/// <summary>
	/// operator << copies array as list of module_def into the current object
	/// </summary>
	/// <param name="array">json::Array&</param>
	/// <returns></returns>
	module_list& operator<<(const json::Array& array);
	/// <summary>
	/// operator << copies the object into the current list as an module_def
	/// </summary>
	/// <param name="object">json::Object</param>
	/// <returns></returns>
	module_list& operator<<(const json::Object& object);
private:
	std::list<module_definition> modules_;
};


