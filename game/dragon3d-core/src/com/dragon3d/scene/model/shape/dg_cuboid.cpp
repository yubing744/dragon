#include "dg_cuboid.h"


DGCuboid::DGCuboid(void){
	this->isImmutable = true;

	this->xSize = 1;
	this->ySize = 1;
	this->zSize = 1;

	this->position = DGVector3::zero;

	this->mesh = new DGMesh();
	this->material = new DGMaterial(DGColor::green);

	/*
	int size = 6;
	for(int i=0; i<6; i++) {
		materials[i] = DGMaterial::defaultMaterial;
	}
	*/
}

/*
DGCuboid::DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize) {
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;

	this->position = DGVector3::zero;

	int size = 6;
	for(int i=0; i<6; i++) {
		materials[i] = DGMaterial::defaultMaterial;
	}

	isImmutable = true;
}

DGCuboid::DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position){
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;

	this->position = position;

	int size = 6;
	for(int i=0; i<6; i++) {
		materials[i] = DGMaterial::defaultMaterial;
	}

	isImmutable = true;
}

DGCuboid::DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position, DGColor color){
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;

	this->position = position;

	int size = 6;
	for(int i=0; i<6; i++) {
		materials[i] = DGMaterial::defaultMaterial;
		materials[i].color = color;
	}

	isImmutable = true;
}

DGCuboid::DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position, DGMaterial material) {
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;

	this->position = position;

	int size = 6;
	for(int i=0; i<6; i++) {
		materials[i] = material;
	}

	isImmutable = true;
}

DGCuboid::DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position, DGColor color, DGTexture texture){
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;

	this->position = position;

	int size = 6;
	for(int i=0; i<6; i++) {
		materials[i] = DGMaterial(color, texture);
	}

	isImmutable = true;
}
*/

DGCuboid::~DGCuboid(void){
	dgDelete(this->material);
	dgDelete(this->mesh);
}

void DGCuboid::drawModel(){

}

void DGCuboid::init(DGGameObject* gameObject, DGContext* ctx) {
    DGComponent::init(gameObject, ctx);

    int numVertices = 24;
    int numIndices = 36;
   
    DGfloat cubeVerts[] =
    {
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, 0.5f,
      -0.5f,  0.5f, 0.5f,
      0.5f,  0.5f, 0.5f, 
      0.5f, -0.5f, 0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
   };

   DGfloat cubeNormals[] =
   {
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
   };

   DGfloat cubeTex[] =
   {
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
    };

    DGuint cubeIndices[] =
    {
        0, 2, 1,
        0, 3, 2, 
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11, 
        12, 15, 14,
        12, 14, 13, 
        16, 17, 18,
        16, 18, 19, 
        20, 23, 22,
        20, 22, 21
    };

    this->mesh->vertexCount = numVertices;

    //Copy vertices data
    this->mesh->vertices = new DGVector3[numVertices];
    memcpy(this->mesh->vertices, cubeVerts, sizeof(cubeVerts));

    //Copy normals data
    this->mesh->normals = new DGVector3[numVertices];
    memcpy(this->mesh->normals, cubeNormals, sizeof(cubeNormals));

    //Copy vertices data
    this->mesh->uv = new DGVector2[numVertices];
    memcpy(this->mesh->uv, cubeTex, sizeof(cubeTex));


    //Copy indices data
    this->mesh->indexCount = numIndices;

    this->mesh->indices = new DGuint[numIndices];
    memcpy(this->mesh->indices, cubeIndices, sizeof(cubeIndices));

	//Init Texture
	DGGraphicsLib* gl = ctx->getGraphicsLib();
	if (this->material && this->material->mainTexture) {
		this->material->mainTexture->initTexture(gl);
	}
}

void DGCuboid::update(DGContext* ctx){

}

void DGCuboid::draw(DGContext* ctx){
    DGGraphicsLib* gl = ctx->getGraphicsLib();

	gl->setColor(this->material->color);

	if (this->material && this->material->mainTexture) {
		gl->setTexture(this->material->mainTexture);
	}

    gl->drawMesh(this->mesh);
}

void DGCuboid::setColor(const DGColor& color){
	this->material->color = color;
}

void DGCuboid::setMaterial(DGMaterial* material){
	if (material) {
		dgDelete(this->material);
		this->material = material;
	}
}
