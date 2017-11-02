#pragma once
#include <iostream>
#include <string>
using namespace std;

class Point {
public:
	Point(int, int, float, float, float);
	int getXcoodinate();
	int getYcoodinate();
	friend ostream &operator<<(ostream &, const Point &);

private:
	int x, y;
	float r, g, b;

};
