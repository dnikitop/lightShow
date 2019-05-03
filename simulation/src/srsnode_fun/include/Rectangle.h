#ifndef RECTANGLE_INCLUDED
#define RECTANGLE_INCLUDED

#include "Color.h"
#include "Shape.h"

class Rectangle: public Shape {
public: 
	Rectangle(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, double lenz, Color col, double ce, int steps);
	Rectangle(double pos [], double rot [], double size [], Color col, double emit, int steps);
	void draw();
private:
	void init(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, double lenz, Color col, double ce, int steps);
};

#endif