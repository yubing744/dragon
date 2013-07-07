#include "dg_component.h"
#include "dg_game_object.h"

DGComponent::DGComponent(void){
	this->name = "DGComponent";
	this->active = true;
}

DGComponent::DGComponent(const char* name){
	this->name = name;
}

DGComponent::~DGComponent(void){

}

string DGComponent::getName(){
	return this->name;
}

DGboolean DGComponent::isActive(){
	return this->active;
}

void DGComponent::setActive(DGboolean active){
	this->active = active;
}


void DGComponent::init(DGGameObject* gameObject, DGContext* ctx){
    this->gameObject = gameObject;
    this->transform = gameObject->transform;
}

void DGComponent::update(DGContext* ctx){

}

void DGComponent::draw(DGContext* ctx){

}

void DGComponent::destroy(){

}

