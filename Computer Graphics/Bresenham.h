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
	void polygon();
	vector<vector<int>>buffer;// declare my bidimentional array used as frame buffer;
	friend ostream& operator<<(std::ostream &out, std::vector<std::vector<int>> const&v);

private:
	// initialize, or in other words, populate it wiht 0's.
	void init(int, int); 
	// Used to record the coordinates of the line.
	void put(int, int, int); 
	// Used to record the coordinates of the circle.
	void put(int, int, int, int);
	
};
