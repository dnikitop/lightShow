#include "Light.h"

Light::Light(float posx, float posy, float posz, unsigned int lightNum){
	num = lightNum;
    light_ambient[0] = 0.0;
    light_ambient[1] = 0.0;
    light_ambient[2] = 0.0;
    light_ambient[3] = 1.0;
    light_diffuse[0] = 0.0;
    light_diffuse[1] = 0.0;
    light_diffuse[2] = 0.0;
    light_diffuse[3] = 1.0;
    light_specular[0] = 0.0;
    light_specular[1] = 0.0;
    light_specular[2] = 0.0;
    light_specular[3] = 1.0;
    light_position[0] = posx;
    light_position[1] = posy;
    light_position[2] = posz;
    light_position[3] = 1.0;
    glEnable(GL_LIGHT0 + num);
}

void Light::print(){
	std::cout << c.r << " " << c.g << " " << c.b << " " << intensity << std::endl;
}
void Light::draw(){
   	glLightfv(GL_LIGHT0 + num, GL_POSITION, light_position);
}

void Light::update(Color col){
	c.r = col.r;
	c.g = col.g;
	c.b = col.b;
	intensity = col.a;
	float max = std::max(c.r,c.g);
	max  = std::max(max,c.b);
	light_ambient[0] = 0;
    light_ambient[1] = 0;
    light_ambient[2] = 0;
    light_ambient[3] = 1.0;
    light_diffuse[0] = c.r*intensity + max*intensity/5;
    light_diffuse[1] = c.g*intensity + max*intensity/5;
    light_diffuse[2] = c.b*intensity + max*intensity/5;
    light_diffuse[3] = 1.0;
    light_specular[0] = c.r*intensity/2 + max*intensity/5;
    light_specular[1] = c.g*intensity/2 + max*intensity/5;
    light_specular[2] = c.b*intensity/2 + max*intensity/5;
    light_specular[3] = 1.0;

    glLightfv(GL_LIGHT0 + num, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0 + num, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0 + num, GL_SPECULAR, light_specular);
    glLightf(GL_LIGHT0 + num, GL_LINEAR_ATTENUATION, 1);
}