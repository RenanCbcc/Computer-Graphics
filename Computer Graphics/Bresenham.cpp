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

	paint(x1, y1);
	while (x1 <= x2) {
		if (e + 2 * dy<dx) {
			x1++;
			e += 2 * dy;
			paint(x1, y1);
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
	int p = 0;

	setpt(xc, yc, x, y);
	while (x < y) {
		x++;
		if (p < 0)
		{
			p += 2 * x + 3;
		}
		else
		{
			y--;
			p += 2 * (x - y) + 5;
		}
		setpt(xc, yc, x, y);
	}
}

void Bresenham::paint(int x, int y) {
	point.push_back(Point(x, y));
}

void Bresenham::setpt(int xc, int yc, int x, int y)
{
	if ((x == 0) && (y == 0)) {
		paint(xc, yc);
		return;
	}
	paint((xc + x), (yc + y));
	paint((xc + x), (yc - y));
	paint((xc - x), (yc - y));
	paint((xc - x), (yc + y));
	paint((xc + y), (yc + x));
	paint((xc + y), (yc - x));
	paint((xc - y), (yc + x));
	paint((xc - y), (yc - x));
}