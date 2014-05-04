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

const Type* Camera::TYPE = TypeOf<Camera>();

Camera::Camera() 
	:orthographic(false), 
	orthographicSize(1), 

	clearFlags(SolidColor), 
	backgroundColor(Color::BLACK), 

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
	useOcclusionCulling(false),

	pixelRect(0, 0, 100, 100),
	rect(0, 0, 1, 1),

	renderingPath(UsePlayerSettings),


	velocity(Vector3::ZERO),
	targetTexture(null),

	frustum(new Frustum()),

    updateMVMatrix(true),
    updatePMatrix(true),
   	updateMVPMatrix(true),
    updateInverseMVPMatrix(true),

	modelViewMatrix(Matrix4x4::IDENTITY),
	projectionMatrix(Matrix4x4::IDENTITY),
	modelViewProjectionMatrix(Matrix4x4::IDENTITY),
	modelViewProjectionInverseMatrix(Matrix4x4::IDENTITY),

    depthRangeDirty(true),
    frustumDirty(true),
    viewPortDirty(true),
    frameDirty(true) {

}

Camera::Camera(int width, int height) 
	:orthographic(false), 
	orthographicSize(1), 

	clearFlags(SolidColor), 
	backgroundColor(Color::BLACK), 

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
	useOcclusionCulling(false),

	pixelRect(0, 0, width, height),
	rect(0, 0, 1, 1),

	renderingPath(UsePlayerSettings),


	velocity(Vector3::ZERO),
	targetTexture(null),

	frustum(new Frustum()),

    updateMVMatrix(true),
    updatePMatrix(true),
   	updateMVPMatrix(true),
    updateInverseMVPMatrix(true),

	modelViewMatrix(Matrix4x4::IDENTITY),
	projectionMatrix(Matrix4x4::IDENTITY),
	modelViewProjectionMatrix(Matrix4x4::IDENTITY),
	modelViewProjectionInverseMatrix(Matrix4x4::IDENTITY),

    depthRangeDirty(true),
    frustumDirty(true),
    viewPortDirty(true),
    frameDirty(true) {

    onFrustumChange();
    onViewPortChange();
    onFrameChange();
}

Camera::~Camera() {
	SafeRelease(this->frustum);
}

bool Camera::isTypeOf(const Type* type) {
    return Camera::TYPE->equals(type) 
        || Behaviour::isTypeOf(type);
}

void Camera::init() {
    onFrustumChange();
    onViewPortChange();
    onFrameChange();
}

void Camera::update(Input* input, ReadOnlyTimer* timer) {
    onFrustumChange();
	onFrameChange();
}

void Camera::destroy() {

}

void Camera::copyFrom(Camera* other) {
	throw "not implement";
}

void Camera::resetAspect() {
	throw "not implement";
}

//------------viewport------------------------------
float Camera::pixelWidth() {
	return pixelRect.width;
}

float Camera::pixelHeight() {
	return pixelRect.height;
}

void Camera::setPixelRect(const Rect& rect) {
	this->pixelRect = rect;
	onViewPortChange();
}

void Camera::setPixelWidth(float width) {
	this->pixelRect.width = width;
	onViewPortChange();
}

void Camera::setPixelHeight(float height) {
	this->pixelRect.height = height;
	onViewPortChange();
}

void Camera::resize(float width, float height) {
	this->pixelRect.width = width;
	this->pixelRect.height = height;
	onViewPortChange();
}

void Camera::setRect(const Rect& rect) {
	this->rect = rect;
	onViewPortChange();
}

Rect Camera::getViewPortRect() {
    Rect& screenRect = this->pixelRect;
    Rect& nvp = this->rect;

    return Rect(screenRect.x + screenRect.width * nvp.x, screenRect.y + screenRect.height * nvp.y, 
        screenRect.width * nvp.width, screenRect.height * nvp.height);
}

void Camera::resetProjectionMatrix() {
	throw "not implement";
}

void Camera::resetWorldToCameraMatrix() {
	throw "not implement";
}

Ray3* Camera::screenPointToRay(Vector3 position) {
	throw "not implement";
}

Vector3 Camera::screenToViewportPoint(Vector3 position) {
	throw "not implement";
}

