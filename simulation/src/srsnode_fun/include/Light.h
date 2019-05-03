#ifndef LIGHT_INCLUDED
#define LIGHT_INCLUDED

#include <GL/glut.h>
#include "Color.h"

class Light{
public:
    GLfloat light_ambient[4];
    GLfloat light_diffuse[4];
    GLfloat light_specular[4];
    GLfloat light_position[4];
    unsigned int num;
    Light(float posx, float posy, float posz, unsigned int lightNum);
    void update(Color col);
    void draw();
    void print();
    Color c;
    float intensity;
};

#endif