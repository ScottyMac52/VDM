// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppInconsistentNaming
#include "pch.h"
#include "globals.h"
#include "main.h"
#include "windowsx.h"
#include "framework.h"
#include <windows.h>
#include "pch.h"
#include "globals.h"
#include "main.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"
#include "ConfigurationDefinition.h"
#include <iterator>

#include "app_settings.h"
#include "resource.h"
#include "generic_window.h"
#include "display_main_window.h"

display_main_window* p_main_window;

static wchar_t sz_atom_name[] = L"<VDMApp>{D0F77DD9-E743-4C1E-8BB6-075D55F585BE}<VDMApp>";
ATOM atom;

using namespace std;

std::wstring app_settings::file_path_;
std::wstring app_settings::file_spec_;
bool app_settings::save_cropped_images_;
bool app_settings::show_tool_tips_;
bool app_settings::turn_off_cache_;
bool app_settings::show_rulers_;
int app_settings::ruler_size_;
int app_settings::ruler_major_width_;
int app_settings::ruler_minor_width_;
bool app_settings::use_cougar_;
bool app_settings::show_configuration_menu_;
std::wstring app_settings::display_config_file_ = L"displays.json";


/// <summary>
/// WinMain : Entry point, minimized
/// </summary>
/// <param name="hInstance">Current Instance</param>
/// <param name="hPrevInstance">Always 0</param>
/// <param name="lpCmdLine">WCHAR* LPWSTR of the command line</param>
/// <param name="nShowCmd"></param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nShowCmd);

    // Disable the duplicate check for now
	const auto atom_to_delete = ::GlobalFindAtom(sz_atom_name);
    ::GlobalDeleteAtom(atom_to_delete);

	// Check the global atom table for an instance of
    // szAtomName. If the atom exists, there must be
    // another instance of this application running.
    if (::GlobalFindAtom(sz_atom_name))
    {
       
        MessageBox(nullptr, L"Another instance of this application is running", L"Error", MB_OK |
            MB_ICONSTOP);
        return -1;
    }

    // No previous instance was detected; add szAtomName
    // to the table.
    atom = ::GlobalAddAtom(sz_atom_name);
	
	auto main_app = new main(lpCmdLine);
	// Run the application
	const auto ret_code= main_app->run(hInstance, lpCmdLine);
    delete main_app;
    return  ret_code;
}


main::main(LPWSTR lp_cmd_line)  // NOLINT(bugprone-exception-escape)
{
    command_line_ = lp_cmd_line;
}

int main::run(const HINSTANCE h_instance, LPCWSTR command_line)
{
    MSG msg;

    auto settings = app_settings::get_instance();
    // ReSharper disable once StringLiteralTypo
    settings.from_file(L"appsettings.json");

	p_main_window = new display_main_window(this);
    std::wstring class_name = L"MainWindow";
    p_main_window->register_class(h_instance, class_name);
    if(p_main_window->create(h_instance, class_name) == FALSE)
    {
        quit(-1);
    }
    p_main_window->show();

    const auto h_accelerator_table = LoadAccelerators(h_instance, MAKEINTRESOURCE(IDI_VYPERDISPLAYMANAGER));
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, h_accelerator_table, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return exit_code_;
}

void main::quit(const int status)
{
    if (p_main_window != nullptr)
    {
        p_main_window->close();
    }

    // Delete the atom before exiting.
    ::GlobalDeleteAtom(atom);

    exit_code_ = status;
}

std::vector<std::wstring>  main::get_command_line() const
{
    std::wistringstream iss(command_line_);
    std::vector<std::wstring> results((std::istream_iterator<std::wstring, wchar_t>(iss)),
        std::istream_iterator<std::wstring, wchar_t>());
    return results;
}
