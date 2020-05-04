#pragma once

class app_settings :
	public json_check
{
public:
	~app_settings() = default;

	static app_settings& get_instance()
	{
		static app_settings instance;
		//instance.from_file(L"appsettings.json");
		return instance;
	}
	
	app_settings(const app_settings& copy);
	void operator=(app_settings const&) = delete;
	[[nodiscard]] json::Object to_json_object() const override;
	app_settings& operator<<(const json::Object& object);
	void from_json_object(const json::Object& object) override;
	/// <summary>
	/// read the content from a file
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	app_settings& from_file(const std::wstring& path);
	/// <summary>
	/// write the content to a file
	/// </summary>
	/// <param name="file_name"></param>
	/// <returns></returns>
	bool to_file(const std::wstring& file_name) const;
	static std::wstring get_file_path() { return file_path_; }
	static std::wstring get_display_file_name() { return display_config_file_; }
	static bool show_configuration_menu() { return show_configuration_menu_; }
	static bool show_rulers() { return show_rulers_; }
	static int get_ruler_size() { return ruler_size_; }
	static int get_ruler_major_width() { return ruler_major_width_; }
	static int get_ruler_minor_width() { return ruler_minor_width_; }
private:
	static std::wstring display_config_file_;
	static bool save_cropped_images_;
	static bool show_tool_tips_;
	static bool show_rulers_;
	static int ruler_size_;
	static int ruler_major_width_;
	static int ruler_minor_width_;
	static std::wstring file_path_;
	static std::wstring file_spec_;
	static bool use_cougar_;
	static bool turn_off_cache_;
	static bool show_configuration_menu_;
	app_settings() = default;
};

