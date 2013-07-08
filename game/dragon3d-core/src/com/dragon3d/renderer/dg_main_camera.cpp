#include "dg_main_camera.h"
#include "dg_first_person_camera.h"

DGMainCamera::DGMainCamera(void){

}

DGMainCamera::~DGMainCamera(void) {

}

void DGMainCamera::start(){
	this->addComponent(new DGFirstPersonCamera());

	DGGameObject::start();
}

void DGMainCamera::update(DGContext* ctx){
	DGGameObject::update(ctx);
}

void DGMainCamera::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}
