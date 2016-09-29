#include "Grahpics.h"

//--------------------------------------------------------------

ConnectedLine::ConnectedLine()
	:_color(FL_WHITE)
{
}

void ConnectedLine::addPoint(Point p)
{
	_points.push_back(p);
}

int ConnectedLine::getSize() const
{
	return _points.size();
}

int ConnectedLine::getMinX() const
{
	int min = 1000000;

	for (int index = 0; index < _points.size(); ++index)
	{
		if (_points.at(index).x < min) min = _points.at(index).x;
	}

	return min;
}

int ConnectedLine::getMaxX() const
{
	int max = -1000000;

	for (int index = 0; index < _points.size(); ++index)
	{
		if (_points.at(index).x > max) max = _points.at(index).x;
	}

	return max;
}

int ConnectedLine::getMinY() const
{
	int min = 1000000;

	for (int index = 0; index < _points.size(); ++index)
	{
		if (_points.at(index).y < min) min = _points.at(index).y;
	}

	return min;
}

int ConnectedLine::getMaxY() const
{
	int max = -1000000;

	for (int index = 0; index < _points.size(); ++index)
	{
		if (_points.at(index).y > max) max = _points.at(index).y;
	}

	return max;
}

Fl_Color ConnectedLine::getColor() const
{
	return _color;
}

void ConnectedLine::setColor(Fl_Color color)
{
	_color = color;
}

Point& ConnectedLine::operator[] (const int index)
{
	if (index < 0 || index >= _points.size())
	{
		error("Out of range access - ConnectedLine index");
		system("PAUSE");
		exit(1);
	}

	return _points.at(index);
}

//--------------------------------------------------------------

Graphics_Text::Graphics_Text(int x, int y, int width , int height, Fl_Color c, const char* str)
	:Fl_Widget(x, y, width, height), _color(c), _str(str)
{
	//strcpy(_str, str);
}

void Graphics_Text::draw()
{
	fl_color(_color);
	fl_draw(_str, x(), y());
}

//--------------------------------------------------------------

void Graphics_Rectangle::draw()
{
	fl_color(_color);
	fl_rect(x(), y(), w(), h());
}

Graphics_Rectangle::Graphics_Rectangle(int x, int y, int width, int height, Fl_Color c)
	:Fl_Widget(x, y, width, height), _color(c)
{}

//--------------------------------------------------------------

Graphics_Graph::Graphics_Graph(int x, int y, int width, int height, Fl_Color c)
	:Fl_Widget(x, y, width, height), _xPos(x), _yPos(y), _width(width), _height(height), _color(c)
{
	_origin.x = x;
	_origin.y = y + height;
}

void Graphics_Graph::addLine(ConnectedLine line)
{
	_lines.push_back(line);
}

int Graphics_Graph::x() const
{
	return _xPos;
}

int Graphics_Graph::y() const
{
	return _yPos;
}

int Graphics_Graph::w() const
{
	return _width;
}

int Graphics_Graph::h() const
{
	return _height;
}

void Graphics_Graph::clear()
{
	_lines.clear();
}

int Graphics_Graph::getMinX() const
{
	int min = 1000000;

	if (_lines.size() > 0)
		min = _lines.at(0).getMinX();
	else
		return 0;

	for (int index = 1; index < _lines.size(); ++index)
	{
		if (_lines.at(index).getMinX() < min) min = _lines.at(index).getMinX();
	}

	return min;
}

int Graphics_Graph::getMinY() const
{
	int min = 1000000;

	if (_lines.size() > 0)
		min = _lines.at(0).getMinY();
	else
		return 0;

	for (int index = 1; index < _lines.size(); ++index)
	{
		if (_lines.at(index).getMinY() < min) min = _lines.at(index).getMinY();
	}

	return min;
}

int Graphics_Graph::getMaxX() const
{
	int max = -1000000;

	if (_lines.size() > 0)
		max = _lines.at(0).getMaxX();
	else
		return 0;

	for (int index = 1; index < _lines.size(); ++index)
	{
		if (_lines.at(index).getMaxX() > max) max = _lines.at(index).getMaxX();
	}

	return max;
}

int Graphics_Graph::getMaxY() const
{
	int max = -1000000;

	if (_lines.size() > 0)
		max = _lines.at(0).getMaxY();
	else
		return 0;

	for (int index = 1; index < _lines.size(); ++index)
	{
		if (_lines.at(index).getMaxY() > max) max = _lines.at(index).getMaxY();
	}

	return max;
}

void Graphics_Graph::changeColor(int i)
{
	if (i % 4 == 0)
		_color = FL_RED;
	else if (i % 4 == 1)
		_color = FL_GREEN;
	else if (i % 4 == 2)
		_color = FL_BLUE;
	else if (i % 4 == 3)
		_color = FL_MAGENTA;

	fl_color(_color);
}

void Graphics_Graph::draw()
{
	fl_color(FL_BLACK);
	// X-Axis
	fl_rectf(x(), y(), _width, _height);

	// Get Min/Max values
	int minX = getMinX();
	int minY = getMinY();
	int maxX = getMaxX();
	int maxY = getMaxY();

	// Draw all lines
	for (int i = 0; i < _lines.size(); ++i)
	{
		//changeColor(i);                          REMOVE

		ConnectedLine tempLine = _lines.at(i);
		fl_color(tempLine.getColor());

		if (tempLine.getSize() > 2)
		{
			for (int lineIndex = 0; lineIndex < tempLine.getSize() - 1; ++lineIndex)
			{
				double point1X = (double)tempLine[lineIndex].x;
				double point1Y = (double)tempLine[lineIndex].y;
				double point2X = (double)tempLine[lineIndex + 1].x;
				double point2Y = (double)tempLine[lineIndex + 1].y;

				int x1 = _origin.x + ((point1X - minX) / (maxX - minX)) * _width;
				int y1 = _origin.y - ((point1Y - minY) / (maxY - minY)) * _height;
				int x2 = _origin.x + ((point2X - minX) / (maxX - minX)) * _width;
				int y2 = _origin.y - ((point2Y - minY) / (maxY - minY)) * _height;

				//cout << x1 << " " << y1 << " -- " << x2 << " " << y2 << endl;

				fl_line(x1, y1, x2, y2);
			}
		}
	}

	fl_color(FL_WHITE);
	fl_rect(x(), y(), _width, _height);
}

Graphics_DownRect::Graphics_DownRect(int x, int y, int dir)
	:Fl_Widget(x, y, WIDTH, HEIGHT), _xCord(x), _yCord(y), _direction(dir)
{
	
}


void Graphics_DownRect::draw()
{
	if (_direction == 0)
		drawDownArrow();
	else
		drawUpArrow();
}

void Graphics_DownRect::drawDownArrow() const
{
	int x1 = _xCord;
	int y1 = _yCord;
	int x2 = _xCord + WIDTH;
	int y2 = _yCord;
	int x3 = _xCord + WIDTH / 2;
	int y3 = _yCord + HEIGHT;

	fl_color(FL_RED);
	fl_polygon(x1, y1, x2, y2, x3, y3);
}

void Graphics_DownRect::drawUpArrow() const
{
	int x1 = _xCord + WIDTH / 2;
	int y1 = _yCord;
	int x2 = _xCord;
	int y2 = _yCord + HEIGHT;
	int x3 = _xCord + WIDTH;
	int y3 = _yCord + HEIGHT;

	fl_color(FL_GREEN);
	fl_polygon(x1, y1, x2, y2, x3, y3);
}