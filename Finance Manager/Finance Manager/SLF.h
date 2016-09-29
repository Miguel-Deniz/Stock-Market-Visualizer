/*
	Standard Library Functions (SLF)
	Author: Miguel Deniz Lopez
	Data:	1/7/16

	Documentation:

*/

#pragma once

#ifndef SLF_H
#define SLF_H

#include <FL\Fl_Widget.H>
#include <FL\fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/fl_draw.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/fl_ask.H>
#include <FL\Fl_Check_Button.H>
#include <FL\Fl_Toggle_Button.H>

#include <map>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>

#include "Grahpics.h"

using namespace std;

// Constant globals
// Use to flag a failure
const int FAILED = 0;

// Use to flag a success
const int SUCCESS = 1;

enum Direction { DOWN = 0, UP = 1 };

// String Operations
char* strReverse(char* str);

char* intToCharPtr(int n);

int containsChar(string str, char ch);

string stringToUpper(const string& str);

wstring stringToWString(const string& s);

int stringToWString(wstring& ws, const string& s);

string wstringToString(wstring wstr);

// Removes the given characters in a str from the given string.
// Does not alter original strings
// Ex. str = "Hello", characters = "l" , result = "Heo"
string removeChar(const string& str, const char character);

/* Creates a new string by replacing the given characters
	with the desired replacement string.
	Ex. str = "Hey", character = 'y', replacement = 'w': result = "Hew"

	Parameters:
		string str: source string
		char character: char to replace
		char replacement: replacement for char.
*/
string replaceChar(const string& str, const char character, const char replacement);

void error(std::string message);

void warning(std::string message);

/*	Converts a 32-bit number into a string.

Parameters:
	number - 32 bit integer
Returns:
	A string equivalent of the given 32-bit integer. */
string intToStr(int number);

// Converts an int to a wstring
wstring intToWStr(int number);

/*	Converts a 32-bit double into a string.

	Parameters:
		number - 32 bit double

	Returns:
		A string equivalent of the given 32-bit double. */
string dblToStr(double number);


// File operatioins
bool fileExists(string filename);

int reverseFile(string filename);

#endif