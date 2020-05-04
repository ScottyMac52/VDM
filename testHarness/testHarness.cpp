// testHarness.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once

#include <fstream>
#include "cajun/json/reader.h"
#include "cajun/json/writer.h"
#include "cajun/json/elements.h"
#include <sstream>
#include "json_check.h"
#include "module_def.h"
#include "module_list.h"

using namespace std;
using namespace json;

int main()
{
	auto ml = module_list();
	const auto file_path = L"C:\\Users\\Scott\\Source\\Repos\\VDM\\VyperDisplayManager\\Modules\\Blue Jets\\F-14BRIO.json";

	/*
	std::wifstream in_file;
	std::wstringstream w_string_stream;

	in_file.open(file_path, std::wifstream::in);
	if (in_file.is_open())
	{
		w_string_stream << in_file.rdbuf();
		in_file.close();
	}

	wcout << L"File loaded: " << endl;
	wcout << w_string_stream.str();
	wcout << L"Loading file and processing..." << endl;
	*/
	
	ml.from_file(file_path);
	const std::wstring key = L"F-14R";
	wcout << L"Getting a module..." << endl;
	const auto config = ml[key];
		
	if(config.is_empty())
	{
		wcout << key << " was not found!" << endl;
	}
	else
	{
		wcout << "Configuration found: " << endl;
		wcout << config;
		module_list new_list;
		json::Array new_array;
		auto json_object = config.to_json_object();
		new_array.Insert(json_object);
		new_list << new_array;
		new_list.to_file(L"C:\\Users\\Scott\\Source\\Repos\\VDM\\VyperDisplayManager\\Modules\\Blue Jets\\output.json");
	}
	wcout << L"end program." << endl << "Press any key to continue..." << endl;
	return 0;
}
