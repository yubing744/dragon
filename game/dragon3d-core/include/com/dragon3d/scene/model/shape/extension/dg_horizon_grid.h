#pragma once

#include "dg_game.h"
#include "dg_component.h"

#if !defined(DG_HORIZON_GRID)
#define DG_HORIZON_GRID

class DGHorizonGrid
	:public DGComponent
{
public:
	DGHorizonGrid(void);
	virtual ~DGHorizonGrid(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	DGuint size;
	DGColor color;
};

#endif