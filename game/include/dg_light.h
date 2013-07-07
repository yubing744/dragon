#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_LIGHT)
#define DG_LIGHT

class DGLight : public DGGameObject
{
public:
	DGLight(void);
	virtual ~DGLight(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw();
	
private:
	BOOL light;
	BOOL lp;
	BOOL fp;
};

#endif