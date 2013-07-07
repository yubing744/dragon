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
