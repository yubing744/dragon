#pragma once

#include "dg_game.h"
#include "dg_cuboid.h"
#include "dg_game_object.h"

#if !defined(DG_WOOD_BOARD)
#define DG_WOOD_BOARD

class DGWoodBoard
	:public DGCuboid
{
public:
	DGWoodBoard(void);

	DGWoodBoard(DGVector3 position);
	
	virtual ~DGWoodBoard(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
};

#endif
