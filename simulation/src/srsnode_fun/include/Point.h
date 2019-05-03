#ifndef POINT_INCLUDED
#define POINT_INCLUDED

#include <iostream>

class Point {
public:
	double x,y,z;
	Point();
	Point(double xin, double yin, double zin);
	void print();
};

#endif