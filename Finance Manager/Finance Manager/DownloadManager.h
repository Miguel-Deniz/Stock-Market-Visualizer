#ifndef DOWNLOAD_MANAGER_H
#define DOWNLOAD_MANAGER_H

#include <urlmon.h>
#include <bitset>
#pragma comment(lib, "urlmon.lib")

#include "SLF.h"
#include "Stock.h"
#include "Calendar.h"

using namespace std;

/*
	Author:			Miguel Deniz Lopez
	Data:			7/8/16 11:24 AM
	Last Update:	8/1/2016 4:38 PM

	Class: DownloadManager

	This class is in charge of downloading/updating the stock data.
	It relies on a file for a list of stocks to track. It then retrieves
	the data from the Yahoo Finance API and stores it locally in another
	file. ASSUMES THAT THE STOCK DATA FILE HAS CORRECT FORMAT!!!

	Documentation:
		URL = http://finance.yahoo.com/d/quotes.csv?s= <DOWNLOADS_SYMBOLS> &f= <DOWNLOAD_TAGS>
		
		Symbols to be tracked should be stored in a file "stock_symbols.txt"
		
		Tags to download should be stored at the beginning of the file "stock_symbols.txt"



		// To download history
		Example URL = "http://ichart.finance.yahoo.com/table.csv?s=AAPL&c=1962"

		URL = "http://ichart.finance.yahoo.com/table.csv?s={0}&c={1}"
			{0} is the ticker such as "APPL"
			{1} is the year to start from



		// To download historical data from start date 1/1/2016 to 7/1/2016
		// Each data point takes place on a Monday
		http://ichart.finance.yahoo.com/table.csv?s=GOOG&a=0&b=1&c=2016&d=6&e=1&f=2016&g=w&ignore=.csv

		// Detailed URL
		http://ichart.finance.yahoo.com/table.csv?s=" & ticker & "&a=" & (startDate.Month - 1) & "&b=" & startDate.Day & "&c=" & startDate.Year & "&d=" & (endDate.Month - 1) & "&e=" & endDate.Day & "&f=" & endDate.Year & "&g=w&ignore=.csv"
*/
class DownloadManager
{
public:
	// This creates and initializes the stocks to track and what symbols to track.
	// Does not update stocks on creation, user must call udpate().
	DownloadManager();

	~DownloadManager();



	// Updates all stock prices and their history.
	// Returns 0 if the update failed. Otherwise it returns 1 for success.
	int update();

	// Updates the current stock prices
	// Returns 0 if the update failed. Otherwise it returns 1 for success.
	int updateCurrentPrices();

	/*	Updates the history data for all stock symbols stored in _symbols.
		Downloads history from _startDate to _endDate. (1/1/1980 to CURRENT DATE)
		This only updates if there is no recorded data for the given stock.
		This function has to be called after all symbols have been loaded.
		Will output an error message if the history could not be download for a given stock. */
	void updateHistoryData();

	// Downloads the historical data for the given stock
	// Returns 0 - fail and 1 - success
	int downloadHistory(Symbol symbol, Date startDate, Date endDate);

	// Returns a URL for the given Symbol needed to download the history data file from
	// Yahoo Finance API from startDate to endDate.
	wstring getHistoryDownloadURL(Symbol symbol, Date startDate, Date endDate) const;



	// Returns a wstring containing the URL needed to download all the wanted information
	// from the Yahoo Finance API
	wstring getDownloadURL() const;
	
	// Returns a wstring containing all tracked symbols separated by '+'. Ex "APPL+GOOG+MSFT"
	// If the number of symbols being tracked is < 1, it returns an empty wstring "".
	wstring getSymbols() const;
	
	// Returns a wstring of the tags to download.
	wstring getTags() const;



	// Updates the starting date
	// Returns 0 if the update failed. Otherwise it returns 1 for success.
	int setStartDate(Date* date);

	// Updates the ending date
	// Returns 0 if the update failed. Otherwise it returns 1 for success.
	int setEndDate(Date* date);

private:
	// Filename of symbols to track
	const wstring STOCKS_SYMS_FILENAME = L"stock_symbols.txt";

	// Filename of tags to download. ex Price, volume, closing price
	const wstring STOCKS_TAGS_FILENAME = L"stock_tags.txt";

	// Filename to where stock current stock prices are downloaded to.
	const wstring DOWNLOAD_FILENAME = L"stocks_download.txt";
	
	// Turns ON/OFF debug messages
	const bool DEBUG = FALSE;



	// Vector of symbols currently being tracked, reduces file reading at 
	// the expense of a more memory usage
	vector<Symbol> _symbols;

	// Tags used to idenfity what information to download. Such as price, volume.
	wstring _tags;



	// Start date of history download (1/1/1980)
	Date* _startDate;

	// End date of history download (CURRENT DATE)
	Date* _endDate;



	// Loads the symbols to track onto vector _symbols
	// Returns 0 if the loading failed. Otherwise it returns 1 for success.
	int loadSymbols();

	// Loads the tags to track onto the string _tags
	// Returns 0 if the loading failed. Otherwise it returns 1 for success.
	// If the loading failed _tags will be set to an empty string L"".
	int loadTags();

	// Removes unwanted characters, and adds whitespace
	void cleanCurrentPricesFile();

	// Removes unwated characters, and adds whitespace
	// Returns 0 if the cleanup failed. Otherwise it returns 1 for success.
	int cleanHistoryFile(string filename);
};

#endif