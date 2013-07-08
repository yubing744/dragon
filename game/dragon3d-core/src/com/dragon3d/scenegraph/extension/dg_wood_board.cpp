#include "dg_wood_board.h"


DGWoodBoard::DGWoodBoard(void)   {

}

DGWoodBoard::DGWoodBoard(DGVector3 position) 
	:DGCuboid(1.0f, 1.0f, 1.0f, position)
{
}

DGWoodBoard::~DGWoodBoard(void)
{
}


void DGWoodBoard::start(){
	DGMaterial material1(DGColor::white, "Assets/Textures/Wood03.jpg");
	DGMaterial material2(DGColor::white, "Assets/Textures/Wood02.jpg");

	this->materials[0] = material1;
	this->materials[1] = material2;
	this->materials[2] = material2;
	this->materials[3] = material2;
	this->materials[4] = material2;
	this->materials[5] = material1;

	this->xSize = 4.0f;
	this->ySize = 0.10f;
	this->zSize = 4.0f;

	DGCuboid::start();
}

void DGWoodBoard::update(DGContext* ctx){
	DGCuboid::update(ctx);
}

void DGWoodBoard::draw(DGContext* ctx){
	DGCuboid::draw(ctx);								
}
