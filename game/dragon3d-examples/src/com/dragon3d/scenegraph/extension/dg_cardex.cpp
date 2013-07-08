#include "dg_cardex.h"
#include "dg_wood_board.h"

DGCardex::DGCardex(void)
{
}


DGCardex::~DGCardex(void)
{
}

void DGCardex::start(){
	//this->addComponent(new DGWoodBoard(DGVector3(-5.0f, 0, 0)));
	//this->addComponent(new DGWoodBoard(DGVector3(5.0f, 0, 0)));


	DGGameObject* boardLeft = new DGGameObject();
	boardLeft->addComponent(new DGWoodBoard());
	boardLeft->transform->position = DGVector3(2.0f, -3.0, 0);
	boardLeft->transform->rotation.x = 90.f;
	boardLeft->transform->rotation.z = 90.f;
	this->addChild(boardLeft);

	DGGameObject* boardRight = new DGGameObject();
	boardRight->addComponent(new DGWoodBoard());
	boardRight->transform->position = DGVector3(-2.0f, -3.0, 0);
	boardRight->transform->rotation.x = 90.f;
	boardRight->transform->rotation.z = -90.f;
	this->addChild(boardRight);

	this->transform->position = DGVector3(0, 0, 20.0f);

	DGGameObject::start();
}

void DGCardex::update(DGContext* ctx){
	DGGameObject::update(ctx);
}

void DGCardex::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}
