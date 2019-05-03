#include "chuckLight.h"
void chuckLight::draw(){
	theShape->draw();
}

void chuckLight::setColor(Color col, double mode1, double freq1){
	c.r = col.r;
	c.g = col.g;
	c.b = col.b;
	intensity = col.a;
	theShape->c.r = c.r;
	theShape->c.g = c.g;
	theShape->c.b = c.b;
	theShape->c.a = intensity;
	theShape->emit = intensity;
	freq = freq1;
	mode = mode1;
}
void chuckLight::updateColor(){
	theShape->c.r = c.r;
	theShape->c.g = c.g;
	theShape->c.b = c.b;
	theShape->c.a = intensity;
	theShape->emit = intensity;
}

void chuckLight::update(){
	if(mode == 2){
		intensity-=.02*freq;
		if(intensity <= 0){
			intensity = 1;
		}
		theShape->c.a = intensity;
		theShape->emit = intensity;
	}
	
}
