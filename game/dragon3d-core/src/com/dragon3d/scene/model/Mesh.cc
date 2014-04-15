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

#include <dragon/util/ArrayList.h>
#include <com/dragon3d/scene/model/Mesh.h>
#include <dragon/lang/IndexOutOfBoundsException.h>

Import dragon::util;
Import com::dragon3d::scene::model;

Mesh::Mesh() :
    vertices(), 
    vertexCount(0),

    uv(),
    uv2(),
    normals(),
    tangents(),
    colors(),
    colors32(),
    
    subMeshs(null),
    subMeshCount(0) {

}

Mesh::~Mesh(){
    this->clear();
}

void Mesh::clear() {
    this->vertexCount = 0;

    SafeFree(this->subMeshs);
    this->subMeshCount = 0;
}

// indices
void Mesh::setIndices(Array<int> indices, MeshTopology topology, int submesh) {
    int newSize = submesh + 1;

    if (newSize > this->subMeshCount) {
        this->subMeshs = (MeshData*)realloc(this->subMeshs, sizeof(MeshData) * newSize);
    }
    
    memset(this->subMeshs + this->subMeshCount, 0, sizeof(MeshData) * (newSize - this->subMeshCount));

    for (int i=this->subMeshCount; i<submesh; i++) {
        this->subMeshs[i].indices = Array<int>();
        this->subMeshs[i].indexCount = 0;
        this->subMeshs[i].topology = Triangles;
        this->subMeshs[i].materialName = null;
    }

    this->subMeshs[submesh].indices = indices.clone();
    this->subMeshs[submesh].indexCount = indices.length();
    this->subMeshs[submesh].topology = topology;
    this->subMeshs[submesh].materialName = null;

    this->subMeshCount = newSize;
}

void Mesh::setTriangles(Array<int> triangles) {
    this->setTriangles(triangles, 0);
}

void Mesh::setTriangles(Array<int> triangles, int submesh) {
    this->setIndices(triangles, Triangles, submesh);
}

void Mesh::appendIndices(Array<int> indices, MeshTopology topology, int submesh) {
    int newSize = submesh + 1;

    if (newSize > this->subMeshCount) {
        this->subMeshs = (MeshData*)realloc(this->subMeshs, sizeof(MeshData) * newSize);
    }

    memset(this->subMeshs + this->subMeshCount, 0, sizeof(MeshData) * (newSize - this->subMeshCount));
    
    for (int i=this->subMeshCount; i<=submesh; i++) {
        this->subMeshs[i].indices = Array<int>();
        this->subMeshs[i].indexCount = 0;
        this->subMeshs[i].topology = Triangles;
        this->subMeshs[i].materialName = null;
    }

    this->subMeshs[submesh].indices.append(indices);
    this->subMeshs[submesh].indexCount += indices.length();

    this->subMeshCount = newSize;
}

void Mesh::appendTriangles(Array<int> triangles) {
    this->appendTriangles(triangles, 0);
}

void Mesh::appendTriangles(Array<int> triangles, int submesh) {
    this->appendIndices(triangles, Triangles, submesh);
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


//------------------------------------
int Mesh::getSubMeshCount() {
    return this->subMeshCount;  
}

int Mesh::getVertexCount() {
    return this->vertexCount;
}

//--------------------------------------
// set
void Mesh::setFloatVertices(Array<float> vertices) {
    this->vertices = vertices.clone();
    this->vertexCount = vertices.length() / 3;
}

void Mesh::setVertexArray(Array<Vector3> vertices) {
    int size = 3 * vertices.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<vertices.size(); n++) {
        Vector3 v = vertices[n];

        data[n * 3 + 0] = v.x;
        data[n * 3 + 1] = v.y;
        data[n * 3 + 2] = v.z;
    }

    this->setFloatVertices(Array<float>(data, size));
}

void Mesh::setVertices(List<Vector3>* vertices) {
    int size = 3 * vertices->size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<vertices->size(); n++) {
        Vector3* v = vertices->get(n);

        data[n * 3 + 0] = v->x;
        data[n * 3 + 1] = v->y;
        data[n * 3 + 2] = v->z;
    }

    this->setFloatVertices(Array<float>(data, size));
}

