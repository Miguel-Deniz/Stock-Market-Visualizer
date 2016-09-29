#include "Profile.h"

Profile::Profile(string username, string password)
	:_username(username), _password(password)
{
	loadProfile();
}

Profile::~Profile()
{
	// Here we must save the profile data
}

string Profile::getUsername() const
{
	return _username;
}

string Profile::getFilename() const
{
	return _username + ".txt";
}

int Profile::getNumberOfStocks() const
{
	return _stocks.size();
}

double Profile::getMoney() const
{
	return _money;
}

Stock& Profile::operator[](const int index)
{
	if (index < 0 || index >= _stocks.size())
		return Stock();
	else
		return _stocks.at(index);
}
void Profile::loadProfile()
{
	string filename = getFilename();
	ifstream dataFile(filename);

	if (!dataFile)
	{
		error("Could not load profile, file DNE. Profile::loadProfile()");
		system("PAUSE");
		exit(1);
		// Here we can choose to create a new file or exit the program
	}

	// Read in profile username, password, and money
	string username;
	getline(dataFile, username);
	if (DEBUG) cout << username << endl;

	string password;
	getline(dataFile, password);
	if (DEBUG) cout << password << endl;

	string money;
	getline(dataFile, money);
	stringstream ss;
	ss << money;
	int value;
	ss >> value;
	if (DEBUG) cout << "Debug -- Value: " << value << endl;

	string lastLogin;
	getline(dataFile, lastLogin);
	if (DEBUG) cout << "Debug -- Last Login: " << lastLogin << endl;

	int count = 0;		// changed
	Stock tmpStock;
	while (dataFile >> tmpStock)
	{
		_stocks.push_back(tmpStock);

		// New db change
		count++;
		Fl_Check_Button* _tmpButton = new Fl_Check_Button(300, 300, 10, 10);
	}

	_money = value;

	if (DEBUG)
	{
		cout << "Debug -- Profile [" << _username << "] loaded successfully...\n";
		cout << "Debug -- " << *this << endl;
	}
}

ostream& operator<<(ostream& out, const Profile& profile)
{
	out << "Username: " << profile._username << " $" <<
		profile._money << endl;
	
	// Display stocks
	out << "-----PROFILE STOCKS-----\n";
	for (int i = 0; i < profile._stocks.size(); ++i)
	{
		out << profile._stocks.at(i) << "\tValue: $0.00" << endl;
	}
	out << "------------------------\n";

	return out;
}


//------------------------------------------------------------------------------


ProfileDisplay::ProfileDisplay(Profile profile, StockDatabase* database, int x, int y)
	:Fl_Widget(x, y, WIDTH, HEIGHT), 
	_profile(profile), _database(database), _xCord(x), _yCord(y),
	_startStockIndex(0)
{
	// Add stocks from profile
	for (int index = 0; index < _profile.getNumberOfStocks(); ++index)
	{
		Stock stock = _profile[index];
		ToggleButton* button = new ToggleButton(0, 10 * index, 15, 15, "Test");
		button->hide();
		_stocks.insert(pair<Stock, ToggleButton*>(stock, button));
	}

	_btnUp = new DirectionalButton(_xCord + WIDTH / 4, _yCord + 180, WIDTH / 4, 30, 1);
	_btnUp->callback(cb_increment, this);
	_btnDown = new DirectionalButton(_xCord, _yCord + 180, WIDTH / 4, 30, 0);
	_btnDown->callback(cb_decrement, this);
	_btnBuy = new Fl_Button(_xCord + 2 * (WIDTH / 4), _yCord + 180, WIDTH / 4, 30, "Buy");
	_btnBuy = new Fl_Button(_xCord + 3 * (WIDTH / 4), _yCord + 180, WIDTH / 4, 30, "Sell");
}

bool ProfileDisplay::getButtonStatus(Stock stock) const
{
	return _stocks.at(stock)->isActive();
}

Fl_Color ProfileDisplay::getButtonColor(Stock stock) const
{
	return _stocks.at(stock)->getColor();
}

