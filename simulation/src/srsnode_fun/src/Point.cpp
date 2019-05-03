#include "Point.h"

Point::Point(){

}
Point::Point(double xin, double yin, double zin){
	x = xin;
	y = yin;
	z = zin;
}
void Point::print(){
	std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}