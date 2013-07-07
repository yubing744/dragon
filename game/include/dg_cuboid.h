#pragma once

#include "dg_game.h"
#include "dg_component.h"
#include "dg_game_object.h"
#include "dg_material.h"
#include "dg_mesh.h"

#if !defined(DG_CUBOID)
#define DG_CUBOID

class DGCuboid :
	public DGComponent
{
public:
	DGCuboid(void);

    /*
	DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize);
	DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position);
	DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position, DGColor color);
	DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position, DGMaterial material);
	DGCuboid(DGfloat xSize, DGfloat ySize, DGfloat zSize, DGVector3 position, DGColor color, DGTexture texture);
    */

	virtual ~DGCuboid(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

public:
	virtual void setColor(const DGColor& color);
	virtual void setMaterial(DGMaterial* material);

protected:
	virtual void drawModel();
	
public:
	DGfloat xSize;
	DGfloat ySize;
	DGfloat zSize;

   
	DGVector3 position;

protected:
	DGMesh* mesh;
	DGMaterial* material;

	//DGMaterial materials[6];

protected:
	DGuint base;

public:
	bool isImmutable;
};


#endif
