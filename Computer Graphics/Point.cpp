#include "Point.h"

using namespace std;

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
	
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