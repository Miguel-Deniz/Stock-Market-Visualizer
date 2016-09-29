/*
	Author: Miguel Deniz Lopez
	Date:	7/8/16 5:05 PM

	Last Update: 8/1/16 9:33 PM
*/

#ifndef PROFILE_H
#define PROFILE_H

#include "SLF.h"
#include "Stock.h"
#include "Widgets.h"
#include "StockDatabase.h"

using namespace std;

//const bool DEBUG = true;

class Profile
{
public:
	Profile(string username, string password);

	~Profile();



	// Accessor methods
	string getUsername() const;
	string getFilename() const;
	int getNumberOfStocks() const;
	double getMoney() const;



	// Subscript overloading to access stocks.
	// Number of stocks can be determined by the function getNumberOfStocks().
	Stock& operator[] (int index);

private:
	string _username;

	string _password;

	double _money;

	vector<Stock> _stocks;



	void loadProfile();
	void saveProfile();	// code me



	friend ostream& operator<<(ostream& out, const Profile& profile);
};

ostream& operator<<(ostream& out, const Profile& profile);


//------------------------------------------------------------------------------


class ProfileDisplay : public Fl_Widget
{
public:
	ProfileDisplay(Profile profile, StockDatabase* database, int x, int y);

	// Returns 1 if the button is activated
	// Returns 0 if the button is not activated
	bool getButtonStatus(Stock stock) const;

	// Returns the color selection of the button
	Fl_Color getButtonColor(Stock stock) const;

	void draw();

private:
	// Used to determine which stocks the player owns, along with username
	Profile _profile;
	// Used to obtain current prices of stocks
	StockDatabase* _database;
	// Each stock has an activation button for display
	map<Stock, ToggleButton*> _stocks;


	/// Top left coordinates
	// X-Coordinate of top left corner
	int _xCord;
	// Y-Coordinate of top left corner
	int _yCord;


	// Maximum number of stocks to display
	const int MAX_STOCKS_DISPLAY = 5;
	// Width of each line of display
	const int LINE_WIDTH = 30;
	// Height of the header, is the same as profile display
	const int HEADER_HEIGHT = LINE_WIDTH;
	const int BUTTON_HEIGHT = 30;
	const int BUTTON_WIDTH = 300 / 4;



	/// Profile display dimensions
	// Width of profile display
	const int WIDTH = 300;
	// Height of profile display
	const int HEIGHT = LINE_WIDTH * MAX_STOCKS_DISPLAY + HEADER_HEIGHT + BUTTON_HEIGHT;
	// Border padding
	static const int PROFILE_DISP_PADDING = 10;


	/// Color custimazation
	// Color of outside border
	const Fl_Color COLOR_BORDER = FL_WHITE;
	// Color of stripe 1
	const Fl_Color COLOR_STRIPE1 = FL_WHITE;
	// Color of stripe 2
	const Fl_Color COLOR_STRIPE2 = fl_rgb_color(221, 235, 247);


	/// Buttons
	// Up button
	DirectionalButton* _btnUp;
	// Down button
	DirectionalButton* _btnDown;
	// Buy button
	Fl_Button* _btnBuy;
	// Sell button
	Fl_Button* _btnSell;



	int _startStockIndex;


	/// Callbacks
	static void cb_increment(Fl_Widget* o, void* v)
	{
		((ProfileDisplay*)v)->cb_increment_i();
	}

	inline void cb_increment_i();


	static void cb_decrement(Fl_Widget* o, void* v)
	{
		((ProfileDisplay*)v)->cb_decrement_i();
	}

	inline void cb_decrement_i();

	int handle(int event);


	//int handle(int event);

	/// Accessors
	// Returns the value of all stocks
	double getStocksWorth();
	// Returns the cash in hand plus the value of all stocks
	double getNetWorth();
};

#endif