#include "Floor.h"
#include <math.h>

Floor::Floor(float y, double sub){
	float range = 3;
	for(float i = -1*range; i <= 1*range; i+= 2*range/sub){
		for(float j = -1*range; j <= 1*range; j+= 2*range/sub){
			Points.push_back(Point(i,y,j));
		}
	}
}
void Floor::draw(){
	GLfloat mat_specular[] = { .2, .2, .2, 1.0 };
    GLfloat mat_ambient[] = {.2, .2, .2, 1.0};
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat mat_diffuse[] = {.2, .2, .2, 1.0, 1.0};
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glBegin(GL_QUADS);
    glNormal3d(0.0,1.0,0.0);
    int var = sqrt(Points.size());
    for(int i = 0; i < var -1 ; i++){
    	for(int j = 0; j < var - 1; j++){
    		glVertex3d(Points[j + i*var].x,Points[j + i*var].y,Points[j + i*var].z);
    		glVertex3d(Points[j + i*var + 1].x,Points[j + i*var + 1].y,Points[j + i*var + 1].z);
    		glVertex3d(Points[j + (i+1)*var + 1].x,Points[j + (i+1)*var + 1].y,Points[j + (i+1)*var + 1].z);
    		glVertex3d(Points[j + (i+1)*var].x,Points[j + (i+1)*var].y,Points[j + (i+1)*var].z);
    	}
    }
    glEnd();
}