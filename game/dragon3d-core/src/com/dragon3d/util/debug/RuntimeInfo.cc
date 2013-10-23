/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/


#include <com/dragon3d/util/debug/RuntimeInfo.h>

Import com::dragon3d::util::debug;

RuntimeInfo::RuntimeInfo() {

}

RuntimeInfo::~RuntimeInfo() {

}

/*

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



 */