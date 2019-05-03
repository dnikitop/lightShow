#include "Cylinder.h"
#include <math.h>
#define PI 3.14159265



Cylinder::Cylinder(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, Color col, double ce, int faces, int steps){
	init(px,py,pz,rx,ry,rz,widx,heiy,widx,col,ce,faces,steps);
}

Cylinder::Cylinder(double pos [], double rot [], double size [], Color col, double emit, int faces, int steps){
	init(pos[0],pos[1],pos[2],rot[0],rot[1],rot[2],size[0],size[1],size[2],col,emit,faces, steps);
}
void Cylinder::init(double px, double py, double pz, double rx, double ry, double rz, double widx, double heiy, double lenz, Color col, double ce, int faces, int steps){
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
	mat_specular[3] = 0.0;
	for(int i = 0; i < faces; i++){
		Point temp(cos(i*2*PI/(faces)), .5, sin(i*2*PI/(faces)));
		points.push_back(temp);
	}
	for(int i = 0; i < faces; i++){
		Point temp(cos(i*2*PI/(faces)), -.5, sin(i*2*PI/(faces)));
		points.push_back(temp);
	}
	int size1 = points.size();
	for(int i = 0; i < points.size()/2; i++){
		Point norm1;
		norm1.x = cos(i*2*PI/(faces));
		norm1.y = 0;
		norm1.z = sin(i*2*PI/(faces));
		norms.push_back(norm1);
	}
}


void Cylinder::draw(){
if(c.r != 0 || c.g != 0 || c.b != 0){
	glPushMatrix();
	glDraw();
	glBegin(GL_QUADS);
	int size = points.size();
	for(int i = 0; i < points.size()/2; i++){
		for(double j = 0; j < 1.0; j+=1.0/step){
			glNormal3d(norms[i].x, norms[i].y, norms[i].z);
			glVertex3d(points[i].x,points[i].y-j,points[i].z);

			glNormal3d(norms[(i+1)%(size/2)].x, norms[(i+1)%(size/2)].y, norms[(i+1)%(size/2)].z);
			glVertex3d(points[(i+1)%(size/2)].x,points[i].y-j,points[(i+1)%(size/2)].z);

			glNormal3d(norms[(i+1)%(size/2)].x, norms[(i+1)%(size/2)].y, norms[(i+1)%(size/2)].z);
			glVertex3d(points[(i+1)%(size/2)+size/2].x,points[i].y-(j+1.0/step),points[(i+1)%(size/2)+size/2].z);
			
			glNormal3d(norms[i].x, norms[i].y, norms[i].z);
			glVertex3d(points[i+size/2].x,points[i].y-(j+1.0/step),points[i+size/2].z);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < points.size()/2; i++){
		glNormal3d(0.0f,1.0f,0.0f);
		glVertex3d(0,.5,0);
		glVertex3d(points[i].x,points[i].y,points[i].z);
		glVertex3d(points[(i+1)%(size/2)].x,points[(i+1)%(size/2)].y,points[(i+1)%(size/2)].z);
	}
	for(int i = 0; i < points.size()/2; i++){
		glNormal3d(0.0f,-1.0f,0.0f);
		glVertex3d(0,-.5,0);
		glVertex3d(points[(i+1)%(size/2) + size/2].x,points[(i+1)%(size/2) + size/2].y,points[size/2+(i+1)%(size/2)].z);
		glVertex3d(points[i + size/2].x,points[i + size/2].y,points[i + size/2].z);
		
	}
	glEnd();
	glPopMatrix();
}
}