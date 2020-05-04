#pragma once

class file_logger
{
public:
	/// <summary>
	/// Ctor
	/// </summary>
	/// <param name="full_path"></param>
	/// <param name="desired_log_level"></param>
	explicit file_logger(const std::wstring& full_path, log_level desired_log_level = log_level::information);
	void log_verbose(const std::wstring& log_entry);
	void log_info(const std::wstring& log_entry);
	void log_debug(const std::wstring& log_entry);
	void log_trace(const std::wstring& log_entry);
	void log_warning(const std::wstring& log_entry);
	void log_error(const std::wstring& log_entry);
	void log_critical(const std::wstring& log_entry);
	static void set_log_level(log_level log_level);
protected:
	void add_log_entry(log_level level, const std::wstring& log_message);
private:
	void add_date_time_stamp();
	std::wofstream file_;
	static log_level current_log_level_;
	std::wstring full_path_;
};

