#pragma once
class display_list :
	public json_check
{
public:
	display_list();
	display_list(const display_list& source);
	display_list(display_list&& source) noexcept;
	~display_list();
	/// <summary>
	/// read the content from a file
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	class display_list& from_file(const std::wstring& path);
	/// <summary>
	/// read the json object into a framework object
	/// </summary>
	/// <param name="stream"></param>
	/// <returns></returns>
	display_list& from_json(std::wstringstream& stream);
	/// <summary>
	/// write the content to a file
	/// </summary>
	/// <param name="file_name"></param>
	/// <returns></returns>
	bool to_file(const std::wstring& file_name) const;
	bool displays_from_file(const std::wstring& path);
	/// <summary>
	/// Array index operator returns modules by name
	/// </summary>
	/// <param name="name_key"></param>
	/// <returns></returns>
	display_configuration operator[](const std::wstring& name_key);
	/// <summary>
	/// >> operator is used to fill a json::Array from a module list
	/// </summary>
	friend json::Array& operator>>(const display_list& list, json::Array& array);
	/// <summary>
	/// operator << copies array as list of module_def into the current object
	/// </summary>
	/// <param name="array">json::Array&</param>
	/// <returns></returns>
	display_list& operator<<(const json::Array& array);
	/// <summary>
	/// operator << copies the object into the current list as an module_def
	/// </summary>
	/// <param name="object">json::Object</param>
	/// <returns></returns>
	display_list& operator<<(const json::Object& object);
	/// <summary>
	/// loads a display list from a json Object
	/// </summary>
	/// <param name="object"></param>
	void from_json_object(const json::Object& object) override;
	/// <summary>
	/// creates a json Object from the current display list
	/// </summary>
	/// <returns></returns>
	virtual json::Array to_json_array() override;
	virtual void from_json_array(const json::Array& array) override;
	[[nodiscard]] virtual json::Object to_json_object() const override;
	bool find_partial_match(const wstring& partial_key, display_configuration& current_display);
private:
	std::list<display_configuration> displays_;
};

