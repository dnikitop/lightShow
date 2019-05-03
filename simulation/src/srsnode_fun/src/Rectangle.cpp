#include "Rectangle.h"
#include "Color.h"
#include <iostream>
void Rectangle::init(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, double lenz, Color col, double ce, int steps){
	x = px;
	y = py;
	z = pz;
	rotx = rx;
	roty = ry;
	rotz = rz;
	wid = widx;
	hei = heiy;
	len = lenz;
	c.r = col.r;
	c.g = col.g;
	c.b = col.b;
	c.a = col.a;
	emit = ce;
	step = steps;
	mat_specular[0] = 0.0;
	mat_specular[1] = 0.0;
	mat_specular[2] = 0.0;
	mat_specular[3] = 1.0;
}

Rectangle::Rectangle(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, double lenz, Color col, double ce, int steps){
	init(px,py,pz,rx,ry,rz,widx,heiy,lenz,col,ce,steps);
}

Rectangle::Rectangle(double pos [], double rot [], double size [], Color col, double emit, int steps){
	init(pos[0],pos[1],pos[2],rot[0],rot[1],rot[2],size[0],size[1],size[2], col, emit, steps);
}

void Rectangle::draw(){
if(c.r != 0 || c.g != 0 || c.b != 0){

	glPushMatrix();
	glDraw();
	glBegin(GL_QUADS);
	double st = 1.0/step;
	glNormal3d(0,0,1.0);
	
	for(double i = -.5; i < .5; i+=st){
		for(double j = -.5; j < .5; j+= st){
			glVertex3d(i,j,.5);
			glVertex3d(i+st,j,.5);
			glVertex3d(i+st,j+st,.5);
			glVertex3d(i,j+st,.5);
		}
	}
	glNormal3d(0,0,-1.0);
	for(double i = -.5; i < .5; i+=st){
		for(double j = -.5; j < .5; j+= st){
			glVertex3d(i,j,-.5);
			glVertex3d(i,j+st,-.5);
			glVertex3d(i+st,j+st,-.5);
			glVertex3d(i+st,j,-.5);
		}
	}
	glNormal3d(0,1.0,0);
	for(double i = -.5; i < .5; i+=st){
		for(double j = -.5; j < .5; j+= st){
			glVertex3d(i,.5,j);
			glVertex3d(i,.5,j+st);
			glVertex3d(i+st,.5,j+st);
			glVertex3d(i+st,.5,j);
		}
	}
	glNormal3d(0,-1.0,0);
	for(double i = -.5; i < .5; i+=st){
		for(double j = -.5; j < .5; j+= st){
			glVertex3d(i,-.5,j);
			glVertex3d(i+st,-.5,j);
			glVertex3d(i+st,-.5,j+st);
			glVertex3d(i,-.5,j+st);
		}
	}
	glNormal3d(-1.0,0,0);
	for(double i = -.5; i < .5; i+=st){
		for(double j = -.5; j < .5; j+= st){
			glVertex3d(-.5,i,j);
			glVertex3d(-.5,i,j+st);
			glVertex3d(-.5,i+st,j+st);
			glVertex3d(-.5,i+st,j);
		}
	}
	glNormal3d(1.0,0,0);
	for(double i = -.5; i < .5; i+=st){
		for(double j = -.5; j < .5; j+= st){
			glVertex3d(.5,i,j);
			glVertex3d(.5,i+st,j);
			glVertex3d(.5,i+st,j+st);
			glVertex3d(.5,i,j+st);
		}
	}

	glEnd();
	glPopMatrix();
}
}