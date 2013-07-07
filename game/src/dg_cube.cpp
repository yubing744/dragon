#include "dg_cube.h"


DGCube::DGCube(void){
}

DGCube::DGCube(DGfloat size)
	:DGCuboid(size, size, size){

}

DGCube::DGCube(DGfloat size, DGVector3 position)
	:DGCuboid(size, size, size, position){

}

DGCube::DGCube(DGfloat size, DGVector3 position, DGColor color)
	:DGCuboid(size, size, size, position, color){
}

DGCube::DGCube(DGfloat size, DGVector3 position, DGMaterial material)
	:DGCuboid(size, size, size, position, material) {

}

DGCube::DGCube(DGfloat size, DGVector3 position, DGColor color, DGTexture texture)
	:DGCuboid(size, size, size, position, color, texture){

}


DGCube::~DGCube(void)
{
}


void DGCube::start() {
	DGCuboid::start();
}

void DGCube::update(DGContext* ctx){
	DGCuboid::update(ctx);
}

void DGCube::draw(DGContext* ctx){
	DGCuboid::draw(ctx);
}
