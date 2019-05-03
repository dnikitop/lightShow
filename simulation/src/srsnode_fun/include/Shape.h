#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED

#include <vector>
#include <GL/glut.h>
#include "Color.h"
#include "Point.h"

class Shape {
public:
	GLfloat mat_specular[4];
    GLfloat mat_ambient[4];
    GLfloat mat_shininess = 0;
    GLfloat mat_diffuse[4];
    GLfloat mat_emission[4];
	double x,y,z;
	double rotx,roty,rotz;
	double wid,hei,len;
	double step;
	Color c;
	float emit;
	std::vector<Point> points;
	std::vector<Point> norms;
	virtual void draw(){};
	void glDraw();
};

#endif