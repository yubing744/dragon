#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_BOX_HILL)
#define DG_BOX_HILL

class DGBoxHill :
	public DGGameObject
{
public:
	DGBoxHill(void);
	virtual ~DGBoxHill(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
};

#endif