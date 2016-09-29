#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SLF.h"
#include "Widgets.h"
#include "Profile.h"
#include "StockDatabase.h"

class MainWindow : public Fl_Window
{
public:
	MainWindow(const char* title, Fl_Window* parent, Profile profile);

	~MainWindow();
private:
	// Window properties 
	static const int WINDOW_WIDTH = 1000;
	static const int WINDOW_HEIGHT = 600;
	Fl_Color WINDOW_BCK_COLOR = fl_rgb_color(30, 30, 30);

	// Button properties
	static const int BUTTON_WIDTH = 100;
	static const int BUTTON_HEIGHT = 30;

	// Menu bar properties
	static const int MENU_BAR_XCORD = 0;
	static const int MENU_BAR_YCORD = 0;
	static const int MENU_BAR_WIDTH = WINDOW_WIDTH;
	static const int MENU_BAR_HEIGHT = 30;

	// Profile display properties
	static const int PROFILE_DISP_XCORD = 25;
	static const int PROFILE_DISP_YCORD = 50;

	// Grapher properties
	static const int GRAPHER_XCORD = 300;
	static const int GRAPHER_YCORD = 50;
	static const int GRAPHER_WIDTH = 300;
	static const int GRAPHER_HEIGHT = 200;

	// Stock database and manager
	//DownloadManager _downloadManager;
	StockDatabase _database;

	// Player profile data
	Profile _profile;
	ProfileDisplay* _profileDisplay;

	// Used to go back to previous window
	Fl_Window* _parent;

	Fl_Button* _close;
	Fl_Menu_Bar* _menu;
	Graphics_Graph* _graph;

	// Date choice and Grapher options
	Date* _startDate;
	Date* _endDate;
	Fl_Button* _btnPlotGrapher;
	DateSelector* _dateSelector;

	// Command line and display
	Fl_Multiline_Output* _outputDisplay;
	Fl_Input* _commandPrompt;

	static void cb_updateGrapher(Fl_Widget* o, void* v)
	{
		((MainWindow*)v)->cb_updateGrapher_i();
	}

	inline void cb_updateGrapher_i();

	static void cb_commandPrompt(Fl_Widget* o, void* v)
	{
		((MainWindow*)v)->cb_commandPrompt_i();
	}

	inline void cb_commandPrompt_i();

	static void cb_logout(Fl_Widget* o, void* v)
	{
		((MainWindow*)v)->cb_logout_i();

	}

	inline void cb_logout_i();

	static void cb_quit(Fl_Widget* o, void* v)
	{
		((MainWindow*)v)->cb_quit_i();
	}

	inline void cb_quit_i();

	void displayIntro() const;

	void initialize_menu();

	void draw();

	string getUserFile() const;
};

#endif