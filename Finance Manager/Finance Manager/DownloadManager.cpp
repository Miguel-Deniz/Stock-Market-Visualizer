#include "DownloadManager.h"

DownloadManager::DownloadManager()
{
	_startDate = new Date(1, 1, 1980);		// START 1/1/2010
	_endDate = new Date();					// Set to current date

	loadSymbols();
	loadTags();
}

DownloadManager::~DownloadManager()
{
	delete _startDate;
	delete _endDate;
}

int DownloadManager::update()
{
	int result = updateCurrentPrices();

	// Does not return a flag, it displays an error message for each individual download attempt.
	updateHistoryData();
	
	return result;
}

int DownloadManager::updateCurrentPrices()
{
	cout << "\nStarting update...\n\n";

	wstring URL = getDownloadURL();

	if (DEBUG)
	{
		wcout << "Debug -- " << DOWNLOAD_FILENAME << endl;
		wcout << "Debug -- " << URL << endl;
	}

	HRESULT result = URLDownloadToFile(0, URL.c_str(), DOWNLOAD_FILENAME.c_str(), 0, 0);
	
	if (FAILED(result))
	{
		cout << "Unable to update stock prices..." << endl;
		return 0;
	}
	else
	{
		cout << "Successfully updated stock prices..." << endl;
		cleanCurrentPricesFile();
		return 1;
	}
}

void DownloadManager::updateHistoryData()
{
	for (int index = 0; index < _symbols.size(); ++index)
	{
		int result = downloadHistory(_symbols.at(index), *_startDate, *_endDate);

		if (result == FAILED)
		{
			string message = "Could not download historical data for stock: " +
				_symbols.at(index).getSymbol();

			warning(message);
		}
		else
		{
			string filename = _symbols.at(index).getSymbol() + "_HISTORICAL_DATA.txt";
			cleanHistoryFile(filename);
			reverseFile(filename);
		}
	}
}

int DownloadManager::downloadHistory(Symbol symbol, Date startDate, Date endDate)
{
	//cout << "Starting update...\n";
	//cout << "Downloading " << symbol.getSymbol() << " historical data..." << endl;

	wstring URL = getHistoryDownloadURL(symbol, startDate, endDate);
	wstring destinationFile = stringToWString(symbol.getSymbol()) + L"_HISTORICAL_DATA.txt";

	HRESULT result = URLDownloadToFile(0, URL.c_str(), destinationFile.c_str(), 0, 0);

	if (FAILED(result))
	{
		//cout << "Unsuccessfully updated " << symbol << "historical stock prices...\n";
		return FAILED;
	}
	else
	{
		cout << "Successfully updated " << symbol << " historical stock prices...\n";
		cleanCurrentPricesFile();
		return SUCCESS;
	}
}

wstring DownloadManager::getHistoryDownloadURL(Symbol symbol, Date startDate, Date endDate) const
{
	// URL FORMAT
	http://ichart.finance.yahoo.com/table.csv?s=" & ticker & "&a=" & (startDate.Month - 1) & "&b=" & startDate.Day & "&c=" & startDate.Year & "&d=" & (endDate.Month - 1) & "&e=" & endDate.Day & "&f=" & endDate.Year & "&g=w&ignore=.csv"

	wstring base_url = L"http://ichart.finance.yahoo.com/table.csv?s=";
	wstring sym = stringToWString(symbol.getSymbol());
	wstring separator1 = L"&a=";
	
	wstring startMonth = intToWStr(startDate.getMonth() - 1);
	wstring separator2 = L"&b=";
	wstring startDay = intToWStr(startDate.getDay());
	wstring separator3 = L"&c=";
	wstring startYear = intToWStr(startDate.getYear());
	wstring separator4 = L"&d=";

	wstring endMonth = intToWStr(endDate.getMonth() - 1);
	wstring separator5 = L"&e=";
	wstring endDay = intToWStr(endDate.getDay());
	wstring separator6 = L"&f=";
	wstring endYear = intToWStr(endDate.getYear());

	wstring endurl = L"&g=w&ignore=.csv";

	wstring url = base_url + sym + separator1 +
		startMonth + separator2 +
		startDay + separator3 +
		startYear + separator4 +
		endMonth + separator5 +
		endDay + separator6 +
		endYear + endurl;

	return url;
}

wstring DownloadManager::getDownloadURL() const
{
	// URL = http://finance.yahoo.com/d/quotes.csv?s= <DOWNLOADS_YMBOLS> &f= <DOWNLOAD_TAGS>
	//wstring url(L"http://finance.yahoo.com/d/quotes.csv?s=AAPL+GOOG+MSFT&f=nab");

	wstring base_url = L"http://finance.yahoo.com/d/quotes.csv?s=";
	wstring symbols = getSymbols();
	wstring middle_url = L"&f=";
	wstring tags = getTags();

	wstring URL = base_url + symbols + middle_url + tags;
	return URL;
}

