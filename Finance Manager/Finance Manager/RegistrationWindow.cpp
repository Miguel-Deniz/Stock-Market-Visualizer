#include "RegistrationWindow.h"


inline void RegistrationWindow::cb_register_i()
{
	if (valid_username() && valid_passwords())
	{
		register_account(_username->value(), _password1->value());
		fl_message("Account created successfully!");
		_parent->show();
		_parent->set_modal();
		hide();
	}
	else
	{
		if (!valid_username())
			fl_message("Invalid or taken username...");
		else if (!valid_passwords())
			fl_message("Invalid or non-matching passwords...");
		else
			fl_message("ERROR: Account could not be created...");
	}
}

inline void RegistrationWindow::cb_close_i()
{
	_parent->show();
	_parent->set_modal();
	hide();
}

int RegistrationWindow::valid_username()
{
	// One bug, the function checks the last line twice. But causes no problems.

	int valid = 1;

	// No blank usernames allowed, this prevents "", but not " " or "    "
	if (strcmp(_username->value(), "") == 0 ||
		containsChar(_username->value(), ' '))
		valid = 0;

	ifstream registration_file(REGISTERED_ACCOUNTS_FILE);

	if (!registration_file)
	{
		cout << "Unable to open file for input: " <<
			REGISTERED_ACCOUNTS_FILE << endl << endl;
	}
	else
	{
		char* registered_username = new char[80];
		const char* username = _username->value();
		string t;

		while (registration_file && valid)
		{
			getline(registration_file, t);
			stringstream buffer;
			buffer << t;
			buffer >> t;
			strcpy(registered_username, t.c_str());

			if (strcmp(username, registered_username) == 0)
				valid = 0;
		}
	}

	return valid;
}

int RegistrationWindow::valid_passwords()
{
	if (strcmp(_password1->value(), "") == 0 ||
		strcmp(_password1->value(), _password2->value()) != 0 ||
		containsChar(_password1->value(), ' '))
		return 0;
	else
		return 1;
}

void RegistrationWindow::register_account(string username, string password)
{
	/*
	ofstream registration_file(REGISTERED_ACCOUNTS_FILE, ios::app);

	if (!registration_file)
	{
		cout << "Could not open/create file for output: " <<
			REGISTERED_ACCOUNTS_FILE << endl << endl;
	}
	else
	{
		registration_file << username << " " << password << "\n";
	}
	*/

	/* Account Registration Requiremnts
		For profile name: XYZ
		1. Create a text file XYZ.txt
			Inside the file:
				username
				password
				money
				[stocks...]
	*/
	
	string filename = username + ".txt";
	if (!fileExists(filename))
	{
		ofstream profileData(filename);
		profileData << username << endl;
		profileData << password << endl;
		profileData << STARTING_MONEY << endl;

		cout << "Profile created successfully..." << endl;
	}
}

RegistrationWindow::RegistrationWindow(Fl_Window* parent)
	:Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Registration"), _parent(parent)
{
	// Window properties
	color(0x11111100);
	position(Fl::w() / 2 - WINDOW_WIDTH / 2, Fl::h() / 2 - WINDOW_HEIGHT / 2);

	// Hide the parent window, must be reshown in cb_cancel() since constructors don't work
	_parent->hide();

	begin();

	_username = new Fl_Input(100, 20, INPUT_WIDTH, INPUT_HEIGHT, "Username: ");
	_username->labelcolor(FL_WHITE);

	_password1 = new Fl_Secret_Input(100, 60, INPUT_WIDTH, INPUT_HEIGHT, "Password: ");
	_password1->labelcolor(FL_WHITE);

	_password2 = new Fl_Secret_Input(100, 100, INPUT_WIDTH, INPUT_HEIGHT, "Confirm\nPassword");
	_password2->labelcolor(FL_WHITE);

	_register = new Fl_Button(80, 150, BUTTON_WIDTH, BUTTON_HEIGHT, "&REGISTER");
	_register->callback(cb_register, this);

	_cancel = new Fl_Button(220, 150, BUTTON_WIDTH, BUTTON_HEIGHT, "&CANCEL");
	_cancel->callback(cb_close, this);

	redraw();
	end();
	show();
}