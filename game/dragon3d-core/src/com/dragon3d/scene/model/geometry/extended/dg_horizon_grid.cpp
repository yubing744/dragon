#include "dg_horizon_grid.h"


DGHorizonGrid::DGHorizonGrid(void){

}

DGHorizonGrid::~DGHorizonGrid(void){

}

void DGHorizonGrid::init(DGGameObject* gameObject, DGContext* ctx){
	DGComponent::init(gameObject, ctx);

	size = 200;
	color = DGColor::hexColor("#5D5C5C");
}

void DGHorizonGrid::draw(DGContext* ctx){
	DGGraphicsLib* gl = ctx->getGraphicsLib();

	gl->setColor(color);

	int radius = size / 2;

	DGfloat iif = 0.0f;
	DGfloat radiusf = radius * 1.0f;

	for(int i=-radius; i<=radius; i++) {
		iif = i * 1.0f;
		gl->drawLine(DGVector3(radiusf, 0, iif), DGVector3(-radiusf, 0, iif));
		gl->drawLine(DGVector3(iif, 0, radiusf), DGVector3(iif, 0, -radiusf));
	}
}

void DGHorizonGrid::update(DGContext* ctx){

}

void DGHorizonGrid::destroy(){
	size = 200;
	color = DGColor::hexColor("#5D5C5C");
}