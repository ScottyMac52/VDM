#include "pch.h"
#include "globals.h"
#include <fstream>
#include "FileChecker.h"
#include <codecvt>

using namespace std;

bool file_checker::validate_file(const std::wstring& full_path)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	const auto converted_str = converter.to_bytes(full_path);
	struct stat buffer;
	const auto b_exist = (stat(converted_str.c_str(), &buffer) == 0);
	return b_exist;
}

std::wstring file_checker::get_current_directory()
{
	wchar_t buffer[MAX_PATH]; 
	GetModuleFileName(nullptr, buffer, MAX_PATH);
	const auto pos = wstring(buffer).find_last_of(L"\\/");
	return wstring(buffer).substr(0, pos);
}