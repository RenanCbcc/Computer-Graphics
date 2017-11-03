#pragma once
#include<vector>
#include "Point.h"
using namespace std;

class Bresenham
{
public:
	Bresenham(int, int);
	void line(int, int, int, int);
	void circle(int, int, int);
	vector<Point> point;
private:
	void paint(int, int);
	void setpt(int, int, int, int);
	int max, min;
};