wstring DownloadManager::getSymbols() const
{
	// Return an empty string if < 1 symbols
	if (_symbols.size() < 1) return L"";

	// Here we can assume we are working with 1 or more symbols
	string symbolsString = _symbols.at(0).getSymbol();

	// Starting at index 1 because we already included the first Symbol
	for (int index = 1; index < _symbols.size(); ++index)
		symbolsString += "+" + _symbols.at(index).getSymbol();

	return stringToWString(symbolsString);
}

wstring DownloadManager::getTags() const
{
	return _tags;
}

int DownloadManager::setStartDate(Date* date)
{
	if (date == NULL) return FAILED;

	delete _startDate;
	_startDate = date;

	return SUCCESS;
}

int DownloadManager::setEndDate(Date* date)
{
	if (date == NULL) return FAILED;

	delete _endDate;
	_endDate = date;

	return SUCCESS;
}

int DownloadManager::loadSymbols()
{
	// Returns 0 for failure
	// Returns 1 for success

	ifstream input(STOCKS_SYMS_FILENAME);
	if (!input)
	{
		error("Could not open stock data file for input");
		return FAILED;
	}

	string symbol;
	_symbols.clear();		// Remove all previous stored symbols, to avoid duplicates

	while (input >> symbol)
		_symbols.push_back(Symbol(symbol));

	return SUCCESS;
}

int DownloadManager::loadTags()
{
	ifstream input(STOCKS_TAGS_FILENAME);

	if (!input)
	{
		error("Could not load tags from file...");
		_tags = L"";
		return FAILED;
	}

	string firstLine;
	getline(input, firstLine);

	_tags = stringToWString(firstLine);

	return SUCCESS;
}

void DownloadManager::cleanCurrentPricesFile()
{
	/*
		To clean file:
			1. Rename stock data file, and create a temp copy
			2. Copy new formated text back to the new file from temp file
			3. Delete temp file
	*/

	string oldFileName = wstringToString(DOWNLOAD_FILENAME);
	string tempFilename = "temp_stock_data.txt";

	rename(oldFileName.c_str(), tempFilename.c_str());

	ifstream tempFile(tempFilename);
	if (!tempFile)
	{
		error("Could not open temp file: DownloadManager::cleanFile()");
		system("PAUSE");
		exit(1);
	}

	ofstream replacementFile(oldFileName);
	if (!replacementFile)
	{
		error("Could not open/create file: DownloadManager::cleanFile()");
		system("PAUSE");
		exit(1);
	}

	string line;
	while (getline(tempFile, line))
	{
		if (DEBUG) cout << "Debug -- Line: " << line << endl;
		line = removeChar(line, '"');
		replacementFile << line << endl;
	}

	// Remove temp file
	tempFile.close();
	remove(tempFilename.c_str());

	// Check if deletion was succesful
	ifstream ifs(tempFilename);
	if (ifs)
	{
		warning("Temp file was not deleted: DownloadManager::cleanFile()");
	}
}

int DownloadManager::cleanHistoryFile(string filename)
{
	/*
		To clean file:
			1. Create a temp file that will be used as the new clean file.
			2. Copy the desired information into the temp file from the original file
				removing any unwated characters and adding new spaces in between.
			3. Delete the original history file
			4. Rename the temp file to the same original history filename.
	*/

	string tempFileName = "temp_" + filename;

	// Create the temp file, and check if it was created successfully
	ofstream tempFile(tempFileName.c_str());
	if (!tempFile)
	{
		error("Unable to create a temp file in DownloadManager::cleanHistoryFile()");
		return FAILED;
	}

	// Copy desired information
	ifstream originalFile(filename);
	if (!originalFile)
	{
		error("Could not open file for cleanup in DownloadManager::cleanHistoryFile()");
		return FAILED;
	}

	// Remove the first line, it is only a guide
	string firstLine;
	getline(originalFile, firstLine);

	string line;
	while (getline(originalFile, line))
	{
		line = replaceChar(line, '-', ' ');
		line = replaceChar(line, ',', ' ');

		// Process each line for the desired information, to reach desired format
		stringstream ss(line);

		int year;
		int month;
		int day;
		double open;
		double high;
		double low;
		double close;
		double volume;
		double adjClose;

		ss >> year;
		ss >> month;
		ss >> day;
		ss >> open;
		ss >> high;
		ss >> low;
		ss >> close;
		ss >> volume;
		ss >> adjClose;

		// Add desired fields to the new file
		tempFile << setw(2) << setfill('0') <<  month << "/"  <<
			setw(2) << setfill('0') << day << "/" << year << " " <<
			fixed << setprecision(3) << adjClose << endl;
	}

	// Remove original file
	originalFile.close();
	remove(filename.c_str());

	// Rename temp file to original file
	tempFile.close();
	rename(tempFileName.c_str(), filename.c_str());

	return SUCCESS;
}
