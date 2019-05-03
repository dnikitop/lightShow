#include "Shape.h"

void Shape::glDraw(){
	mat_shininess = 0.0;
    mat_ambient[0] = c.r;
    mat_ambient[1] = c.g;
    mat_ambient[2] = c.b;
    mat_ambient[3] = c.a;
    mat_diffuse[0] = c.r;
    mat_diffuse[1] = c.g;
    mat_diffuse[2] = c.b;
    mat_diffuse[3] = c.a;
    mat_emission[0] = c.r*emit;
    mat_emission[1] = c.g*emit;
    mat_emission[2] = c.b*emit;
    mat_emission[3] = 1.0;
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(x, y, z);
	glRotated(rotx, 1.0f, 0.0f, 0.0f);
	glRotated(roty, 0.0f, 1.0f, 0.0f);
	glRotated(rotz, 0.0f, 0.0f, 1.0f);	
	glScaled(wid,hei,len);
};