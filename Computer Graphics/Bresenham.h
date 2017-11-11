#pragma once
#include<vector>
#include<iostream>

using namespace std;

class Bresenham
{
public:
	Bresenham(int, int);
	void line(int, int, int, int);
	void circle(int, int, int);
	void square();
	void polygon();
	vector<vector<int>>buffer;// declare my bidimentional array used as frame buffer;
	friend ostream& operator<<(ostream &, vector<vector<int>> const&);

private:
	// initialize, or in other words, populate it wiht 0's.
	void init(int, int); 
	// Used to record the coordinates of the line.
	void put(int, int, int); 
	// Used to record the coordinates of the circle.
	void put(int, int, int, int);
	
	int xmin;
	int xmax;
	int ymin;
	int ymax;

	const int INSIDE = 0; // 0000
	const int LEFT = 1;   // 0001
	const int RIGHT = 2;  // 0010
	const int BOTTOM = 4; // 0100
	const int TOP = 8;    // 1000

};
