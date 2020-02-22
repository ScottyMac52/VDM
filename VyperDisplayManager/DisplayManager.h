#pragma once
#include "DisplayWindow.h"
using namespace std;

typedef std::map<int, display_window*> display_window_map;
typedef std::pair<int, display_window*> display_window_pair;

/// <summary>
/// Class manages the list of Displays for a Module and the ConfigurationDefinition for each
/// </summary>
class display_manager
{
public:
	display_manager();
	~display_manager();
	/// <summary>
	/// Adds a DisplayWindow to the map using the ConfigurationDefinition
	/// </summary>
	/// <param name="config"></param>
	void AddConfiguration(const configuration_definition& config);
	/// <summary>
	/// Reads all sources of ConfigurationDefinition
	/// </summary>
	void ReadConfigurations();
	/// <summary>
	/// Closes all Windows 
	/// </summary>
	void close_all();
	/// <summary>
	/// Removes a DisplayWindow from the Map
	/// </summary>
	/// <param name="index"></param>
	void remove_configuration(const int index);
	/// <summary>
	/// Creates all of the Windows
	/// </summary>
	/// <param name="h_instance"></param>
	void create_configurations(HINSTANCE const h_instance, HWND const h_wnd);
	/// <summary>
	/// Shows all windows
	/// </summary>
	void show_all();
protected:
	display_window_map configuration_map_;
private:
};