// append
void Mesh::appendFloatVertices(Array<float> vertices) {
    this->vertices.append(vertices);
    this->vertexCount += vertices.length() / 3;
}

void Mesh::appendVertexArray(Array<Vector3> vertices) {
    int size = 3 * vertices.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<vertices.size(); n++) {
        Vector3 v = vertices[n];

        data[n * 3 + 0] = v.x;
        data[n * 3 + 1] = v.y;
        data[n * 3 + 2] = v.z;
    }

    this->appendFloatVertices(Array<float>(data, size));
}

void Mesh::appendVertices(List<Vector3>* vertices) {
    int size = 3 * vertices->size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<vertices->size(); n++) {
        Vector3* v = vertices->get(n);

        data[n * 3 + 0] = v->x;
        data[n * 3 + 1] = v->y;
        data[n * 3 + 2] = v->z;
    }

    this->appendFloatVertices(Array<float>(data, size));
}

// get
Array<float> Mesh::getFloatVertices() {
    return this->vertices;
}

List<Vector3>* Mesh::getVertices() {
    Array<float> array = this->getFloatVertices();

    int size = array.length();
    const float* data = array.raw();

    List<Vector3>* ret = new ArrayList<Vector3>();

    for (int i=0; i<size; i+=3) {
        Vector3* v = new Vector3(data[i], data[i + 1], data[i + 2]);
        ret->add(v);
        SafeRelease(v);
    }

    return ret;
}

Array<Vector3> Mesh::getVertexArray() {
    Array<float> array = this->getFloatVertices();

    const float* data = array.raw();
    int size = array.length() / 3;

    Array<Vector3> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].x = data[i * 3 + 0];
        ret[i].y = data[i * 3 + 1];
        ret[i].z = data[i * 3 + 2];
    }

    return ret;
}

//----------------------------------
// uvs
// set
void Mesh::setFloatUVs(Array<float> uvs) {
    this->uv = uvs.clone();
}

void Mesh::setUVArray(Array<Vector2> uvs) {
    int size = 2 * uvs.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<uvs.size(); n++) {
        Vector2 v = uvs[n];

        data[n * 2 + 0] = v.x;
        data[n * 2 + 1] = v.y;
    }

    this->setFloatUVs(Array<float>(data, size));
}

void Mesh::setUVs(List<Vector2>* uvs) {
    int size = 2 * uvs->size();
    float* data = (float*)malloc(sizeof(float) * size);

    int n = 0;
    Iterator<Vector2>* it = uvs->iterator();

    while(it->hasNext()) {
        Vector2* v = it->next();

        data[n * 2 + 0] = v->x;
        data[n * 2 + 1] = v->y;

        n++;

        SafeRelease(v);
    }

    SafeDelete(it);

    this->setFloatUVs(Array<float>(data, size));
}

// append
void Mesh::appendFloatUVs(Array<float> uvs) {
    this->uv.append(uvs);
}

void Mesh::appendUVArray(Array<Vector2> uvs) {
    int size = 2 * uvs.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<uvs.size(); n++) {
        Vector2 v = uvs[n];

        data[n * 2 + 0] = v.x;
        data[n * 2 + 1] = v.y;
    }

    this->appendFloatUVs(Array<float>(data, size));
}

void Mesh::appendUVs(List<Vector2>* uvs) {
    int size = 2 * uvs->size();
    float* data = (float*)malloc(sizeof(float) * size);

    int n = 0;
    Iterator<Vector2>* it = uvs->iterator();

    while(it->hasNext()) {
        Vector2* v = it->next();

        data[n * 2 + 0] = v->x;
        data[n * 2 + 1] = v->y;

        n++;

        SafeRelease(v);
    }

    SafeDelete(it);

    this->appendFloatUVs(Array<float>(data, size));
}

// get
Array<float> Mesh::getFloatUVs() {
    return this->uv;
}

