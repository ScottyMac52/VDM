#pragma once

class file_checker
{
public:
	[[nodiscard]] std::vector<std::wstring> get_modules(const std::wstring& file_spec = L"*") const;
};

