#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <ros/ros.h>
#include <cstdlib>
#include <string>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <srslib_framework/MsgUpdateBodyLights.h>
#include <srslib_framework/MsgUpdateToteLights.h>
#include "Chuck.h"
#include "Floor.h"
#define PI 3.14159265

//g++ -std=c++11 first.cpp -lGL -lglut -lGLU


char title[] = "Chuck";


class Camera {
public:

	double x, y, z;
	double px, py, pz;
	Camera(double eye [], double pos []);
	void look();
};

Camera::Camera(double eye [], double pos[]){
	x = eye[0];
	y = eye[1];
	z = eye[2];
	px = pos[0];
	py = pos[1];
	pz = pos[2];
}
void Camera::look(){
	gluLookAt(x,y,z,px,py,pz,0,1,0);
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    GLfloat light_ambient_world[] = {0.0,0.0,0.0, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_ambient_world);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}
void reshape(GLsizei width, GLsizei height) {  
    if (height == 0) height = 1;                
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();            
    gluPerspective(70.0f, aspect, 0.01f, 100.0f);
}


class chuckHandle{
public:
	int channel = 0;
	Chuck * chucks[3];
	void init();
	void draw();
};

void chuckHandle::init(){
	double pos [3] = {0,0,0};
	double rot [3] = {0,0,0};
	double size [3] = {1,1,1};
	double color [3] = {1,0,0};
	double angle = 0;
	double rad = 4;

	int numChucks = 3;
	for(int i = 0; i < numChucks; i++){
		angle = -10*((numChucks+1)%2) + 20*(-1*numChucks/2 + i + (numChucks+1)%2);	
		pos[0] = -1*rad*sin(angle*2*PI/360.0);
		pos[2] = -1*rad*cos(angle*2*PI/360.0) + rad;
		rot[1] = angle;
		chucks[i] = new Chuck(pos,rot,(unsigned int) i);
		std::cout << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
	}

}

void chuckHandle::draw(){
	for(int i = 0; i < 3; i++){
   		chucks[i]->draw();
   	}
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "srsnode_fun");
	ros::NodeHandle nh;
    glutInit(&argc, argv);
	glutInitWindowSize(3000,1500);
	glutInitWindowPosition(50, 100); 
	glutCreateWindow(title);
	glutInitDisplayMode(GLUT_DOUBLE); 
	reshape(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
	initGL();
	chuckHandle chucky;
	if(argv[1] != NULL){
		chucky.channel = atoi(argv[1]);
	}
	chucky.init();
	Floor floor(-.2, 50);
	ros::Rate r(100);

   	int j = 0;
   	std::cout << std::endl;
   	std::cout << std::endl;

   	std::cout << GL_MAX_LIGHTS;
   	std::cout << std::endl;
   	//chucky.chucks[0].lights[0]->intensity = .5;
   	//chucky.chucks[0].lights[1]->intensity = .5;
	while(ros::ok()){
		int start = glutGet(GLUT_ELAPSED_TIME);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   		glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   		glLoadIdentity();
   		gluLookAt(0,2,2.5,0,0,0,0,1,0);

   		chucky.draw();
   		floor.draw();
   		glutSwapBuffers();


   		int qq = 0;
   		while(glutGet(GLUT_ELAPSED_TIME) - start < 20){
   			ros::spinOnce();
   			r.sleep();
   		}
   		//std::cout << "." << std::endl;
   		j++;
	}
	exit(0);
   return 0;
}