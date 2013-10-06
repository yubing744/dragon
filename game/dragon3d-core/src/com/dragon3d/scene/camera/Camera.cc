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

const Type Camera::TYPE = Type(typeid(Camera), sizeof(Camera));

Camera::Camera() 
	:orthographic(false), 
	orthographicSize(1), 

	clearFlags(SolidColor), 
	backgroundColor(Color::BLACK), 

	cameraToWorldMatrix(Matrix4x4::IDENTITY),
	projectionMatrix(Matrix4x4::IDENTITY),

	cullingMask(0),
	eventMask(0),

	depth(0.0f),
	depthTextureMode(None), 

	fieldOfView(60.0f),
	aspect(1.0f),
	nearClipPlane(0.3f),
	farClipPlane(1000.0f),

	hdr(false),

	layerCullDistances(NULL),
	layerCount(0),
	layerCullSpherical(false),

	pixelRect(0, 0, 100, 100),

	rect(0, 0, 1, 1),

	renderingPath(UsePlayerSettings),

	useOcclusionCulling(false),

	velocity(Vector3::ZERO),
	targetTexture(null) {

}

Camera::~Camera() {

}

const Type& Camera::getType() {
	return Camera::TYPE;
}

void Camera::copyFrom(Camera* other) {

}

void Camera::resetAspect() {

}

float Camera::pixelWidth() {
	return pixelRect.width;
}

float Camera::pixelHeight() {
	return pixelRect.height;
}

void Camera::resetProjectionMatrix() {

}

void Camera::resetWorldToCameraMatrix() {

}

Ray3* Camera::screenPointToRay(Vector3 position) {
	return null;
}

Vector3 Camera::screenToViewportPoint(Vector3 position) {
	return Vector3::ZERO;
}

Vector3 Camera::screenToWorldPoint(Vector3 position) {
	return Vector3::ZERO;
}

Ray3* Camera::viewportPointToRay(Vector3 position) {
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
