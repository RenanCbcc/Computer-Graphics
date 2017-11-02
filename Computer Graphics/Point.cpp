#include "Point.h"

using namespace std;

Point::Point(int x, int y, float r, float g, float b) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->g = g;
	this->b = b;
}

int Point::getXcoodinate()
{
	return this->x;
}

int Point::getYcoodinate()
{
	return this->y;
}

ostream & operator<<(ostream &output, const Point &point)
{
	output << "(" << point.x << "," << point.y << ") " << endl;
	return output;
}
