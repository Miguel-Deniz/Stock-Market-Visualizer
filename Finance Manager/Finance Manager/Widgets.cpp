#include "Widgets.h"

DateSelector::DateSelector(int x, int y, Fl_Color color)
	:Fl_Widget(x, y, WIDTH, HEIGHT), _xCord(x), _yCord(y), _color(color)
{
	int startXCord = _xCord + 9 * PADDING;
	int startYCord = _yCord + PADDING;
	_startMonth = new Fl_Choice(startXCord, startYCord, CHOICE_WIDTH, CHOICE_HEIGHT, "Start Date:");
	_startMonth->labelcolor(_color);
	_startDay = new Fl_Choice(startXCord + CHOICE_WIDTH + PADDING, startYCord, CHOICE_WIDTH, CHOICE_HEIGHT);
	_startYear = new Fl_Choice(startXCord + 2 * CHOICE_WIDTH + 2 * PADDING, startYCord, CHOICE_WIDTH, CHOICE_HEIGHT);

	int endXCord = startXCord;
	int endYCord = _yCord + 50;
	_endMonth = new Fl_Choice(endXCord, endYCord, CHOICE_WIDTH, CHOICE_HEIGHT, "End Date:");
	_endMonth->labelcolor(_color);
	_endDay = new Fl_Choice(endXCord + CHOICE_WIDTH + PADDING, endYCord, CHOICE_WIDTH, CHOICE_HEIGHT);
	_endYear = new Fl_Choice(endXCord + 2 * CHOICE_WIDTH + 2 * PADDING, endYCord, CHOICE_WIDTH, CHOICE_HEIGHT);

	init();
}

int DateSelector::getStartMonth() const
{
	return _startMonth->value() + 1;
}

int DateSelector::getStartDay() const
{
	return _startDay->value() + 1;
}

int DateSelector::getStartYear() const
{
	return _startYear->value() + MIN_YEAR;
}

int DateSelector::getEndMonth() const
{
	return _endMonth->value() + 1;
}

int DateSelector::getEndDay() const
{
	return _endDay->value() + 1;
}

int DateSelector::getEndYear() const
{
	return _endYear->value() + MIN_YEAR;
}

Date DateSelector::getStartDate() const
{
	return Date(getStartMonth(), getStartDay(), getStartYear());
}

Date DateSelector::getEndDate() const
{
	return Date(getEndMonth(), getEndDay(), getEndYear());
}

void DateSelector::draw()
{
	fl_color(_color);
	fl_rect(_xCord, _yCord, WIDTH, HEIGHT);
}

void DateSelector::init()
{
	for (int month = 1; month <= 12; ++month)
	{
		_startMonth->add(intToStr(month).c_str());
		_endMonth->add(intToStr(month).c_str());
	}

	for (int day = 1; day <= 31; ++day)
	{
		_startDay->add(intToStr(day).c_str());
		_endDay->add(intToStr(day).c_str());
	}

	int numberOfYears = 0;
	for (int year = MIN_YEAR; year <= MAX_YEAR; ++year)
	{
		_startYear->add(intToStr(year).c_str());
		_endYear->add(intToStr(year).c_str());
		numberOfYears++;
	}

	_startMonth->value(0);
	_startDay->value(0);
	_startYear->value(0);

	_endMonth->value(0);
	_endDay->value(0);
	_endYear->value(numberOfYears - 1);
}


//------------------------------------------------------------------------------


ToggleButton::ToggleButton(int X, int Y, int W, int H, string label)
	:Fl_Button(X, Y, W, H, label.c_str()),
	_active(false),
	_color(FL_WHITE)
{}

void ToggleButton::draw()
{
	// Fill button color
	fl_color(_color);
	fl_rectf(x(), y(), w(), h());

	// Draw diagonal
	if (_active)
	{
		if (_color == FL_WHITE)
			fl_color(FL_BLACK);
		else
			fl_color(FL_WHITE);

		fl_line(x(), y(), x() + w(), y() + h());
		fl_line(x() + w(), y(), x(), y() + h());
	}

	// Draw border
	fl_color(FL_BLACK);
	fl_rect(x(), y(), w(), h());
}

int ToggleButton::handle(int event)
{
	// Determine if the event was a mouse event
	if (event == FL_PUSH)
	{
		int buttonEvent = Fl::event_button();

		//cout << "Event = " << event << endl;
		//cout << "X = " << buttonEvent << endl;

		if (buttonEvent == FL_LEFT_MOUSE)
		{
			// Activate button
			toggleActivation();
			redraw();
			return 1;
		}
		else if (buttonEvent == FL_RIGHT_MOUSE)
		{
			// Here we toggle the color
			toggleColor();
			redraw();
			return 1;
		}
		else if (buttonEvent == FL_MIDDLE_MOUSE)
		{
			// Reset here
		}
	}

	return 0;		// Event not handled
}

void ToggleButton::toggleActivation()
{
	if (_active == false)
		_active = true;
	else
		_active = false;
}

void ToggleButton::toggleColor()
{
	if (_color == FL_WHITE)
		_color = FL_RED;
	else if (_color == FL_RED)
		_color = FL_BLUE;
	else if (_color == FL_BLUE)
		_color = FL_GREEN;
	else if (_color == FL_GREEN)
		_color = FL_MAGENTA;
	else if (_color == FL_MAGENTA)
		_color = FL_CYAN;
	else
		_color = FL_WHITE;
}

bool ToggleButton::isActive() const
{
	return _active;
}

Fl_Color ToggleButton::getColor() const
{
	return _color;
}

DirectionalButton::DirectionalButton(int X, int Y, int W, int H, int direction)
	:Fl_Button(X, Y, W, H),
	X_CORD(X), Y_CORD(Y), WIDTH(W), HEIGHT(H),
	_direction(direction)
{

}

void DirectionalButton::draw()
{
	Fl_Button::position(X_CORD, Y_CORD);
	Fl_Button::size(WIDTH, HEIGHT);
	Fl_Button::draw();

	if (_direction == 0)
	{
		fl_color(FL_RED);
		int x1 = X_CORD + PADDING;
		int y1 = Y_CORD + PADDING;
		int x2 = X_CORD + WIDTH - PADDING;
		int y2 = Y_CORD + PADDING;
		int x3 = X_CORD + WIDTH / 2;
		int y3 = Y_CORD + HEIGHT - PADDING;

		fl_polygon(x1, y1, x2, y2, x3, y3);
	}
	else
	{
		fl_color(FL_GREEN);
		int x1 = X_CORD + WIDTH / 2;
		int y1 = Y_CORD + PADDING;
		int x2 = X_CORD + PADDING;
		int y2 = Y_CORD + HEIGHT - PADDING;
		int x3 = X_CORD + WIDTH  - PADDING;
		int y3 = Y_CORD + HEIGHT - PADDING;

		fl_polygon(x1, y1, x2, y2, x3, y3);
	}

	//fl_color(FL_BLACK);
	//fl_rect(X_CORD, Y_CORD, WIDTH, HEIGHT);
}
