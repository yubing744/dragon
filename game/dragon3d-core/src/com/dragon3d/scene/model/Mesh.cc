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


#include <com/dragon3d/scene/model/Mesh.h>

Import com::dragon3d::scene::model;

Mesh::Mesh() {

}

Mesh::~Mesh() {

}

/*

#include "dg_mesh.h"


DGMesh::DGMesh(void){
    this->vertices = NULL;
    this->normals = NULL;
    this->uv = NULL;
    this->uv2 = NULL;
    this->vertexCount = 0;

    this->indices = NULL;
    this->indexCount = 0;

	this->matrix = DGMatrix4x4::IDENTITY;
}

DGMesh::DGMesh(const char* name){
	this->name = string(name);

    this->vertices = NULL;
    this->normals = NULL;
    this->uv = NULL;
    this->uv2 = NULL;
    this->vertexCount = 0;

    this->indices = NULL;
    this->indexCount = 0;

	this->matrix = DGMatrix4x4::IDENTITY;
}

DGMesh::~DGMesh(void){
    this->vertexCount = 0;
    this->indexCount = 0;
}


 */