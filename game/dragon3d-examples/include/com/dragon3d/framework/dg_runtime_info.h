#pragma once

#include "dg_game.h"
#include "dg_component.h"
#include "dg_game_object.h"

#if !defined(DG_RUNTIME_INFO)
#define DG_RUNTIME_INFO

class DGRuntimeInfo :
	public DGComponent
{
public:
	DGRuntimeInfo(void);
	virtual ~DGRuntimeInfo(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

};

#endif
