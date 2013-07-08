#pragma once

#include "dg_game.h"
#include "dg_cuboid.h"
#include "dg_game_object.h"

#if !defined(DG_CUBE)
#define DG_CUBE

class DGCube :
	public DGCuboid
{
public:
	DGCube(void);

	DGCube(DGfloat size);
	DGCube(DGfloat size, DGVector3 position);
	DGCube(DGfloat size, DGVector3 position, DGColor color);
	DGCube(DGfloat size, DGVector3 position, DGMaterial material);
	DGCube(DGfloat size, DGVector3 position, DGColor color, DGTexture texture);

	virtual ~DGCube(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

public:
	DGfloat size;
};

#endif
