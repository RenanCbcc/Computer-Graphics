#include "Bresenham.h"

Bresenham::Bresenham(int max, int min)
{
	this->max = max;
	this->min = min;
}

void Bresenham::line(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1;
	int e = 0;

	paint(x1, y1, 1.0, 0.0, 0.0);
	while (x1 <= x2) {
		if (e + 2 * dy<dx) {
			x1++;
			e += 2 * dy;
			paint(x1, y1, 1.0, 0.0, 0.0);
		}
		else {
			y1++;
			e -= 2 * dx;
		}
	}
}

void Bresenham::circle(int xc, int yc, int r)
{
	int x = 0, y = r;
	int e = 0;

	setpt(xc, yc, x, y);
	while (x != y) {
		if (e + 2 * x < y) {
			x++;
			e += 2 * x;
			setpt(xc, yc, x, y);
		}
		else {
			y--;
			e -= 2 * y;
		}
	}
}

void Bresenham::paint(int x, int y, float r, float g, float b) {
	point.push_back(Point(x, y, r, g, b));
}

void Bresenham::setpt(int xc, int yc, int x, int y)
{
	if ((x == 0) && (y == 0)) {
		paint(xc, yc, 0.0, 1.0, 0.0);
		return;
	}
	paint((xc + x), (yc + y), 0.0, 1.0, 0.0);
	paint((xc + x), (yc - y), 0.0, 1.0, 0.0);
	paint((xc - x), (yc - y), 0.0, 1.0, 0.0);
	paint((xc - x), (yc + y), 0.0, 1.0, 0.0);
	paint((xc + y), (yc + x), 0.0, 1.0, 0.0);
	paint((xc + y), (yc - x), 0.0, 1.0, 0.0);
	paint((xc - y), (yc + x), 0.0, 1.0, 0.0);
	paint((xc - y), (yc - x), 0.0, 1.0, 0.0);
}
