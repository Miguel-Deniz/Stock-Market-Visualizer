#include "LoginWindow.h"

LoginWindow::LoginWindow(const char* title)
	: Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, title),
	_incorrectAttempts(0)
{
	begin();

	// Window properties
	color(0x11111100);
	position(Fl::w() / 2 - w() / 2, Fl::h() / 2 - h() / 2);

	_logo = new Fl_JPEG_Image("logo.jpg");
	_logoBox = new Fl_Box(WINDOW_WIDTH / 2 - _logo->w() / 2, 5, _logo->w(), _logo->h());
	_logoBox->image(_logo);
	_logoBox->redraw();
	char* pass = new char[80];
	pass = "Incorrect username or password...";
	_incorrectPassword = new Graphics_Text(WINDOW_WIDTH / 2 - 102, 215, 1, 1, FL_RED, pass);
	_incorrectPassword->clear_visible();

	_rectBorder = new Graphics_Rectangle(WINDOW_RECT_BORDER,
		WINDOW_RECT_BORDER,
		WINDOW_WIDTH - WINDOW_RECT_BORDER * 2,
		WINDOW_HEIGHT - WINDOW_RECT_BORDER * 2,
		FL_WHITE);

	_username = new Fl_Input(100, 50, INPUT_WIDTH, INPUT_HEIGHT, "Username:");
	_username->labelcolor(FL_WHITE);
	_username->when(FL_WHEN_CHANGED);
	_username->callback(cb_username_change, this);

	_password = new Fl_Secret_Input(100, 100, INPUT_WIDTH, INPUT_HEIGHT, "Password:");
	_password->labelcolor(FL_WHITE);
	_password->when(FL_WHEN_CHANGED);
	_password->callback(cb_password_change, this);

	_login = new Fl_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH - BUTTON_SPACING, 150, BUTTON_WIDTH, BUTTON_HEIGHT, "&LOGIN");
	_login->callback(cb_login, this);

	_register = new Fl_Button(WINDOW_WIDTH / 2 + BUTTON_SPACING, 150, 100, 30, "&REGISTER");
	_register->callback(cb_register, this);

	end();
	resizable(this);
	show();
}


inline void LoginWindow::cb_login_i()
{
	int loginSuccessful = 0;
	string username = _username->value();
	string password = _password->value();
	string filename = username + ".txt";
	
	ifstream profile(filename);
	if (!profile)
	{
		cout << "Profile does not exist: " << username << endl;
	}
	else
	{
		string tmpUser, tmpPass;
		getline(profile, tmpUser);
		getline(profile, tmpPass);

		if (DEBUG)
		{
			cout << "Debug -- Username: " << username << endl;
			cout << "Debug -- Password: " << password << endl;
		}

		if (username == tmpUser && password == tmpPass)
			loginSuccessful = 1;
	}

	if (loginSuccessful)
	{
		clear_fields();

		Profile user(username, password);

		MainWindow* main_window = new MainWindow("Finance Manager", this, user);
		main_window->set_modal();
	}
	else
	{
		cout << "Incorrect username or password..." << endl;
		_incorrectPassword->set_visible();
		redraw();
		_incorrectAttempts++;
		if (_incorrectAttempts >= 5)
		{
			cout << "Limit cap!!!" << endl;
		}
	}
}

inline void LoginWindow::cb_register_i()
{
	clear_fields();
	RegistrationWindow* register_window = new RegistrationWindow(this);
	register_window->set_modal();
}

inline void LoginWindow::cb_username_change_i()
{
	_incorrectPassword->clear_visible();
	redraw();
}

inline void LoginWindow::cb_password_change_i()
{
	_incorrectPassword->clear_visible();
	redraw();
}

void LoginWindow::clear_fields()
{
	_username->value("");
	_password->value("");
	_incorrectPassword->clear_visible();
}