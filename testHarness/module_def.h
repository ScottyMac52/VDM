#pragma once

class json_check;

class config_def;
/**
 * Module definition file 
 */
class module_def : public json_check
{
public:
	/// <summary>
	/// default ctor
	/// </summary>
	module_def();
	/// <summary>
	/// copy ctor
	/// </summary>
	/// <param name="source"></param>
	module_def(const module_def& source);
	/// <summary>
	/// move ctor
	/// </summary>
	/// <param name="source"></param>
	/// <returns></returns>
	module_def(module_def&& source) noexcept;
	/// <summary>
	/// default destructor
	/// </summary>
	~module_def();

	// GETS
	/// <summary>
	/// get for name
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::wstring get_name() const;
	/// <summary>
	/// get for display name
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::wstring get_display_name() const;
	/// <summary>
	/// get for file path
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::wstring get_file_path() const;
	/// <summary>
	/// get for file name
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::wstring get_file_name() const;

	// SETS
	/// <summary>
	/// set for name
	/// </summary>
	/// <param name="name"></param>
	void set_name(const std::wstring& name);
	/// <summary>
	/// set for display name
	/// </summary>
	/// <param name="display_name"></param>
	void set_display_name(const std::wstring& display_name);
	/// <summary>
	/// set for file path
	/// </summary>
	/// <param name="file_path"></param>
	void set_file_path(const std::wstring& file_path);
	/// <summary>
	/// set for file name
	/// </summary>
	/// <param name="file_name"></param>
	void set_file_name(const std::wstring& file_name);

	// JSON methods
	[[nodiscard]] json::Object to_json_object() const;
//	json::Object to_json_object() const override;
//	void from_json(const json::Object& object) override;

	/// <summary>
	/// populate class from stream
	/// </summary>
	/// <param name="stream"></param>
	/// <returns></returns>
	bool from_json(std::wstringstream& stream);
	
	/// <summary>
	/// show class as json in string stream
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::wstringstream to_json() const;
	void from_json(const json::Object& object) override;
	
	/// <summary>
	/// name is the minimum required, otherwise the module_def is empty
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] bool is_empty() const;
	
	// Operators
	/// <summary>
	/// assignment operator
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	module_def& operator=(const module_def& other);
	/// <summary>
	/// move assignment operator
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	module_def& operator=(module_def&& other) noexcept;  // NOLINT(bugprone-exception-escape)
	/// <summary>
	/// allows assignment from a json::Object 
	/// </summary>
	/// <param name="object"></param>
	/// <returns></returns>
	module_def& operator=(json::Object object);
	/// <summary>
	/// equality operator
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator==(const module_def& other) const;
	/// <summary>
	/// non-equality operator
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator!=(const module_def& other) const;


	friend wostream& operator<<(wostream& output, const module_def& def);
	
	/// <summary>
	/// Gets the list of configurations for this module
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::list<config_def> get_configurations() const;
	/// <summary>
	/// adds a new config_def to the list
	/// </summary>
	/// <param name="config"></param>
	/// <returns></returns>
	bool add_configuration(const config_def& config);
protected:
	static bool are_configurations_equal(const std::list<config_def>& list_a, const std::list<config_def>& list_b);
private:
	std::wstring name_;
	std::wstring display_name_;
	std::wstring file_path_;
	std::wstring file_name_;
	std::list<config_def> configuration_list_;
	
};

