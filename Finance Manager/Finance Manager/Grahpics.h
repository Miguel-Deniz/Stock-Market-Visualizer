#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SLF.h"
#include <FL\Fl.H>
#include <FL\Fl_Widget.H>
#include <FL\fl_draw.H>

/*
	Author: Miguel Deniz Lopez
	Date:   8/2/16

	Last Update: 8/2/16 4:05 PM
*/

struct Point
{
	int x;
	int y;
};

//--------------------------------------------------------------

// A line consisting of multiple points connected together
// Will not draw if there are no points
class ConnectedLine
{
public:
	ConnectedLine();

	// Adds a point to the end of the line
	void addPoint(Point p);

	// Returns the number of points in the line
	int getSize() const;

	int getMinX() const;

	int getMaxX() const;

	int getMinY() const;

	int getMaxY() const;

	Fl_Color getColor() const;


	void setColor(Fl_Color color);



	// Subscript overload to access a given point at an index
	Point& operator[] (const int index);

private:
	std::vector<Point> _points;
	Fl_Color _color;
};

//--------------------------------------------------------------

class Graphics_Text : public Fl_Widget
{
private:
	Fl_Color _color;
	const char* _str;
public:
	void draw();
public:
	Graphics_Text(int x, int y, int width, int height, Fl_Color c, const char* str);
};

//--------------------------------------------------------------

class Graphics_Rectangle : public Fl_Widget
{
private:
	Fl_Color _color;

	void draw();
public:
	Graphics_Rectangle(int x, int y, int width, int height, Fl_Color c);
};

//--------------------------------------------------------------

// Draws and XY cartisian style graph with bottom left corner at (x,y).
class Graphics_Graph : public Fl_Widget
{
public:
	Graphics_Graph(int x, int y, int width, int height, Fl_Color c);

	void addLine(ConnectedLine line);

	void draw();

	int x() const;
	int y() const;
	int w() const;
	int h() const;

	void clear();
	
private:
	// X-Coordinate position of top left of the graph
	int _xPos;
	// Y-Coordinate position of the top left of the graph
	int _yPos;
	// Width of the graph
	int _width;
	// Height of the graph
	int _height;

	int getMinX() const;

	int getMinY() const;

	int getMaxX() const;

	int getMaxY() const;

	void changeColor(int i);

	Fl_Color _color;
	Point _origin;
	std::vector<ConnectedLine> _lines;
};

//--------------------------------------------------------------

// This class draws either an up or down arrow depending on the direction.
// If the direction is up, the arrow points up and is shaded green.
// If the direction is down, the arrow points down and is shaded red.
class Graphics_DownRect : public Fl_Widget
{
public:
	Graphics_DownRect(int x, int y, int dir);

	//Direction getDirection() const;

	void draw();
private:
	// Constants
	const int WIDTH = 10;
	const int HEIGHT = 10;

	int _direction;

	int _xCord;
	int _yCord;

	void drawDownArrow() const;
	void drawUpArrow() const;
};

#endif