#pragma once

#include "dg_game_object.h"

#ifndef DG_FIRST_PERSON_CONTROLLSER
#define DG_FIRST_PERSON_CONTROLLSER

#include "dg_camera.h"

static const float PIOVER_180 = 0.0174532925f;

class DGFirstPersonController :
	public DGGameObject
{
public:
	DGFirstPersonController(void);
	virtual ~DGFirstPersonController(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

private:
	DGfloat walkbias;
	DGfloat walkbiasangle;

	DGfloat forwardSpeed;
	DGfloat turnSpeed;
	DGfloat angle;

private:
	DGCamera* camera;
};

#endif