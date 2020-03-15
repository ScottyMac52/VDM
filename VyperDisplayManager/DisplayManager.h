#pragma once

class display_window;
class file_checker;
class module_definition;

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
	void add_configuration(const configuration_definition& config);
	/// <summary>
	/// Closes all Windows 
	/// </summary>
	void close_all();
	/// <summary>
	/// Removes a DisplayWindow from the Map
	/// </summary>
	/// <param name="index"></param>
	void remove_configuration(const int index);
	void run(HINSTANCE const h_instance, HWND const h_wnd, std::vector<std::wstring> command_line);
	[[nodiscard]] std::wstring get_selected_module() const;
	[[nodiscard]] std::wstring get_selected_sub_modules() const;
protected:
	display_window_map configuration_map_;
	module_definition *pmodule_definition_;
	/// <summary>
	/// Reads all sources of ConfigurationDefinition
	/// </summary>
	void read_configurations();
	/// <summary>
	/// Creates all of the Windows
	/// </summary>
	/// <param name="h_instance"></param>
	void create_configurations(HINSTANCE const h_instance, HWND const h_wnd);
	/// <summary>
	/// Shows all windows
	/// </summary>
	void show_all();
private:
	bool b_button_down_ = false;
	std::wstring selected_module_;
	std::wstring selected_sub_modules_;
	file_checker file_checker_;
};

