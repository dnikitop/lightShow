#include "Chuck.h"

Chuck::Chuck(double pos [], double rot [], unsigned int chuckNum1){

	channels[0] = 1;
	channels[1] = 0;
	channels[2] = 2;
	chuckNum = chuckNum1;
	channel = channels[chuckNum];
	totes = "drivers/brainstem/cmd/update_tote_lights/";
	bodys = "drivers/brainstem/cmd/update_body_lights/";
	bodys.append(std::to_string(channel+1));
	totes.append(std::to_string(channel+1));
	x = pos[0];
	y = pos[1];
	z = pos[2];
	rotx = rot[0];
	roty = rot[1];
	rotz = rot[2];
	shapes.push_back(new Rectangle(0,0,0, 0,0,0, 1,.3,2,   Color(.1,.1,.4, 1.0), 0, 5));
	shapes.push_back(new Rectangle(0,1.2,0,0,0,0,1,.1,2,   Color(.1,.1,.4, 1.0), 0, 5));
	shapes.push_back(new Cylinder(-.25,.5,0,  0,0,0,  .07,1,  Color(0.1,0.1,0.1,1.0),  0,30,10));
	shapes.push_back(new Cylinder(.25,.5,0,  0,0,0,  .07,1,  Color(0.1,0.1,0.1  ,1.0),  0,30,10));

	lights.emplace_back(boost::static_pointer_cast<chuckLight>(boost::make_shared<bodyLight>(204)));
	lights.back()->theShape = new Rectangle(-.4, .1,.95,  0,0,0,  .21,.05,.13, Color(0,0,0,0),0, 1);
	lights.back()->setColor(Color(0,0,0,0),0,.5);
	bodyLights.push_back(boost::static_pointer_cast<bodyLight>(lights.back()));

	lights.emplace_back(boost::static_pointer_cast<chuckLight>(boost::make_shared<bodyLight>(205)));
	lights.back()->theShape = new Rectangle(.4, .1,.95,  0,0,0,  .21,.05,.13, Color(0,0,0,0),0, 1);
	lights.back()->setColor(Color(0,0,0,0),0,.5);
	bodyLights.push_back(boost::static_pointer_cast<bodyLight>(lights.back()));
	if(chuckNum < 4){
		glLights.push_back(new Light(-.4,.1,1.1,chuckNum*2));
		glLights.push_back(new Light(.4,.1,1.1,chuckNum*2 + 1));
	}
	for(int i = 0 ; i < 2; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 27; k+=3){
				lights.emplace_back(boost::make_shared<toteLight>(k,i,j));
				lights.back()->theShape = new Cylinder(-.5 + i,.15 + j*1.1,-.8+k*.18/3,   90,0,0,   .02,.1,   Color(0,0,0,0), 0,   10,1);
				lights.back()->setColor(Color(0,0,0,1),0,0);
				toteLights.push_back(boost::static_pointer_cast<toteLight>(lights.back()));
			}
		}
	}
	body_sub = nh.subscribe(bodys, 10, &Chuck::bodyCallback, this);
	tote_sub = nh.subscribe(totes, 10, &Chuck::toteCallback, this);
	
}

void Chuck::draw(){
	
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotated(rotx, 1.0f, 0.0f, 0.0f);
	glRotated(roty, 0.0f, 1.0f, 0.0f);
	glRotated(rotz, 0.0f, 0.0f, 1.0f);
	int drawStart = glutGet(GLUT_ELAPSED_TIME);
	for(int i = 0; i < glLights.size(); i++){
		glLights[i]->update(Color(lights[i]->c.r, lights[i]->c.g, lights[i]->c.b, lights[i]->intensity));
		glLights[i]->draw();
	}
	int lightTime = glutGet(GLUT_ELAPSED_TIME) - drawStart;	
	for(int i = 0; i < shapes.size(); i++){
		shapes[i]->draw();
	}
	int shapeTime = glutGet(GLUT_ELAPSED_TIME) - lightTime - drawStart;	
	for(int i = 0; i < lights.size(); i++){
		lights[i]->update();
		lights[i]->draw();
	}
	int ledTime = glutGet(GLUT_ELAPSED_TIME) - shapeTime - lightTime - drawStart;
	glPopMatrix();
	//std:: cout << lightTime << " " << shapeTime << " " << ledTime << std::endl;
}


void Chuck::bodyCallback(const srslib_framework::MsgUpdateBodyLights& body){
	int id = body.bodyLightUpdates[0].entity;
	int cmd = body.bodyLightUpdates[0].lightCmd;
	Color start(((float)body.bodyLightUpdates[0].startColor.r)/255, ((float)body.bodyLightUpdates[0].startColor.g)/255, ((float)body.bodyLightUpdates[0].startColor.b)/255, 1.0);
	double freq = (float)body.bodyLightUpdates[0].frequency;
	for(int i = 0; i < bodyLights.size(); i++){
		if(bodyLights[i]->id == id){
			if(cmd == 0){
				bodyLights[i]->setColor(Color(0,0,0,0),1,0);
			}
			else if(cmd == 1){
				bodyLights[i]->setColor(start,1,0);
			}
			else if(cmd == 2){
				bodyLights[i]->setColor(start,2,freq);
			}
		}
	}

}

void Chuck::toteCallback(const srslib_framework::MsgUpdateToteLights& tote){
	int sx = (int)tote.startSegment.x;
	int sy = (int)tote.startSegment.y;
	int sz = (int)tote.startSegment.z;
	int ex = (int)tote.endSegment.x;
	int ey = (int)tote.endSegment.y;
	int ez = (int)tote.endSegment.z;
	int cmd = tote.lightCmd;
	Color start(((float)tote.startColor.r)/255, ((float)tote.startColor.g)/255, ((float)tote.startColor.b)/255, 1.0);

	double freq = (float)tote.frequency;
	for(int i = 0; i < toteLights.size(); i++){
		int lx = toteLights[i]->x;
		int ly = toteLights[i]->y;
		int lz = toteLights[i]->z;
		if(sx <= lx && lx <= ex && sy <= ly && ly <= ey && sz <= lz && lz <= ez){
			if(cmd == 0){
				toteLights[i]->setColor(Color(0,0,0,1),1,0);
			}
			else if(cmd == 1){
				toteLights[i]->setColor(start,1,0);
			}
			else if(cmd == 2){
				toteLights[i]->setColor(start,2,freq);
			}
		}
	}
}