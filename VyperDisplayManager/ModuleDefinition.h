#pragma once
class module_definition :
	public json_check
{
public:
	module_definition();
	~module_definition();
	module_definition(const module_definition& source);
	module_definition(module_definition&& source) noexcept;  // NOLINT(bugprone-exception-escape)
	[[nodiscard]] std::wstring get_name() const;
	[[nodiscard]] std::wstring get_display_name() const;
	[[nodiscard]] std::wstring get_file_path() const;
	[[nodiscard]] std::wstring get_file_name() const;

	void set_name(const std::wstring& name);

	void set_display_name(const std::wstring& display_name);

	void set_file_path(const std::wstring& file_path);

	void set_file_name(const std::wstring& file_name);
	[[nodiscard]] bool is_empty() const;
	bool from_json(std::wstringstream& stream);

	[[nodiscard]] std::wstringstream to_json() const;
	[[nodiscard]] json::Object to_json_object() const override;
	void from_json_object(const json::Object& object) override;
	module_definition& operator=(const module_definition& other);
	module_definition& operator=(module_definition&& other);
	module_definition& operator=(const json::Object& object);
	bool operator==(const module_definition& other) const;
	bool operator!=(const module_definition& other) const;
	static bool are_configurations_equal(const std::list<configuration_definition>& list_a,
	                                     const std::list<configuration_definition>& list_b);
	list<configuration_definition> get_configurations() const;
	bool add_configuration(const configuration_definition& config);
protected:
private:
	/// <summary>
	/// Name of the Module
	/// </summary>
	std::wstring name_;
	/// <summary>
	/// Display name of the Module	/
	/// </summary>
	std::wstring display_name_;
	/// <summary>
	/// File path that the Module uses by default
	/// </summary>
	std::wstring file_path_;
	/// <summary>
	/// Filename that the Module uses by default
	/// </summary>
	std::wstring file_name_;
	/// <summary>
	/// List of Configurations for the Module
	/// </summary>
	list<configuration_definition> configurations_;

};