List<Vector2>* Mesh::getUVs() {
    Array<float> array = this->getFloatUVs();

    int size = array.length();
    const float* data = array.raw();

    List<Vector2>* ret = new ArrayList<Vector2>();

    for (int i=0; i<size; i+=2) {
        Vector2* v = new Vector2(data[i], data[i + 1]);
        ret->add(v);
        SafeRelease(v);
    }

    return ret;
}

Array<Vector2> Mesh::getUVArray() {
    Array<float> array = this->getFloatUVs();

    const float* data = array.raw();
    int size = array.length() / 2;

    Array<Vector2> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].x = data[i * 2 + 0];
        ret[i].y = data[i * 2 + 1];
    }

    return ret;
}


//----------------------------------------
// uv2
// set
void Mesh::setFloatUV2s(Array<float> uv2s) {
    this->uv2 = uv2s.clone();
}

void Mesh::setUV2Array(Array<Vector2> uv2s) {
    int size = 2 * uv2s.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<uv2s.size(); n++) {
        Vector2 v = uv2s[n];

        data[n * 2 + 0] = v.x;
        data[n * 2 + 1] = v.y;
    }

    this->setFloatUV2s(Array<float>(data, size));
}

void Mesh::setUV2s(List<Vector2>* uv2s) {
    int size = 3 * uv2s->size();
    float* data = (float*)malloc(sizeof(float) * size);

    int n = 0;
    Iterator<Vector2>* it = uv2s->iterator();

    while(it->hasNext()) {
        Vector2* v = it->next();

        data[n * 2 + 0] = v->x;
        data[n * 2 + 1] = v->y;

        n++;

        SafeRelease(v);
    }

    SafeDelete(it);

    this->setFloatVertices(Array<float>(data, size));
}

// append
void Mesh::appendFloatUV2s(Array<float> uv2s) {
    this->uv2.append(uv2s);
}

void Mesh::appendUV2Array(Array<Vector2> uv2s) {
    int size = 2 * uv2s.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<uv2s.size(); n++) {
        Vector2 v = uv2s[n];

        data[n * 2 + 0] = v.x;
        data[n * 2 + 1] = v.y;
    }

    this->appendFloatUV2s(Array<float>(data, size));
}

void Mesh::appendUV2s(List<Vector2>* uv2s) {
    int size = 3 * uv2s->size();
    float* data = (float*)malloc(sizeof(float) * size);

    int n = 0;
    Iterator<Vector2>* it = uv2s->iterator();

    while(it->hasNext()) {
        Vector2* v = it->next();

        data[n * 2 + 0] = v->x;
        data[n * 2 + 1] = v->y;

        n++;

        SafeRelease(v);
    }

    SafeDelete(it);

    this->appendFloatUV2s(Array<float>(data, size));
}

// get
Array<float> Mesh::getFloatUV2s() {
    return this->uv2;
}

List<Vector2>* Mesh::getUV2s() {
    Array<float> array = this->getFloatUV2s();

    int size = array.length();
    const float* data = array.raw();

    List<Vector2>* ret = new ArrayList<Vector2>();

    for (int i=0; i<size; i+=2) {
        Vector2* v = new Vector2(data[i], data[i + 1]);
        ret->add(v);
        SafeRelease(v);
    }

    return ret;
}

Array<Vector2> Mesh::getUV2Array() {
    Array<float> array = this->getFloatUV2s();

    const float* data = array.raw();
    int size = array.length() / 2;

    Array<Vector2> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].x = data[i * 2 + 0];
        ret[i].y = data[i * 2 + 1];
    }

    return ret;
}

//------------------------------------------
// normals
// set
void Mesh::setFloatNormals(Array<float> normals) {
    this->normals = normals.clone();
}

void Mesh::setNormalArray(Array<Vector3> normals) {
    int size = 3 * normals.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<normals.size(); n++) {
        Vector3 v = normals[n];

        data[n * 3 + 0] = v.x;
        data[n * 3 + 1] = v.y;
        data[n * 3 + 2] = v.z;
    }

    this->setFloatNormals(Array<float>(data, size));
}

