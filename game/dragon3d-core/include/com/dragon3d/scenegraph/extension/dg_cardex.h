#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_CARDEX)
#define DG_CARDEX

class DGCardex
	:public DGGameObject
{
public:
	DGCardex(void);
	virtual ~DGCardex(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
};

#endif