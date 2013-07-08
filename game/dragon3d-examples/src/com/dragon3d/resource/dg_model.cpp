#include "dg_model.h"
#include "dg_mesh_renderer.h"

DGLog* DGModel::LOG = new DGLog("dg_model");

DGModel::DGModel(){

}

DGModel::~DGModel(void) {

}

void DGModel::init(DGContext* ctx){
	DGGameObject::init(ctx);
}

void DGModel::update(DGContext* ctx){
	DGGameObject::update(ctx);
}


void DGModel::draw(DGContext* ctx){
	DGGameObject::draw(ctx);
}


void DGModel::destroy(){
	DGGameObject::destroy();
}

void DGModel::addPart(DGMesh* mesh, DGMaterial* material) {
	DGGameObject* part = new DGGameObject();

	DGMeshRenderer* renderer = new DGMeshRenderer(mesh);
	renderer->material = material;

	part->addComponent(renderer);
	this->addChild(part);
}
