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
	/// loads a display list from a json Object
	/// </summary>
	/// <param name="object"></param>
	void from_json_object(const json::Object& object) override;
	/// <summary>
	/// creates a json Object from the current display list
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] virtual json::Object to_json_object() const override;
	bool find_partial_match(const wstring& partial_key, json::Object& current_display);
private:
	json::Array display_list_;
};

