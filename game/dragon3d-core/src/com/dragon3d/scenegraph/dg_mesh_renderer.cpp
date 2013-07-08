#include "dg_mesh_renderer.h"


DGMeshRenderer::DGMeshRenderer(void){

}

DGMeshRenderer::DGMeshRenderer(DGMesh* mesh){
	this->mesh = mesh;
}

DGMeshRenderer::~DGMeshRenderer(void){

}

void DGMeshRenderer::init(DGGameObject* gameObject, DGContext* ctx){
    DGRenderer::init(gameObject, ctx);
}

void DGMeshRenderer::update(DGContext* ctx){
	DGRenderer::update(ctx);
}

void DGMeshRenderer::draw(DGContext* ctx){
	DGGraphicsLib* gl = ctx->getGraphicsLib();

	if (this->material) {
		gl->setColor(this->material->color);

		if (this->material && this->material->mainTexture) {
			gl->setTexture(this->material->mainTexture);
		}
	}

	gl->pushMatrix();

	gl->multMatrix(this->mesh->matrix);
	gl->drawMesh(this->mesh);

	gl->popMatrix();

	DGRenderer::draw(ctx);
}

void DGMeshRenderer::destroy(){
	DGRenderer::destroy();
}

