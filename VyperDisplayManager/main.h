#pragma once

class main
{
public:
	main(LPWSTR lp_cmd_line);
	
	/// <summary>
	/// Main run method
	/// </summary>
	/// <param name="h_instance"></param>
	/// <param name="command_line"></param>
	/// <returns></returns>
	int run(const HINSTANCE h_instance, LPCWSTR command_line);

	/// <summary>
	/// Quit method
	/// </summary>
	/// <param name="status"></param>
	void quit(int status);

	/// <summary>
	/// Gets the command line passed as a vector
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] std::vector<std::wstring> get_command_line() const;
private:
	int exit_code_ = 0;
	std::wstring command_line_;
	
};


