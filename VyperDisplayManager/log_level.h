#pragma once
enum class log_level
{
	none, verbose, information, debug, trace, warning, error, critical
};

/// <summary>
/// Overloaded << operator to provide wostream output of log_level
/// </summary>
/// <param name="os"></param>
/// <param name="level"></param>
/// <returns></returns>
inline std::wostream& operator<<(std::wostream& os, const log_level& level)
{
	switch(level)
	{
	case log_level::none:
		os << L"None";
		break;
	case log_level::verbose:
		os << L"Verbose";
		break;
	case log_level::information:
		os << L"Information";
		break;
	case log_level::debug:
		os << L"Debug";
		break;
	case log_level::trace:
		os << L"Trace";
		break;
	case log_level::warning:
		os << L"Warning";
		break;
	case log_level::error:
		os << L"Error";
		break;
	case log_level::critical:
		os << L"Critical";
		break;
	default:
		os << L"Unknown";
	}

	return os;
}
