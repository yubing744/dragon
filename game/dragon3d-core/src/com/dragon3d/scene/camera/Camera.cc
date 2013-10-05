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


#include <com/dragon3d/scene/camera/Camera.h>

Import com::dragon3d::scene::camera;

Camera::Camera() {

}

Camera::~Camera() {

}


void Camera::copyFrom(Camera* other) {

}

void Camera::resetAspect() {

}


void Camera::resetProjectionMatrix() {

}


void Camera::resetWorldToCameraMatrix() {

}


Ray* Camera::screenPointToRay(Vector3 position) {
	return null;
}

Vector3 Camera::screenToViewportPoint(Vector3 position) {
	return Vector3::ZERO;
}

Vector3 Camera::screenToWorldPoint(Vector3 position) {
	return Vector3::ZERO;
}

Ray* Camera::viewportPointToRay(Vector3 position) {
	return null;
}

Vector3 Camera::viewportToScreenPoint(Vector3 position) {
	return Vector3::ZERO;
}

Vector3 Camera::viewportToWorldPoint(Vector3 position) {
	return Vector3::ZERO;
}

Vector3 Camera::worldToScreenPoint(Vector3 position) {
	return Vector3::ZERO;
}

Vector3 Camera::worldToViewportPoint(Vector3 position) {
	return Vector3::ZERO;
}


/*

#include "dg_camera.h"
#include "dg_engine.h"

DGCamera::DGCamera(){
	this->log = DGPlatform::getCurrent()->getLogger("dg_camera");
}

void DGCamera::init(DGGameObject* gameObject, DGContext* ctx){
	DGComponent::init(gameObject, ctx);

	DGEngine* engine = ctx->getEngine();

	this->fovy = 45.0f;
	this->aspect = 1.0f;

	this->zNear = 0.1f;
	this->zFar = 1000.0f;

	this->eye = DGVector3::zero;
	this->center = DGVector3::forward;
	this->up = DGVector3::up;

	engine->setupCamera(this);
}

void DGCamera::setup(DGContext* ctx) {
	DGGraphicsLib* gl = ctx->getGraphicsLib();

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(fovy, aspect, zNear, zFar);

	gl->lookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
	//log->debug("lookAt(%.3f,%.3f,%.3f, %.3f,%.3f,%.3f, %.3f,%.3f,%.3f)", eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

 */