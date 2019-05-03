#ifndef CHUCKLIGHT_INCLUDED
#define CHUCKLIGHT_INCLUDED

#include "Color.h"
#include "Shape.h"


class chuckLight{
public:
	Color c;
	double intensity;
	double mode;
	double freq;
	double lastTime;
	Shape* theShape;
	void draw();
	void setColor(Color col, double mode1, double freq1);
	void update();
	void updateColor();
	chuckLight(){};
	virtual ~chuckLight() = default;
};

class toteLight: public chuckLight{
public:
	double x,y,z;
	toteLight(double xin, double yin, double zin){x = xin; y = yin; z = zin;}
};
class bodyLight: public chuckLight{
public:
	int id;
	bodyLight(int idin){id = idin;}
};

#endif