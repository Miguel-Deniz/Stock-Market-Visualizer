#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "SLF.h"
#include "Profile.h"
#include "MainWindow.h"
#include "RegistrationWindow.h"

class LoginWindow : public Fl_Window
{
	static const int WINDOW_WIDTH = 400;
	static const int WINDOW_HEIGHT = 250;
	static const int WINDOW_RECT_BORDER = 10;
	static const int INPUT_WIDTH = 250;
	static const int INPUT_HEIGHT = 30;
	static const int BUTTON_WIDTH = 100;
	static const int BUTTON_HEIGHT = 30;
	static const int BUTTON_SPACING = 20;
	const string LOGIN_DATA_FILE = "USERDATA.txt";

public:
	Fl_Box* _logoBox;
	Fl_JPEG_Image* _logo;
	Graphics_Text* _incorrectPassword;

	Graphics_Rectangle* _rectBorder;
	Fl_Input* _username;
	Fl_Secret_Input* _password;

	Fl_Button* _login;
	Fl_Button* _register;

	const bool DEBUG = false;

	unsigned int _incorrectAttempts;

	LoginWindow(const char* title);

	~LoginWindow() {};
private:
	static void cb_login(Fl_Widget* o, void* v)
	{
		((LoginWindow*)v)->cb_login_i();
	}

	inline void cb_login_i();

	static void cb_register(Fl_Widget* o, void* v)
	{
		((LoginWindow*)v)->cb_register_i();
	}

	inline void cb_register_i();

	static void cb_username_change(Fl_Widget* o, void* v)
	{
		((LoginWindow*)v)->cb_username_change_i();
	}

	inline void cb_username_change_i();

	static void cb_password_change(Fl_Widget* o, void* v)
	{
		((LoginWindow*)v)->cb_password_change_i();
	}

	inline void cb_password_change_i();

	void clear_fields();
};


#endif