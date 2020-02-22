#pragma once
class file_checker
{
public:
	static bool validate_file(const std::wstring& full_path);
	static std::wstring get_current_directory();
protected:
private:
	std::ifstream fs_;
};

