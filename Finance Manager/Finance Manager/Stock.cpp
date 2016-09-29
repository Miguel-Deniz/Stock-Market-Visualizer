#include "Stock.h"

Symbol::Symbol()
{
	_symbol = DEFAULT_SYMBOL;
}

Symbol::Symbol(string sym)
{
	if (isValidSymbol(sym))
		_symbol = sym;
	else
		_symbol = DEFAULT_SYMBOL;
}

string Symbol::getSymbol() const
{
	return _symbol;
}

bool Symbol::isValidSymbol(string sym)
{
	// A more sophisticated error checking should be implemented
	if (sym.length() >= MIN_LENGTH && sym.length() <= MAX_LENGTH)
		return true;
	else
		return false;
}

istream& operator>>(istream& in, Symbol& symbol)
{
	in >> symbol._symbol;
	return in;
}

ostream& operator<< (ostream& out, const Symbol& symbol)
{
	out << symbol._symbol;
	return out;
}

//------------------------------------------------------------------------------

Stock::Stock()
{
	_quantity = 0;
}

Stock::Stock(Symbol sym, int quantity)
	:_symbol(sym), _quantity(quantity)
{
	// Check for valid values here
}

Symbol Stock::getSymbol() const
{
	return _symbol;
}

string Stock::getSymbolAsString() const
{
	return _symbol.getSymbol();
}

int Stock::getQuantity() const
{
	return _quantity;
}

istream& operator>>(istream& in, Stock& stock)
{
	in >> stock._symbol >> stock._quantity;
	return in;
}

ostream& operator<<(ostream& out, const Stock& stock)
{
	out << stock._symbol << " Qty:" << stock._quantity;
	return out;
}

bool operator<(const Stock &stock1, const Stock &stock2)
{
	if (stock1.getSymbolAsString().compare(stock2.getSymbolAsString()) < 0)
		return true;
	else
		return false;
}

//------------------------------------------------------------------------------


StockValue::StockValue()
	:_stockName("N/A")
{
	_value = 0.0;
}

StockValue::StockValue(Stock stock, double val, double previousClosing)
	:Stock(stock), _prevClose(previousClosing), _stockName("N/A")
{
	_value = val;
} 

StockValue::StockValue(Symbol sym, int quantity, double val, double previousClosing, string stockName)
	:Stock(sym, quantity), _prevClose(previousClosing), _stockName(stockName)
{
	_value = val;
}

double StockValue::getValue() const
{
	return _value;
}

double StockValue::getClosingPrice() const
{
	return _prevClose;
}

bool operator==(const Symbol& s1, const Symbol& s2)
{
	return s1.getSymbol() == s2.getSymbol();
}

istream& operator>>(istream& in, StockValue& stock)
{
	Stock tmpStock;
	double tmpVal;
	in >> tmpStock >> tmpVal;

	return in;
}

ostream& operator<<(ostream& out, const StockValue& stock)
{
	out << (Stock)stock << " Value: " << stock._value << endl;
	return out;
}
