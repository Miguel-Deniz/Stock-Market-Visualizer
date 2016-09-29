/*
	Author: Miguel Deniz Lopez
	Date: 7/9/16

	Last Update: 8/1/2016 5:27 PM
*/

#ifndef STOCK_H
#define STOCK_H

#include "SLF.h"

static const bool DEBUG = false;

//------------------------------------------------------------------------------


// This class represents a stock symbol such as "GOOG", "MSFT", "AAPL"
// A symbol is a 2-5 character long string. All characters are uppercase.
class Symbol
{
public:
	// Creates a default symbol, see DEFAULT_SYMBOL
	Symbol();

	// Creates a symbol with the given string.
	// Symbol must be >= 2 characters long and <= 5 characters long
	// If symbol is invalid, it will be set to DEFAULT_SYMBOL
	Symbol(string sym);

	// Returns the current symbol
	string getSymbol() const;

private:
	// Min symbol length
	const int MIN_LENGTH = 2;

	// Max symbol length
	const int MAX_LENGTH = 5;

	// Default symbol for initialization
	const string DEFAULT_SYMBOL = "N/A";

	// Used to store symbol
	string _symbol;



	// Determines where the given string is a valid symbol
	bool isValidSymbol(string sym);



	// Comparison Operator Overload
	friend bool operator==(const Symbol& s1, const Symbol& s2);


	// Input/Output Overloads
	friend istream& operator>>(istream& in, Symbol& symbol);
	friend ostream& operator<< (ostream& out, const Symbol& symbol);
};

bool operator==(const Symbol& s1, const Symbol& s2);

istream& operator>>(istream& in, Symbol& symbol);
ostream& operator<< (ostream& out, const Symbol& symbol);


//------------------------------------------------------------------------------


// This class represents a Stock. A stock has a symbol and a quantity.
class Stock
{
public:
	// Creates a default value Stock, with default Symbol and qty. = 0
	Stock();

	Stock(Symbol sym, int quantity);



	// Accessor methods
	// Returns the Symbol of the stock
	Symbol getSymbol() const;

	// Returns the Symbol of the stock as a string
	string getSymbolAsString() const;

	// Returns the quantity of the stock
	int getQuantity() const;

private:
	Symbol _symbol;

	int _quantity;



	// Input/Output Overloads
	friend istream& operator>>(istream& in, Stock& stock);
	friend ostream& operator<<(ostream& out, const Stock& stock);


	// Comparison operators
	friend bool operator<(Stock &stock1, Stock &stock2);
};

istream& operator>>(istream& in, Stock& stock);
ostream& operator<<(ostream& out, const Stock& stock);

bool operator<(const Stock &stock1, const Stock &stock2);

//------------------------------------------------------------------------------


class StockValue : public Stock
{
public:
	// Creates a default StockValue with default Stock and value = 0
	StockValue();

	StockValue(Stock stock, double val, double previousClosing);

	StockValue(Symbol sym, int quantity, double val, double previousClosing, string stockName = "N/A");



	// Returns the stock value
	double getValue() const;
	// Returns the previous day closing price
	double getClosingPrice() const;


	// Input/Output Overloads
	friend istream& operator>>(istream& in, StockValue& stock);
	friend ostream& operator<<(ostream& out, const StockValue& stock);

private:
	string _stockName;
	double _value;
	// Previous day closing price
	double _prevClose;
};

istream& operator>>(istream& in, StockValue& stock);
ostream& operator<<(ostream& out, const StockValue& stock);


//------------------------------------------------------------------------------



#endif