#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include <map>
#include <vector>
#include <fstream>
#include "generic_window.h"
#include "DisplayWindow.h"
#include "ModuleDefinition.h"
#include "FileChecker.h"
#include "DisplayManager.h"
#include "DisplayConfiguration.h"
#include "log_level.h"
#include "file_logger.h"
#include "input_parser.h"
#include "display_list.h"
#include "module_list.h"

using namespace std;

display_manager::display_manager()
{
	pmodule_definition_ = new module_definition();
}

display_manager::~display_manager()
{
	delete pmodule_definition_;
}

void display_manager::add_configuration(const configuration_definition& config)
{
	// Create a DisplayWindow
	auto disp = new display_window(config);
	// Setup the Configuration Definition for the Window

	// Add the DisplayWindow to the Map
	auto length = static_cast<int>(configuration_map_.size());
	configuration_map_.insert(display_window_pair(length, disp));
}

void display_manager::read_configurations()
{
	module_list mod_list;
	display_list display_list;
	file_logger fl(L"process.log", log_level::trace);
	std::wstring log_entry;
	log_entry.append(L"Reading configurations");
	fl.log_info(log_entry);

	display_list.displays_from_file(L"C:\\Users\\Scott\\Source\\Repos\\VDM\\VyperDisplayManager\\Modules\\displays.json");

	module_definition def;
	auto file_list = vector<std::wstring>();
	file_list.emplace_back(L"C:\\Users\\Scott\\Source\\Repos\\VDM\\VyperDisplayManager\\Modules\\Blue Jets\\A-10C.json");

	// Loop through all of the JSON files 
	const std::wstring log_entry_header = L"Loading file: ";
	for (auto it = file_list.begin(); it != file_list.end(); ++it)
	{
		log_entry = log_entry_header;
		log_entry.append(*it);
		fl.log_debug(log_entry);

		// Load the JSON
		fl.log_trace(L"Loading JSON from: " + *it);
		mod_list.from_file(*it);
	}

	auto current_mod = mod_list[selected_module_];
	if (!current_mod.is_empty())
	{
		auto config_list = current_mod.get_configurations();
		auto it = config_list.begin();
		while (it != config_list.end())
		{
			auto current_config = *it;
			display_configuration current_display;
			// See if the configuration name is made up of any display names
			auto result = display_list.find_partial_match(current_config.get_name(), current_display);
			if (result == true)
			{
				current_config = current_display;
			}
			add_configuration(current_config);
			++it;
		}
	}
	else
	{
		::MessageBox(nullptr, L"Unable to find the specified module", L"Error in arguments", MB_ICONEXCLAMATION);
	}
}

void display_manager::close_all()
{
	auto it = configuration_map_.begin();
	while (it != configuration_map_.end())
	{
		file_logger fl(L"process.log", log_level::information);
		std::wstring log_entry;
		log_entry.append(L"Closing configuration: " + it->second->get_configuration_name());
		fl.log_info(log_entry);
		it->second->close();
		++it;
	}

	configuration_map_.clear();
}

void display_manager::remove_configuration(const int index)
{
	display_window* target = configuration_map_[index];
	target->close();
	configuration_map_.erase(index);
	delete target;
}

void display_manager::create_configurations(HINSTANCE const h_instance, HWND const h_wnd)
{
	// Loop through all the DisplayWindows and create them
	auto it = configuration_map_.begin();
	while (it != configuration_map_.end())
	{
		auto index = it->first;
		file_logger fl(L"process.log", log_level::information);
		std::wstring log_entry;
		log_entry.append(L"Creating configuration: " + it->second->get_configuration_name());
		fl.log_info(log_entry);
		it->second->create(h_instance, it->second->get_configuration_name(), h_wnd);
		++it;
	}
}

void display_manager::show_all()
{
	auto it = configuration_map_.begin();
	while (it != configuration_map_.end())
	{
		auto index = it->first;
		it->second->show();
		++it;
	}
}

void display_manager::run(HINSTANCE const h_instance, HWND const h_wnd, std::vector<std::wstring> command_line)
{
	const auto p_list_tokens = new wchar_t* [command_line.size()];
	int argc = command_line.size();

	auto array_counter = 0;
	for (auto it = command_line.begin(); it != command_line.end(); ++it) {
		p_list_tokens[array_counter] = new wchar_t[it->size() + 1];
		wcsncpy_s(p_list_tokens[array_counter++], it->size() + 1, it->c_str(), it->size() + 1);
	}

	const auto inputs = input_parser(argc, p_list_tokens);

	array_counter = 0;
	for (auto it = command_line.begin(); it != command_line.end(); ++it) {
		delete[] p_list_tokens[array_counter++];
	}
	delete[] p_list_tokens;

	if (inputs.cmd_option_exists(L"-m"))
	{
		selected_module_ = inputs.get_cmd_option(L"-m");
	}

	if (inputs.cmd_option_exists(L"-s"))
	{
		selected_sub_modules_ = inputs.get_cmd_option(L"-s");
	}
	
	file_logger fl(L"process.log", log_level::information);
	std::wstring log_entry;
	log_entry.append(L"Running using Module:" + selected_module_ + L" ");
	if(selected_sub_modules_.length() > 0)
	{
		log_entry.append(L" SubModule(s):" + selected_sub_modules_);
	}
	fl.log_info(log_entry);
	
	read_configurations();
	create_configurations(h_instance, h_wnd);
	show_all();
}

std::wstring display_manager::get_selected_module() const
{
	return selected_module_;
}

std::wstring display_manager::get_selected_sub_modules() const
{
	return selected_sub_modules_;
}
