#include "dg_first_person_controller.h"

DGFirstPersonController::DGFirstPersonController(void){
	this->camera = new DGCamera();
}

DGFirstPersonController::~DGFirstPersonController(void){
	dgDelete(camera);
}

void DGFirstPersonController::init(DGContext* ctx){
	this->addComponent(camera);
	DGGameObject::init(ctx);

	forwardSpeed = 0.1f;
	turnSpeed = 0.5f;
	angle = 90.0f;

	walkbias = 0;
	walkbiasangle = 0;

	camera->eye = DGVector3(0, 0.5f, -12);
	camera->center = DGVector3(0, 2, 0);
	camera->up = DGVector3::up;
}

void DGFirstPersonController::update(DGContext* ctx){
	DGInput* input = ctx->getInput();

	if (input->getAxis("Right")) {
		angle += turnSpeed;
	}

	if (input->getAxis("Left")) {
		angle -= turnSpeed;
	}

	float degree = float(DGMathf::PI * angle / 180.0f);

	if (input->getAxis("Forward")) {
		camera->eye.x += (float)cos(degree) * forwardSpeed;
		camera->eye.z += (float)sin(degree) * forwardSpeed;

		if (walkbiasangle >= 359.0f) {
			walkbiasangle = 0.0f;
		} else {
			walkbiasangle+= 10;
		}

		walkbias = (float)sin(walkbiasangle * PIOVER_180)/20.0f;
	}

	if (input->getAxis("Back")) {
		camera->eye.x -= (float)cos(degree) * forwardSpeed;
		camera->eye.z -= (float)sin(degree) * forwardSpeed;

		if (walkbiasangle <= 1.0f) {
			walkbiasangle = 359.0f;
		} else {
			walkbiasangle-= 10;
		}

		walkbias = (float)sin(walkbiasangle * PIOVER_180) / 20.0f;
	}

	DGfloat ytrans = -walkbias - 0.25f;

	camera->center.x = float(camera->eye.x + 100*cos(degree));
	camera->center.z = float(camera->eye.z + 100*sin(degree));

	camera->center.y = camera->eye.y + ytrans;

	//update GameObject's position
	this->transform->position = camera->center;

	DGGameObject::update(ctx);
}

void DGFirstPersonController::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}
