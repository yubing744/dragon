/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/


#include <com/dragon3d/input/controller/FirstPersonController.h>

Import com::dragon3d::input::controller;

FirstPersonController::FirstPersonController() {

}

FirstPersonController::~FirstPersonController() {

}

/*

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



 */