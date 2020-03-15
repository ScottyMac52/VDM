#pragma once

// class json_check;

/**
 * \brief 
 */
class config_def :
	public json_check
	
{
public:
	config_def();
	config_def(const config_def& source);
	config_def(config_def&& source) noexcept;
	~config_def();
	[[nodiscard]] std::wstring get_name() const;
	[[nodiscard]] std::wstring get_module_name() const;
	[[nodiscard]] std::wstring get_file_name() const;
	[[nodiscard]] std::wstring get_file_path() const;
	[[nodiscard]] std::wstring get_full_path() const;
	[[nodiscard]] bool get_enabled() const;
	[[nodiscard]] bool get_use_as_switch() const;
	[[nodiscard]] bool get_make_opaque() const;
	[[nodiscard]] bool get_use_center() const;
	
	void set_name(const std::wstring& name);
	void set_module_name(const std::wstring& name);
	void set_file_path(const std::wstring& path);
	void set_file_name(const std::wstring& file_name);
	void set_enabled(const bool enable);
	void set_use_as_switch(const bool use_switch);
	void set_make_opaque(const bool is_opaque);
	void set_use_center(const bool use_center);

	[[nodiscard]] json::Object to_json_object() const;
	
	config_def& operator=(const config_def& source);
	config_def& operator=(const json::Object object);
	bool operator==(const config_def& other) const;
	bool operator!=(const config_def& other) const;

	void from_json(const json::Object& object) override;
private:
	std::wstring module_name_;
	std::wstring name_;
	std::wstring file_name_;
	std::wstring file_path_;
	std::wstring throttle_type_;
	std::wstring ruler_name_;
	bool enabled_ = false;
	bool use_as_switch_ = false;
	bool make_opaque_ = false;
	bool use_center_ = false;
};

