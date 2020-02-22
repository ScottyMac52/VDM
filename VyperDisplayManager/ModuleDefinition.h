#pragma once
class module_definition
{
public:
	module_definition();
	~module_definition();
	std::wstring get_name() const;
	std::wstring get_display_name() const;
	std::wstring get_file_path() const;
	std::wstring get_file_name() const;
	void add_configuration(const  configuration_definition& config);
	vector<configuration_definition> get_configurations() const;
	void json_save(const std::wstring json);
	void json_load(const std::wstring json);
	Json::Value to_json() const;
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
	vector<configuration_definition> configurations_;

};

