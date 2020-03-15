#pragma once
class input_parser
{
public:
	input_parser(int& argc, wchar_t** argv)
	{
		for (auto i = 0; i < argc; ++i)
		{
			this->tokens_.emplace_back(argv[i]);
		}
	};

	[[nodiscard]] const std::wstring& get_cmd_option(const std::wstring& option) const {
		auto itr = std::find(this->tokens_.begin(), this->tokens_.end(), option);
		if (itr != this->tokens_.end() && ++itr != this->tokens_.end()) {
			return *itr;
		}
		static const std::wstring empty_string;
		return empty_string;
	};

	[[nodiscard]] bool cmd_option_exists(const std::wstring& option) const {
		return std::find(this->tokens_.begin(), this->tokens_.end(), option)
			!= this->tokens_.end();
	};
	
private:
	std::vector <std::wstring> tokens_;
};