void Mesh::setNormals(List<Vector3>* normals) {
    int size = 3 * normals->size();
    float* data = (float*)malloc(sizeof(float) * size);

    int n = 0;
    Iterator<Vector3>* it = normals->iterator();

    while(it->hasNext()) {
        Vector3* v = it->next();

        data[n * 3 + 0] = v->x;
        data[n * 3 + 1] = v->y;
        data[n * 3 + 2] = v->z;

        n++;

        SafeRelease(v);
    }

    SafeDelete(it);

    this->setFloatNormals(Array<float>(data, size));
}

// append
void Mesh::appendFloatNormals(Array<float> normals) {
    this->normals.append(normals);
}

void Mesh::appendNormalArray(Array<Vector3> normals) {
    int size = 3 * normals.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<normals.size(); n++) {
        Vector3 v = normals[n];

        data[n * 3 + 0] = v.x;
        data[n * 3 + 1] = v.y;
        data[n * 3 + 2] = v.z;
    }

    this->appendFloatNormals(Array<float>(data, size));
}

void Mesh::appendNormals(List<Vector3>* normals) {
    int size = 3 * normals->size();
    float* data = (float*)malloc(sizeof(float) * size);

    int n = 0;
    Iterator<Vector3>* it = normals->iterator();

    while(it->hasNext()) {
        Vector3* v = it->next();

        data[n * 3 + 0] = v->x;
        data[n * 3 + 1] = v->y;
        data[n * 3 + 2] = v->z;

        n++;

        SafeRelease(v);
    }

    SafeDelete(it);

    this->appendFloatNormals(Array<float>(data, size));
}

// get
Array<float> Mesh::getFloatNormals() {
    return this->normals;
}

List<Vector3>* Mesh::getNormals() {
    Array<float> array = this->getFloatNormals();

    int size = array.length();
    const float* data = array.raw();

    List<Vector3>* ret = new ArrayList<Vector3>();

    for (int i=0; i<size; i+=3) {
        Vector3* v = new Vector3(data[i], data[i + 1], data[i + 2]);
        ret->add(v);
        SafeRelease(v);
    }

    return ret;
}

Array<Vector3> Mesh::getNormalArray() {
    Array<float> array = this->getFloatNormals();

    const float* data = array.raw();
    int size = array.length() / 3;

    Array<Vector3> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].x = data[i * 3 + 0];
        ret[i].y = data[i * 3 + 1];
        ret[i].z = data[i * 3 + 2];
    }

    return ret;
}

// ----------------------------------------------
// tangents
// set
void Mesh::setFloatTangents(Array<float> tangents) {
    this->tangents = tangents.clone();
}

void Mesh::setTangentArray(Array<Vector4> tangents) {
    int size = 4 * tangents.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<tangents.size(); n++) {
        Vector4 v = tangents[n];

        data[n * 4 + 0] = v.x;
        data[n * 4 + 1] = v.y;
        data[n * 4 + 2] = v.z;
        data[n * 4 + 3] = v.w;
    }

    this->setFloatTangents(Array<float>(data, size));
}

void Mesh::setTangents(List<Vector4>* tangents) {
    int size = 4 * tangents->size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<tangents->size(); n++) {
        Vector4* v = tangents->get(n);

        data[n * 4 + 0] = v->x;
        data[n * 4 + 1] = v->y;
        data[n * 4 + 2] = v->z;
        data[n * 4 + 3] = v->w;
    }

    this->setFloatTangents(Array<float>(data, size));
}

// append
void Mesh::appendFloatTangents(Array<float> tangents) {
    this->tangents.append(tangents);
}

void Mesh::appendTangentArray(Array<Vector4> tangents) {
    int size = 4 * tangents.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<tangents.size(); n++) {
        Vector4 v = tangents[n];

        data[n * 4 + 0] = v.x;
        data[n * 4 + 1] = v.y;
        data[n * 4 + 2] = v.z;
        data[n * 4 + 3] = v.w;
    }

    this->appendFloatTangents(Array<float>(data, size));
}