Vector3 Camera::screenToWorldPoint(Vector3 position) {
	throw "not implement";
}

Ray3* Camera::viewportPointToRay(Vector3 position) {
	throw "not implement";
}

Vector3 Camera::viewportToScreenPoint(Vector3 position) {
	throw "not implement";
}

Vector3 Camera::viewportToWorldPoint(Vector3 position) {
	throw "not implement";
}

Vector3 Camera::worldToScreenPoint(Vector3 position) {
	throw "not implement";
}

Vector3 Camera::worldToViewportPoint(Vector3 position) {
	throw "not implement";
}

void Camera::lookAt(const Vector3& pos, const Vector3& worldUpVector) {
    lookAt(pos.getX(), pos.getY(), pos.getZ(), worldUpVector);
}

void Camera::lookAt(float x, float y, float z, const Vector3& worldUpVector) {
    this->getTransform()->lookAt(Vector3(x, y, z), worldUpVector);

    onFrustumChange();
    onFrameChange();
}

FrustumIntersect Camera::contains(Bounds* bounds) {
	int result = this->frustum->checkBounds(bounds);

	if (result > 0) {
		return Outside;
	} else if(result == 0) {
		return Inside;
	} else {
		return Intersects;
	}
}

void Camera::onFrustumChange() {
	Matrix4x4 modelViewMatrix = this->getModelViewMatrix();
	Matrix4x4 projectionMatrix = this->getProjectionMatrix();

	this->frustum->update(this->depth, projectionMatrix, modelViewMatrix);
}

void Camera::onViewPortChange() {
	this->viewPortDirty = true;
}

void Camera::onFrameChange() {
	this->updateMVMatrix = true;
    this->updateMVPMatrix = true;
    this->updateInverseMVPMatrix = true;
}

// ---------------------------------------
//  matrix
//  --------------------------------------
// update
void Camera::updateModelViewMatrix() {
	Transform* t = this->getTransform();
	this->modelViewMatrix = t->getWorldToLocalMatrix();
    SafeRelease(t);
}

void Camera::updateProjectionMatrix() {
    // fix the error for coordinate system
    //Matrix4x4 tmp = Matrix4x4::IDENTITY;
    //tmp = tmp.scale(Vector3(-1, 1, 1));

    if (!this->orthographic) {
        this->projectionMatrix = Matrix4x4::perspective(this->fieldOfView, this->aspect, this->nearClipPlane, this->farClipPlane);
    } else {
        this->projectionMatrix = Matrix4x4::ortho(-this->aspect, this->aspect, -this->aspect, this->aspect, this->nearClipPlane, this->farClipPlane);
    }
}

void Camera::updateModelViewProjectionMatrix() {
	this->modelViewProjectionMatrix = getModelViewMatrix().multiply(this->getProjectionMatrix());
}

void Camera::updateInverseModelViewProjectionMatrix() {
	this->modelViewProjectionInverseMatrix = this->getModelViewProjectionMatrix().inverse();
}

// check 
void Camera::checkModelView() {
	if (this->updateMVMatrix) {
		updateModelViewMatrix();

		this->updateMVMatrix = false;
	}	
}

void Camera::checkProjection() {
	if (this->updatePMatrix) {
		updateProjectionMatrix();

		this->updatePMatrix = false;
	}
}

void Camera::checkModelViewProjection() {
	if (this->updateMVPMatrix) {
		updateModelViewProjectionMatrix();

		this->updateMVPMatrix = false;
	}
}

void Camera::checkInverseModelViewProjection() {
	if (this->updateInverseMVPMatrix) {
		updateInverseModelViewProjectionMatrix();

		this->updateInverseMVPMatrix = false;
	}
}

//get
Matrix4x4 Camera::getModelViewMatrix() {
	checkModelView();

	return this->modelViewMatrix;
}

Matrix4x4 Camera::getProjectionMatrix() {
	checkProjection();

	return this->projectionMatrix;
}

Matrix4x4 Camera::getModelViewProjectionMatrix() {
	checkModelViewProjection();

	return this->modelViewProjectionMatrix;
}

Matrix4x4 Camera::getModelViewProjectionInverseMatrix() {
	checkInverseModelViewProjection();

	return this->modelViewProjectionInverseMatrix;
}




