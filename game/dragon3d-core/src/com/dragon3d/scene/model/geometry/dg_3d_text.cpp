#include "dg_3d_text.h"
#include "dg_text_mesh.h"

DG3DText::DG3DText(void){
	this->text = "Hello World";
	this->color = DGColor::white;
}


DG3DText::DG3DText(const char *text) {
	this->text = text;
	this->color = DGColor::white;
}

DG3DText::DG3DText(const char *text, DGColor color){
	this->text = text;
	this->color = color;
}

DG3DText::DG3DText(DGVector3 position, const char *text, DGColor color){
	this->transform->position = position;
	this->text = text;
	this->color = color;
}

DG3DText::~DG3DText(void)
{
}


void DG3DText::start(){
	this->addComponent(new DGTextMesh(this->text, this->color));
	DGGameObject::start();
}

void DG3DText::update(DGContext* ctx){
	DGGameObject::update(ctx);
}

void DG3DText::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}

void DG3DText::destroy(){
	DGGameObject::destroy();
}
