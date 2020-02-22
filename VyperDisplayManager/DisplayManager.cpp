#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include <map>
#include "DisplayWindow.h"
#include "DisplayManager.h"
#include "ModuleDefinition.h"

using namespace std;

display_manager::display_manager()
= default;

display_manager::~display_manager()
= default;

void display_manager::AddConfiguration(const configuration_definition& config)
{
	// Create a DisplayWindow
	auto disp = new display_window(config);
	// Setup the Configuration Definition for the Window

	// Add the DisplayWindow to the Map
	auto length = static_cast<int>(configuration_map_.size());
	configuration_map_.insert(display_window_pair(length, disp));
}

void display_manager::ReadConfigurations()
{
	// Loop through all of the JSON files 

	// For each file

		// Load the JSON

		// Process the JSON

		// Create a ModuleDefinition and ConfigurationDefinitions from the JSON

		//ModuleDefinition module = ModuleDefinition();
		
		configuration_definition config = configuration_definition(L"WHKEY", L"E:\\HOTAS\\TARGET\\CTS\\Docs\\Profile JPGs\\MiG-19\\", L"DCS MIG19 WH.JPG", 0.5F, area(2561, 0, 3761, 1080), area(0,0,0,0));
		config.set_module_name(L"MiG-19");
		//module.addConfiguration(config);
		AddConfiguration(config);

		configuration_definition config2 = configuration_definition(L"LMFD", L"E:\\HOTAS\\TARGET\\CTS\\Docs\\Profile JPGs\\MiG-19\\", L"DCS MIG19 MFD.JPG", 0.5F, area(-1280, 0, -410, 700), area(101, 250, 776, 900));
		config2.set_module_name(L"MiG-19");
		//module.addConfiguration(config2);
		AddConfiguration(config2);

		configuration_definition config3 = configuration_definition(L"RMFD", L"E:\\HOTAS\\TARGET\\CTS\\Docs\\Profile JPGs\\MiG-19\\", L"DCS MIG19 MFD.JPG", 0.5F, area(4890, 0, 5760, 700), area(903, 250, 250, 900));
		config3.set_module_name(L"MiG-19");
		//module.addConfiguration(config3);
		AddConfiguration(config3);


	// Next
}

void display_manager::close_all()
{
	auto it = configuration_map_.begin();
	while (it != configuration_map_.end())
	{
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
