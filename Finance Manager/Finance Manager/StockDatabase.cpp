#include "StockDatabase.h"

StockDatabase::StockDatabase(string filename)
	:_databaseFilename(filename),
	_prevHistoryUpdate(1,1,1980)
{
	loadStocks();
	update();
	Date curDate;
	// Set to last update to current date
	_prevHistoryUpdate.setDate(curDate.getMonth(), curDate.getDay(), curDate.getYear());
}

double StockDatabase::getStockValue(Symbol sym) const
{
	for (int index = 0; index < _stocks.size(); ++index)
	{
		if (sym == _stocks.at(index).getSymbol())
			return _stocks.at(index).getValue();
	}
	
	return NOT_FOUND;
}

string StockDatabase::getStockName(Symbol sym) const
{
	for (int index = 0; index < _stocks.size(); ++index)
	{
		if (sym == _stocks.at(index).getSymbol())
			return _stocks.at(index).getSymbolAsString();
	}

	return "INVALID";
}

double StockDatabase::getStockClosingPrice(Symbol sym) const
{
	for (int index = 0; index < _stocks.size(); ++index)
	{
		if (sym == _stocks.at(index).getSymbol())
			return _stocks.at(index).getClosingPrice();
	}

	return 0.0;
}

void StockDatabase::update()
{
	// We always update prices upon request
	_downloadManager.updateCurrentPrices();

	// Limit history updates since they are slow and do not change from frequently
	Date date;	// Current date

	if (_prevHistoryUpdate < date)
	{
		_downloadManager.updateHistoryData();
		_prevHistoryUpdate.setDate(date.getMonth(), date.getDay(), date.getYear());
		cout << "Historical data was updated successfully..." << endl;
	}
	else
	{
		cout << "Historical data up-to-date, there is no need for an update..." << endl;
	}
}

// This parses downloaded file, and loads all stocks
int StockDatabase::loadStocks()
{
	ifstream inputFile(_databaseFilename);
	if (!inputFile)
	{
		error("Could not open file for input: StockDatabase::getStockValue()");
		return FAILED;
	}

	string symbol;
	while (getline(inputFile, symbol, ','))
	{
		if (DEBUG) cout << "Symbol = " << symbol << endl;
		
		string symbolName;
		getline(inputFile, symbolName, ',');
		if (DEBUG) cout << "name = " << symbolName << endl;

		string value;
		getline(inputFile, value, ',');
		if (DEBUG) cout << "Value = " << value << endl << endl;

		double val;
		if (value == "N/A")
			val = 0.0;
		else
			val = stod(value);

		string prevClose;
		getline(inputFile, prevClose);
		double close;
		if (prevClose == "N/A")
			close = 0.0;
		else
			close = stod(prevClose);

		_stocks.push_back(StockValue(Symbol(symbol), 0, val, close, symbolName));
	}

	return SUCCESS;
}

void StockDatabase::setStartDate(Date date)
{
	Date* copy = new Date(date.getMonth(), date.getDay(), date.getYear());
	_downloadManager.setStartDate(copy);
}

void StockDatabase::setEndDate(Date date)
{
	Date* copy = new Date(date.getMonth(), date.getDay(), date.getYear());
	_downloadManager.setEndDate(copy);
}

ConnectedLine StockDatabase::getConnectedLine(Symbol sym)
{
	ConnectedLine linePoints;

	string filename = sym.getSymbol() + "_HISTORICAL_DATA.txt";

	ifstream input(filename.c_str());
	if (!input)
	{
		error("Could not open file for input in StockDatabase::getConnectedLine()");
		return linePoints;
	}

	Point p;
	Date date;
	double value;

	input >> date >> value;

	int offset = date.getDateAsInt();

	p.x = date.getDateAsInt();	// - offset
	p.y = value;
	linePoints.addPoint(p);

	while (input >> date >> value)
	{
		Point p;
		p.x = date.getDateAsInt();// - offset
		p.y = value;
		linePoints.addPoint(p);

		//cout << p.x << " " << p.y << endl;
	}

	return linePoints;
}

ConnectedLine StockDatabase::getConnectedLine(Symbol sym, Date startDate, Date endDate)
{
	ConnectedLine tmpLine = getConnectedLine(sym);
	
	// Keep the points within the date range
	int minX = startDate.getDateAsInt();
	int maxX = endDate.getDateAsInt();

	ConnectedLine line;
	for (int index = 0; index < tmpLine.getSize(); ++index)
	{
		if (tmpLine[index].x > minX && tmpLine[index].x < maxX)
			line.addPoint(tmpLine[index]);
	}

	return line;
}
