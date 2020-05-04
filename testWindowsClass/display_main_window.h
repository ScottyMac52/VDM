#pragma once
#include "main_window.h"

class main;

class display_main_window :
	public main_window
{
protected:
	int on_paint() override;
public:
	explicit display_main_window(main* app);
	virtual bool close() override;
protected:
	virtual LRESULT on_create_window(LPARAM l_param) override;
	virtual LRESULT on_close() override;
private:
	main *app_;
};

