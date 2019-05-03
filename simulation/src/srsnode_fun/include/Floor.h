#ifndef FLOOR_INCLUDED
#define FLOOR_INCLUDED

#include <vector>
#include "Point.h"
#include <GL/glut.h>

class Floor{
public:
	std::vector<Point> Points;
	Floor(float y, double sub);
	void draw();
};

#endif