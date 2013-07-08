#pragma once

#include "dg_config.h"

#ifndef DG_SCENE
#define DG_SCENE

#include "dg_game_object.h"
#include "dg_horizon_grid.h"

class DGScene
	:public DGGameObject
{
public:
	DGScene(void);
	virtual ~DGScene(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	virtual void turnOnHorizonGrid();
	virtual void turnOffHorizonGrid();

private:
	DGHorizonGrid* horizonGrid;
};

#endif