#pragma once

#ifndef WIDGETS_H
#define WIDGETS_H

#include "SLF.h"
#include "Calendar.h"


//------------------------------------------------------------------------------


// This class gives the user the option to select a range between
// two dates.
class DateSelector : public Fl_Widget
{
public:
	DateSelector(int x, int y, Fl_Color color = FL_WHITE);

	int getStartMonth() const;
	int getStartDay() const;
	int getStartYear() const;

	int getEndMonth() const;
	int getEndDay() const;
	int getEndYear() const;

	Date getStartDate() const;

	Date getEndDate() const;

	void draw();
private:
	// Constants
	const int WIDTH = 300;
	const int HEIGHT = 90;

	const int PADDING = 10;
	const int CHOICE_WIDTH = 60;
	const int CHOICE_HEIGHT = 30;

	const int MIN_YEAR = 1980;
	const int MAX_YEAR = 2016;

	Fl_Color _color;

	Fl_Choice* _startMonth;
	Fl_Choice* _startDay;
	Fl_Choice* _startYear;

	Fl_Choice* _endMonth;
	Fl_Choice* _endDay;
	Fl_Choice* _endYear;

	int _xCord;
	int _yCord;

	void init();
};


//------------------------------------------------------------------------------


class ToggleButton : public Fl_Button
{
public:
	ToggleButton(int X, int Y, int W, int H, string label);

	void draw();

	int handle(int event);

	bool isActive() const;

	Fl_Color getColor() const;
private:
	bool _active;
	Fl_Color _color;;

	// If the button is activated then it is deactivated, and vice versa
	void toggleActivation();

	// Rotates color
	void toggleColor();
};


//------------------------------------------------------------------------------

class DirectionalButton : public Fl_Button
{
public:
	// A button with an arrow pointing up or down
	// 0 down
	// 1 or anything else up
	DirectionalButton(int X, int Y, int W, int H, int direction);

	void draw();

private:
	// Top left coordinaes
	const int X_CORD;
	const int Y_CORD;
	const int WIDTH;
	const int HEIGHT;

	const int PADDING = 10;

	int _direction;
};

//------------------------------------------------------------------------------


#endif