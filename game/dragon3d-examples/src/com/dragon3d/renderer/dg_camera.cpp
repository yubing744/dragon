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