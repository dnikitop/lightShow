#ifndef CYLINDER_INCLUDED
#define CYLINDER_INCLUDED


#include "Color.h"
#include "Shape.h"

class Cylinder: public Shape {
public: 
	Cylinder(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, Color col, double ce, int faces, int steps);
	Cylinder(double pos [], double rot [], double size [], Color col, double emit, int faces, int steps);
	void draw();
private:
	void init(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, double lenz, Color col, double ce, int faces, int steps);
};

#endif