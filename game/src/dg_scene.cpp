#include "dg_scene.h"

DGScene::DGScene(void){
	horizonGrid = new DGHorizonGrid();
}


DGScene::~DGScene(void){
	dgDelete(horizonGrid);
}

void DGScene::init(DGContext* ctx){
	this->addComponent(horizonGrid);

	DGGameObject::init(ctx);
}

void DGScene::update(DGContext* ctx){
	DGGameObject::update(ctx);
}

void DGScene::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}

void DGScene::destroy(){
	DGGameObject::destroy();
}

void DGScene::turnOnHorizonGrid(){
	this->horizonGrid->setActive(true);
}

void DGScene::turnOffHorizonGrid(){
	this->horizonGrid->setActive(false);
}
