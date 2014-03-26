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
#include <dragon/lang/IndexOutOfBoundsException.h>

Import com::dragon3d::scene::model;

Mesh::Mesh() : 
    vertices(null), 
    vertexCount(0),

    normals(null),
    uv(null),
    uv2(null),
    tangents(null),
    colors(null),

    subMeshs(null),
    subMeshCount(0) {

}

Mesh::~Mesh(){
    this->clear();
}

void Mesh::clear() {
    SafeFree(this->vertices);
    this->vertexCount = 0;

    SafeFree(this->normals);
    SafeFree(this->uv);
    SafeFree(this->uv2);
    SafeFree(this->tangents);
    SafeFree(this->colors);

    SafeFree(this->subMeshs);
    this->subMeshCount = 0;
}

void Mesh::setIndices(Array<int> indices, MeshTopology topology, int submesh) {
    int newSize = submesh + 1;

    if (newSize > this->subMeshCount) {
        this->subMeshs = (MeshData*)realloc(this->subMeshs, sizeof(MeshData) * newSize);
    }

    for (int i=this->subMeshCount; i<submesh; i++) {
        this->subMeshs[i].indices = null;
        this->subMeshs[i].indexCount = 0;
        this->subMeshs[i].topology = Triangles;
    }

    this->subMeshs[submesh].indices = const_cast<int*>(indices.raw());
    this->subMeshs[submesh].indexCount = indices.length();
    this->subMeshs[submesh].topology = topology;
    this->subMeshs[submesh].material = null;
    
    this->subMeshCount = newSize;
}

void Mesh::setTriangles(Array<int> triangles) {
    this->setTriangles(triangles, 0);
}

void Mesh::setTriangles(Array<int> triangles, int submesh) {
    this->setIndices(triangles, Triangles, submesh);
}

Mesh::MeshData Mesh::getSubMeshData(int submesh) {
    if (submesh >= this->subMeshCount) {
        throw new IndexOutOfBoundsException("the submesh is out of bounds!");
    }

    return this->subMeshs[submesh];
}

Array<int> Mesh::getIndices(int submesh) {
    Mesh::MeshData data = this->getSubMeshData(submesh);
    return Array<int>(data.indices, data.indexCount, false);
}

Array<int> Mesh::getTriangles() {
    if (this->subMeshCount == 0) {
        this->setTriangles(Array<int>());
    }

    Mesh::MeshData data = this->getSubMeshData(0);
    return Array<int>(data.indices, data.indexCount, false);
}

Array<unsigned short> Mesh::getShortIndices(int submesh) {
    Mesh::MeshData data = this->getSubMeshData(submesh);

    int size = data.indexCount;
    unsigned short* shortIndices = (unsigned short*)malloc(sizeof(unsigned short) * size);

    for (int i=0; i<size; i++) {
        shortIndices[i] = data.indices[i];
    }

    return Array<unsigned short>(shortIndices, size, false);
}

int Mesh::getSubMeshCount() {
    return this->subMeshCount;  
}

