#ifndef REGISTRATION_WINDOW
#define REGISTRATION_WINDOW

#include "SLF.h"

class RegistrationWindow : public Fl_Window
{
private:
	static const int WINDOW_WIDTH = 400;
	static const int WINDOW_HEIGHT = 250;
	static const int INPUT_WIDTH = 250;
	static const int INPUT_HEIGHT = 30;
	static const int BUTTON_WIDTH = 100;
	static const int BUTTON_HEIGHT = 30;
	const string REGISTERED_ACCOUNTS_FILE = "USERDATA.txt";

	// Account registration details
	const double STARTING_MONEY = 10000.0;

	Fl_Window* _parent;

	Fl_Input* _username;
	Fl_Secret_Input* _password1;
	Fl_Secret_Input* _password2;
	Fl_Button* _register;
	Fl_Button* _cancel;

	static void cb_register(Fl_Widget* o, void* v)
	{
		((RegistrationWindow*)v)->cb_register_i();
	}

	inline void cb_register_i();

	static void cb_close(Fl_Widget* o, void* v)
	{
		((RegistrationWindow*)v)->cb_close_i();
	}

	inline void cb_close_i();

	int valid_username();

	int valid_passwords();

	void register_account(string username, string password);
public:
	RegistrationWindow(Fl_Window* parent);
};

#endif