#include "Bresenham.h"

Bresenham::Bresenham(int maxx, int maxy)
{
	init(maxx, maxy);
}

void Bresenham::line(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1;
	int e = 0;

	put(x1, y1,1);
	while (x1 <= x2) {
		if (e + 2 * dy<dx) {
			x1++;
			e += 2 * dy;
			put(x1, y1, 1);
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

	put(xc, yc, x, y);
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
		put(xc, yc, x, y);
	}
}

void Bresenham::polygon()
{
	buffer[150][200] = 1;
	buffer[100][300] = 1;
	// l2
	buffer[150][200] = 1;
	buffer[300][ 200] = 1;

	// l3
	buffer[300][200] = 1;
	buffer[350][ 300] = 1;

	// l3
	buffer[100] [300] = 1;
	buffer[350][300] = 1;

	// l5
	buffer[200][300] = 1;
	buffer[250][350] = 1;

	// l6
	buffer[250][350] = 1;
	buffer[350][300] = 1;

}


void Bresenham::init(int maxx, int maxy)
{
	for (int x = 0; x< maxx; x++) {
		vector <int> temp;
		for (int y = 0; y< maxy; y++)
		{
			temp.push_back(0);
		}
		buffer.push_back(temp);
	}
}

// Effectually put the desired point, the calculated point, in the buffer;
void Bresenham::put(int x, int y, int value) {
	if ((x<0) || (x>buffer.size() || (y<0) || (y>buffer[0].size()))) {
		cout <<"Range error "<< x << " " << y << endl;
		exit(1);
	}
	buffer[x][y] = value;
}

void Bresenham::put(int xc, int yc, int x, int y)
{
	if ((x == 0) && (y == 0)) {
		put(xc, yc, 1);
		return;
	}
	put((xc + x), (yc + y),1);
	put((xc + x), (yc - y),1);
	put((xc - x), (yc - y),1);
	put((xc - x), (yc + y),1);
	put((xc + y), (yc + x),1);
	put((xc + y), (yc - x),1);
	put((xc - y), (yc + x),1);
	put((xc - y), (yc - x),1);
}

ostream& operator<<(std::ostream &out, std::vector<std::vector<int>> const&v) {
	for (auto &&i : v) {
		for (auto &&j : i) out << j << " ";
		out << std::endl;
	}
	return out;
}