#include "MainWindow.h"

MainWindow::MainWindow(const char* title, Fl_Window* parent, Profile profile)
	:Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, title),
	_parent(parent),
	_profile(profile), //_database("stocks_download.txt")
	_database("stocks_download.txt")
{
	_parent->hide();

	// Window properties
	color(WINDOW_BCK_COLOR);
	position(Fl::w() / 2 - w() / 2, Fl::h() / 2 - h() / 2);	// Center window on screen

	begin();

	// Set up menu bar
	_menu = new Fl_Menu_Bar(MENU_BAR_XCORD, MENU_BAR_YCORD, MENU_BAR_WIDTH, MENU_BAR_HEIGHT, "Menu");
	initialize_menu();

	// Set up grapher
	_graph = new Graphics_Graph(GRAPHER_XCORD + 50, GRAPHER_YCORD, 600, 375, FL_BLACK);
	_btnPlotGrapher = new Fl_Button(150, 400, 100, 30, "Update Graph");
	_btnPlotGrapher->callback(cb_updateGrapher, this);
	_dateSelector = new DateSelector(25, 300, FL_WHITE);

	// Set up command line display
	_outputDisplay = new Fl_Multiline_Output(20, h() - 150, w() - 40, 100);
	_commandPrompt = new Fl_Input(80, h() - 40, w() - 100, 30, "Command:");
	_commandPrompt->callback(cb_commandPrompt, this);
	_commandPrompt->when(FL_WHEN_ENTER_KEY_ALWAYS);

	// Setup profile display
	_profileDisplay = new ProfileDisplay(profile, &_database, PROFILE_DISP_XCORD, PROFILE_DISP_YCORD);

	resizable(this);

	// Stop attaching widgets
	end();

	// Draw profile status
	draw();

	show();
}

MainWindow::~MainWindow() {}

inline void MainWindow::cb_logout_i()
{
	// Return to login window
	_parent->show();
	_parent->set_modal();
	hide();
}

string MainWindow::getUserFile() const
{
	// fix this
	// return profile
	return ".txt";
}

inline void MainWindow::cb_updateGrapher_i()
{
	_graph->clear();

	Date sd = _dateSelector->getStartDate();
	Date ed = _dateSelector->getEndDate();
	_startDate = new Date(sd.getMonth(), sd.getDay(), sd.getYear());
	_endDate = new Date(ed.getMonth(), ed.getDay(), ed.getYear());

	// Download historical data
	_database.setStartDate(sd);
	_database.setEndDate(ed);
	_database.update();

	// Display the data
	for (int index = 0; index < _profile.getNumberOfStocks(); ++index)
	{
		Stock stock = _profile[index];
		bool active = _profileDisplay->getButtonStatus(stock);

		if (active == true)
		{
			Fl_Color color = _profileDisplay->getButtonColor(stock);
			ConnectedLine line = _database.getConnectedLine(stock.getSymbol(), *_startDate, *_endDate);
			line.setColor(color);
			_graph->addLine(line);
		}
	}

	redraw();
}

inline void MainWindow::cb_commandPrompt_i()
{
	string command = _commandPrompt->value();

	if (command == "display profile")
	{
		cout << _profile << endl;
	}
	else
	{
		string error = "Unknown command: " + command;
		_outputDisplay->insert(error.c_str());
		_outputDisplay->insert("\n");
	}
}

void MainWindow::initialize_menu()
{
	_menu->add("File/Logout", FL_CTRL + 'm', cb_logout, this);
	_menu->add("File/Quit", FL_CTRL + 'q', cb_quit);
	_menu->add("Edit/A");
	_menu->add("Profile/Change Password");
	_menu->add("Profile/Reset");
	_menu->add("Profile/Restor");
	_menu->add("Help/About");
	_menu->add("Help/Version");
}

void MainWindow::draw()
{
	Fl_Window::draw();
	_profileDisplay->draw();
	_graph->draw();
	_dateSelector->draw();
}

inline void MainWindow::cb_quit_i()
{
	exit(0);
}

void MainWindow::displayIntro() const
{
	cout << "Error.... here" << endl;
}