void Mesh::appendTangents(List<Vector4>* tangents) {
    int size = 4 * tangents->size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<tangents->size(); n++) {
        Vector4* v = tangents->get(n);

        data[n * 4 + 0] = v->x;
        data[n * 4 + 1] = v->y;
        data[n * 4 + 2] = v->z;
        data[n * 4 + 3] = v->w;
    }

    this->appendFloatTangents(Array<float>(data, size));
}

// get
Array<float> Mesh::getFloatTangents() {
    return Array<float>(this->tangents, this->vertexCount * 4, false);
}

List<Vector4>* Mesh::getTangents() {
    Array<float> array = this->getFloatTangents();

    int size = array.length();
    const float* data = array.raw();

    List<Vector4>* ret = new ArrayList<Vector4>();

    for (int i=0; i<size; i+=4) {
        Vector4* v = new Vector4(data[i], data[i + 1], data[i + 2], data[i + 3]);
        ret->add(v);
        SafeRelease(v);
    }

    return ret;
}

Array<Vector4> Mesh::getTangentArray() {
    Array<float> array = this->getFloatTangents();

    const float* data = array.raw();
    int size = array.length() / 4;

    Array<Vector4> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].x = data[i * 4 + 0];
        ret[i].y = data[i * 4 + 1];
        ret[i].z = data[i * 4 + 2];
        ret[i].w = data[i * 4 + 3];
    }

    return ret;
}

//--------------------------------------------
// colors32
// set
void Mesh::setByteColors32(Array<byte> colors32) {
    this->colors32 = colors32.clone();
}

void Mesh::setColors32Array(Array<Color32> colors32) {
    int size = 4 * colors32.size();
    byte* data = (byte*)malloc(sizeof(byte) * size);

    for (int n=0; n<colors32.size(); n++) {
        Color32 c = colors32[n];

        data[n * 4 + 0] = c.r;
        data[n * 4 + 1] = c.g;
        data[n * 4 + 2] = c.b;
        data[n * 4 + 3] = c.a;
    }

    this->setByteColors32(Array<byte>(data, size));
}

void Mesh::setColors32(List<Color32>* colors32) {
    int size = 4 * colors32->size();
    byte* data = (byte*)malloc(sizeof(byte) * size);

    for (int n=0; n<colors32->size(); n++) {
        Color32* c = colors32->get(n);

        data[n * 4 + 0] = c->r;
        data[n * 4 + 1] = c->g;
        data[n * 4 + 2] = c->b;
        data[n * 4 + 3] = c->a;

        SafeRelease(c);
    }

    this->setByteColors32(Array<byte>(data, size));
}

// append
void Mesh::appendByteColors32(Array<byte> colors32) {
    this->colors32.append(colors32);
}

void Mesh::appendColors32Array(Array<Color32> colors32) {
    int size = 4 * colors32.size();
    byte* data = (byte*)malloc(sizeof(byte) * size);

    for (int n=0; n<colors32.size(); n++) {
        Color32 c = colors32[n];

        data[n * 4 + 0] = c.r;
        data[n * 4 + 1] = c.g;
        data[n * 4 + 2] = c.b;
        data[n * 4 + 3] = c.a;
    }

    this->appendByteColors32(Array<byte>(data, size));
}

void Mesh::appendColors32(List<Color32>* colors32) {
    int size = 4 * colors32->size();
    byte* data = (byte*)malloc(sizeof(byte) * size);

    for (int n=0; n<colors32->size(); n++) {
        Color32* c = colors32->get(n);

        data[n * 4 + 0] = c->r;
        data[n * 4 + 1] = c->g;
        data[n * 4 + 2] = c->b;
        data[n * 4 + 3] = c->a;

        SafeRelease(c);
    }

    this->appendByteColors32(Array<byte>(data, size));
}

// get
Array<byte> Mesh::getByteColors32() {
    return Array<byte>(this->colors32, this->vertexCount * 4, false);
}

