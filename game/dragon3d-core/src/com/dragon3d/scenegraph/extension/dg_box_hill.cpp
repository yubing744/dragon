#include "dg_box_hill.h"

#include "dg_cube.h"
#include "dg_3d_text.h"



DGBoxHill::DGBoxHill(void)
{
}


DGBoxHill::~DGBoxHill(void)
{
}


void DGBoxHill::start() {

	this->addComponent(new DGCube(1, DGVector3(0, 1, 0)));
	this->addComponent(new DGCube(2, DGVector3(4, 2, 0)));
	this->addComponent(new DGCube(3, DGVector3(10, 3, 0), DGColor::red));
	this->addComponent(new DGCube(4, DGVector3(18, 4, 0), DGColor::green));
	this->addComponent(new DGCube(5, DGVector3(28, 5, 0), DGColor::blue));

	//this->addChild(new DG3DText(DGVector3(10, 8, 0), "Box Hill", DGColor::white));

	this->transform->position = DGVector3(0, 0, 40.0f);

	DGGameObject::start();
}

void DGBoxHill::update(DGContext* ctx){
	DGGameObject::update(ctx);
}

void DGBoxHill::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}
