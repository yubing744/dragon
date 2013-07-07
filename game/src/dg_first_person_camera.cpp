#include "dg_first_person_camera.h"
#include <math.h>

DGFirstPersonCamera::DGFirstPersonCamera(){

}


DGFirstPersonCamera::~DGFirstPersonCamera(){

}

void DGFirstPersonCamera::start(){
	DGCamera::start();

	forwardSpeed = 0.1f;
	turnSpeed = 0.5f;
	angle = 90.0f;

	walkbias = 0;
	walkbiasangle = 0;

	this->eye = DGVector3(0, 2.0, -12);
	this->center = DGVector3(0, 0, 0);
	this->up = DGVector3::up;
}

void DGFirstPersonCamera::update(DGContext* ctx){
	DGInput* input = ctx->getInput();

	if (input->getAxis("Right")) {
		angle += turnSpeed;
	}

	if (input->getAxis("Left")) {
		angle -= turnSpeed;
	}

	float degree = float(DGMathf::PI * angle / 180.0f);

	if (input->getAxis("Forward")) {
		this->eye.x += (float)cos(degree) * forwardSpeed;
		this->eye.z += (float)sin(degree) * forwardSpeed;

		if (walkbiasangle >= 359.0f) {
			walkbiasangle = 0.0f;
		} else {
			walkbiasangle+= 10;
		}

		walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
	}

	if (input->getAxis("Back")) {
		this->eye.x -= (float)cos(degree) * forwardSpeed;
		this->eye.z -= (float)sin(degree) * forwardSpeed;

		if (walkbiasangle <= 1.0f) {
			walkbiasangle = 359.0f;
		} else {
			walkbiasangle-= 10;
		}

		walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
	}

	GLfloat ytrans = -walkbias - 0.25f;

	this->center.x = float(this->eye.x + 100*cos(degree));
	this->center.z = float(this->eye.z + 100*sin(degree));

	this->center.y = this->eye.y + ytrans;

	DGCamera::update(ctx);
}


void DGFirstPersonCamera::draw(DGContext* ctx){
	DGGUIText* gui = ctx->getGUIText();
	DGScreen* screen = ctx->getScreen();

	//gui->print(10, screen->getHeight() - 30, "walkbiasangle: %.3f walkbias: %.3f", walkbiasangle, walkbias);

	DGCamera::draw(ctx);
}