List<Color32>* Mesh::getColors32() {
    Array<byte> array = this->getByteColors32();

    int size = array.length();
    const byte* data = array.raw();

    List<Color32>* ret = new ArrayList<Color32>();

    for (int i=0; i<size; i+=4) {
        Color32* c = new Color32(data[i], data[i + 1], data[i + 2], data[i + 3]);
        ret->add(c);
        SafeRelease(c);
    }

    return ret;
}

Array<Color32> Mesh::getColors32Array() {
    Array<byte> array = this->getByteColors32();

    const byte* data = array.raw();
    int size = array.length() / 4;

    Array<Color32> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].r = data[i * 4 + 0];
        ret[i].g = data[i * 4 + 1];
        ret[i].b = data[i * 4 + 2];
        ret[i].a = data[i * 4 + 3];
    }

    return ret;
}

//------------------------------------------
// colors
// set
void Mesh::setFloatColors(Array<float> colors) {
    this->colors = colors.clone();
}

void Mesh::setColorArray(Array<Color> colors) {
    int size = 4 * colors.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<colors.size(); n++) {
        Color c = colors[n];

        data[n * 4 + 0] = c.r;
        data[n * 4 + 1] = c.g;
        data[n * 4 + 2] = c.b;
        data[n * 4 + 3] = c.a;
    }

    this->setFloatColors(Array<float>(data, size));
}

void Mesh::setColors(List<Color>* colors) {
    int size = 4 * colors->size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<colors->size(); n++) {
        Color* c = colors->get(n);

        data[n * 4 + 0] = c->r;
        data[n * 4 + 1] = c->g;
        data[n * 4 + 2] = c->b;
        data[n * 4 + 3] = c->a;

        SafeRelease(c);
    }

    this->setFloatColors(Array<float>(data, size));
}

// append
void Mesh::appendFloatColors(Array<float> colors) {
    this->colors.append(colors);
}

void Mesh::appendColorArray(Array<Color> colors) {
    int size = 3 * colors.size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<colors.size(); n++) {
        Color c = colors[n];

        data[n * 3 + 0] = c.r;
        data[n * 3 + 1] = c.g;
        data[n * 3 + 2] = c.b;
    }

    this->appendFloatColors(Array<float>(data, size));
}

void Mesh::appendColors(List<Color>* colors) {
    int size = 4 * colors->size();
    float* data = (float*)malloc(sizeof(float) * size);

    for (int n=0; n<colors->size(); n++) {
        Color* c = colors->get(n);

        data[n * 4 + 0] = c->r;
        data[n * 4 + 1] = c->g;
        data[n * 4 + 2] = c->b;
        data[n * 4 + 3] = c->a;

        SafeRelease(c);
    }

    this->appendFloatColors(Array<float>(data, size));
}

// get
Array<float> Mesh::getFloatColors() {
    return Array<float>(this->colors, this->vertexCount * 3, false);
}

List<Color>* Mesh::getColors() {
    Array<float> array = this->getFloatColors();

    int size = array.length();
    const float* data = array.raw();

    List<Color>* ret = new ArrayList<Color>();

    for (int i=0; i<size; i+=4) {
        Color* c = new Color(data[i], data[i + 1], data[i + 2]);
        ret->add(c);
        SafeRelease(c);
    }

    return ret;
}

Array<Color> Mesh::getColorArray() {
    Array<float> array = this->getFloatColors();

    const float* data = array.raw();
    int size = array.length() / 4;

    Array<Color> ret(size);

    for (int i=0; i<size; i++) {
        ret[i].r = data[i * 4 + 0];
        ret[i].g = data[i * 4 + 1];
        ret[i].b = data[i * 4 + 2];
        ret[i].a = data[i * 4 + 3];
    }

    return ret;
}


String* Mesh::getMaterialName(int submesh) {
    Mesh::MeshData data = this->getSubMeshData(submesh);
    String* name = data.materialName;

    if (name != null) {
        name->retain();
        return name;
    }

    return null;
}

//---------------------------------
bool Mesh::hasUV() {
    return this->uv != null;
}

bool Mesh::hasUV2() {
    return this->uv2 != null;
}

bool Mesh::hasVertices() {
    return this->vertices != null;
}