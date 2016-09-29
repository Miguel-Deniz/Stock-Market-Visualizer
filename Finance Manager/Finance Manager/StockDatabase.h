#ifndef STOCK_DATABASE_H
#define STOCK_DATABASE_H

#include "SLF.h"
#include "Stock.h"
#include "DownloadManager.h"
#include "Grahpics.h"

//------------------------------------------------------------------------------


class StockDatabase
{
public:
	// Creates a database and loads all the information for use using the given filename.
	StockDatabase(string filename);



	// Returns the stock value of the given symbol.
	// Returns 0 if the stock is not in the database.
	double getStockValue(Symbol sym) const;

	// Returns the full stock registered name of the symbol
	// Returns "INVALID" if not found
	string getStockName(Symbol sym) const;

	// Returns the previous closing price of the stock
	// Returns 0.0 if the stock does not have a recorded price
	double getStockClosingPrice(Symbol sym) const;

	ConnectedLine getConnectedLine(Symbol sym);

	ConnectedLine getConnectedLine(Symbol sym, Date startDate, Date endDate);

	void setStartDate(Date date);

	void setEndDate(Date date);



	// Updates all prices and history
	// History will only update if there has been no recent update in the last day.
	void update();

private:
	vector<StockValue> _stocks;
	string _databaseFilename;
	const double NOT_FOUND = 0.0;
	Date _prevHistoryUpdate;

	// Used to update file data
	DownloadManager _downloadManager;



	// Loads all stocks with prices and values
	// Returns 0 if the update failed. Otherwise it returns 1 for success.
	int loadStocks();



	// Output overload
	friend ostream& operator<<(ostream& out, const StockDatabase& database);
};

ostream& operator<<(ostream& out, const StockDatabase& database);


//------------------------------------------------------------------------------

#endif