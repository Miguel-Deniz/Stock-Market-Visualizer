#include "SLF.h"

char* strReverse(char* str)
{
	char *start, *end;
	int len;
	char t;

	len = strlen(str);

	start = str;
	end = str + len - 1;

	while (start < end)
	{
		t = *start;
		*start = *end;
		*end = t;

		start++;
		end--;
	}

	return str;
}

char* intToCharPtr(int n)
{
	char* str = new char[80];
	int index = 0;
	int negative = 0;

	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		index++;
		negative = 1;
	}

	while (n)
	{
		int r = n % 10;
		str[index] = r + '0';
		n = n / 10;
		index++;
	}

	str[index] = '\0';

	// Reduced unused space, from 80 to ????
	// Before it could be str = "145\00000000000000000000000000000000"
	// After			  str = "145\0"
	int len = strlen(str);
	char* newChar = new char[len + 1];
	strcpy(newChar, str);

	if (negative)
		strReverse(newChar + 1);
	else
		strReverse(newChar);

	return newChar;
}

int containsChar(string str, char ch)
{
	int contains_character = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) == ch) contains_character = 1;
	}


	return contains_character;
}

string stringToUpper(const string& str)
{
	string newStr = "";

	for (int i = 0; i < str.length(); ++i)
	{
		newStr += toupper(str.at(i));
	}

	return newStr;
}

wstring stringToWString(const string& s)
{
	wstring wsTmp(s.begin(), s.end());
	return wsTmp;
}

int stringToWString(wstring& ws, const string& s)
{
	wstring wsTmp(s.begin(), s.end());
	ws = wsTmp;
	return 0;
}

string wstringToString(wstring wstr)
{
	string tmp(wstr.begin(), wstr.end());
	return tmp;
}

string removeChar(const string& str, const char character)
{
	string newStr;

	for (int strIndex = 0; strIndex < str.length(); ++strIndex)
	{
		if (str.at(strIndex) != character)
			newStr += str.at(strIndex);
	}

	return newStr;
}

string replaceChar(const string& str, const char character, const char replacement)
{
	string newStr;

	for (int strIndex = 0; strIndex < str.length(); ++strIndex)
	{
		if (str.at(strIndex) == character)
			newStr += replacement;
		else
			newStr += str.at(strIndex);
	}

	return newStr;
}





void error(std::string message)
{
	std::cout << "Error: " << message << endl;
}

void warning(std::string message)
{
	cout << "Warning: " << message << endl;
}



string intToStr(int number)
{
	ostringstream ss;
	ss << number;
	return ss.str();
}

wstring intToWStr(int number)
{
	return stringToWString(intToStr(number));
}

string dblToStr(double number)
{
	ostringstream s;
	s << number;
	return s.str();
}



bool fileExists(string filename)
{
	ifstream ifs(filename);
	if (!ifs)
		return false;
	else
		return true;
}

int reverseFile(string filename)
{
	string tempFile = "reverse_" + filename;
	vector<string> fileLines;

	ifstream input(filename.c_str());
	if (!input)
	{
		error("Could not reverse file...");
		return 0;
	}

	string line;
	while (getline(input, line))
	{
		fileLines.push_back(line);
	}
	input.close();


	ofstream outFile(tempFile.c_str());

	std::vector<std::string>::reverse_iterator rIt;
	for (rIt = fileLines.rbegin(); rIt < fileLines.rend(); rIt++)
	{
		outFile << *rIt << endl;
	}
	outFile.close();


	// Rename and delete
	remove(filename.c_str());
	rename(tempFile.c_str(), filename.c_str());

	return 1;
}