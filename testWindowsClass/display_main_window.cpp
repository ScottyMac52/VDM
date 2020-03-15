#include "pch.h"
#include "main.h"
#include "display_main_window.h"

int display_main_window::on_paint()
{
	return 0;
}

display_main_window::display_main_window(main* app)
{
	app_ = app;
}

bool display_main_window::close()
{
	PostQuitMessage(0);
	return false;
}

LRESULT display_main_window::on_create_window(LPARAM l_param)
{
	return LRESULT();
}

LRESULT display_main_window::on_close()
{
	if(app_ != nullptr)
	{
		app_->quit(0);
	}
	return LRESULT();
}

