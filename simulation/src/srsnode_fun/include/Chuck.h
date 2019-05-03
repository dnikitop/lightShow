#include "Shape.h"
#include <ros/ros.h>
#include <boost/shared_ptr.hpp>
#include <memory>
#include "chuckLight.h"
#include "Light.h"
#include <srslib_framework/MsgUpdateBodyLights.h>
#include <srslib_framework/MsgUpdateToteLights.h>
#include "Rectangle.h"
#include "Cylinder.h"
class Chuck{
public:
	ros::NodeHandle nh;
	ros::Subscriber body_sub;
	ros::Subscriber tote_sub;
	void bodyCallback(const srslib_framework::MsgUpdateBodyLights& body);
	void toteCallback(const srslib_framework::MsgUpdateToteLights& tote);
	int channels [3];
	int channel;
	std::string bodys;
	std::string totes;
	double x, y, z;
	double rotx, roty, rotz;
	std::vector<Shape*> shapes;
	std::vector<boost::shared_ptr<chuckLight>> lights;
	std::vector<boost::shared_ptr<bodyLight>> bodyLights;
	std::vector<boost::shared_ptr<toteLight>> toteLights;
	std::vector<Light*> glLights;
	Chuck(double pos [], double rot [], unsigned int chuckNum);
	void draw();
	unsigned int chuckNum;
};