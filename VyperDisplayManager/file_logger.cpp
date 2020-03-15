#include "pch.h"
#include "globals.h"
#include <cwchar>
#include <fstream>
#include "log_level.h"
#include "file_logger.h"

log_level file_logger::current_log_level_;

file_logger::file_logger(const std::wstring& full_path, const log_level desired_log_level)
{
	full_path_ = full_path;
	current_log_level_ = desired_log_level;
}

void file_logger::log_verbose(const std::wstring& log_entry)
{
	if(current_log_level_ != log_level::none)
	{
		add_log_entry(log_level::verbose, log_entry);
	}
}

void file_logger::log_info(const std::wstring& log_entry)
{
	if(current_log_level_ >= log_level::information)
	{
		add_log_entry(log_level::information, log_entry);
	}
}

void file_logger::log_debug(const std::wstring& log_entry)
{
	if (current_log_level_ >= log_level::debug)
	{
		add_log_entry(log_level::debug, log_entry);
	}
}

void file_logger::log_trace(const std::wstring& log_entry)
{
	if (current_log_level_ >= log_level::trace)
	{
		add_log_entry(log_level::trace, log_entry);
	}
}

void file_logger::log_warning(const std::wstring& log_entry)
{
	if (current_log_level_ != log_level::none)
	{
		add_log_entry(log_level::warning, log_entry);
	}
}

void file_logger::log_error(const std::wstring& log_entry)
{
	if (current_log_level_ != log_level::none)
	{
		add_log_entry(log_level::error, log_entry);
	}
}

void file_logger::log_critical(const std::wstring& log_entry)
{
	add_log_entry(log_level::critical, log_entry);
}

void file_logger::set_log_level(log_level log_level)
{
	current_log_level_ = log_level;
}

void file_logger::add_log_entry(const log_level level, const std::wstring& log_message)
{
	file_.open(full_path_.c_str(), std::ios_base::app);
	add_date_time_stamp();
	file_  << L" :" << level << L"-> " << log_message << std::endl;
	file_.close();
}


void file_logger::add_date_time_stamp()
{
	wchar_t buffer[256];
	tm ti;
	time_t tt;
	time(&tt);
	auto error_no = localtime_s(&ti, &tt);
	wcsftime(buffer, sizeof buffer * 2, L"%A %c", &ti);
	file_ << buffer;
}