void ProfileDisplay::draw()
{
	fl_color(COLOR_BORDER);
	// Draw outline
	fl_rect(_xCord, _yCord, WIDTH, HEIGHT, COLOR_BORDER);

	// Draw table stripes
	int stripeXcord = _xCord;
	int stripeYCord = _yCord + 30;
	for (int index = 0; index < 5; ++index, stripeYCord += 30)
	{
		if (index % 2 == 0)
			fl_color(fl_rgb_color(221, 235, 247));
		else
			fl_color(FL_WHITE);

		fl_rectf(stripeXcord, stripeYCord, WIDTH, 30);
	}

	// Draw header information
	string username = _profile.getUsername();
	string money = dblToStr(_profile.getMoney());
	string networth = dblToStr(getNetWorth());

	const int NAME_XCORD = _xCord + 10;
	const int NAME_YCORD = _yCord + 20;

	string heading = username + "   $" + money + "   Net: $" + networth;
	fl_draw(heading.c_str(), NAME_XCORD, NAME_YCORD);

	// Draw stocks information
	int xcord = NAME_XCORD;
	int ycord = NAME_YCORD + 30;
	for (int i = _startStockIndex; i < _profile.getNumberOfStocks() && i < _startStockIndex + MAX_STOCKS_DISPLAY; ++i)
	{
		fl_color(FL_BLACK);

		// Draw symbol
		string symbol = _profile[i].getSymbolAsString();
		fl_draw(symbol.c_str(), xcord, ycord);

		// Draw quantity
		int quantity = _profile[i].getQuantity();
		fl_draw(intToCharPtr(quantity), xcord + 50, ycord);

		// Draw value
		Symbol sym(symbol);
		double value = _database->getStockValue(sym);
		fl_draw(dblToStr(value).c_str(), xcord + 100, ycord);

		// Draw UP/DOWN arrow for profit notification
		double closingPrice = _database->getStockClosingPrice(sym);
		double priceChange = value - closingPrice;
		
		Direction direction;
		if (priceChange >= 0.0)
			direction = UP;
		else
			direction = DOWN;

		Graphics_DownRect rect(xcord + 150, ycord - 10, direction);
		rect.draw();

		string changeStr = "$" + dblToStr(priceChange);
		fl_draw(changeStr.c_str(), xcord + 170, ycord);

		// Reset color to default value for the next drawing operation
		fl_color(COLOR_BORDER);
		
		// Draw check boxes
		_stocks.at(_profile[i])->position(xcord + 215, ycord - 10);
		_stocks.at(_profile[i])->show();
		_stocks.at(_profile[i])->draw();

		ycord += 30;
	}

	_btnDown->draw();
}

inline void ProfileDisplay::cb_increment_i()
{
	if (_startStockIndex < _profile.getNumberOfStocks() - 1)
	{
		_startStockIndex++;
		ProfileDisplay::parent()->redraw();
	}
}

inline void ProfileDisplay::cb_decrement_i()
{
	if (_startStockIndex > 0)
	{
		_startStockIndex--;
		ProfileDisplay::parent()->redraw();
	}
}

int ProfileDisplay::handle(int event)
{
	if (!Fl::event_inside(_xCord, _yCord, _xCord + WIDTH, _yCord + HEIGHT)) return 0;

	if (event == FL_MOUSEWHEEL)
	{
		int dy = Fl::event_dy();

		if (dy > 0)
			cb_increment_i();		// Positive dy means scrolling up
		else
			cb_decrement_i();		// Negative dy means scrolling down

		return 1;
	}


	return 0;	// event not handled
}

double ProfileDisplay::getStocksWorth()
{
	double totalValue = 0.0;

	for (int i = 0; i < _profile.getNumberOfStocks(); ++i)
	{
		double stockValue = _database->getStockValue(_profile[i].getSymbol());
		int stockQty = _profile[i].getQuantity();
		totalValue += stockValue * stockQty;
	}

	return totalValue;
}

double ProfileDisplay::getNetWorth()
{
	return _profile.getMoney() + getStocksWorth();
}