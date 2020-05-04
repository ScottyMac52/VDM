#include "pch.h"
#include <string>
#include <filesystem>
#include <vector>
#include "FileChecker.h"

using namespace std;
//namespace fs = std::filesystem;

std::vector<std::wstring> file_checker::get_modules(const std::wstring& file_spec) const
{
	auto files_list = std::vector<std::wstring>();

	/*
	const auto module_directory = fs::current_path();
	const std::wstring modules = L"\\Modules";
	std::wstring full_path = module_directory;
	full_path.append(modules);
	auto counter = 0;
	for (auto& p : fs::recursive_directory_iterator(full_path))
	{
		if(p.path().extension() == L".json")
		{
			if(file_spec == L"*" || (file_spec != L"*" && p.path().filename().wstring().find(file_spec) != std::wstring::npos))
			{
				files_list.push_back(p.path());
			}
		}
	}
	*/
	return files_list;
}
