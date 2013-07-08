#pragma once

#include "dg_game.h"
#include "dg_component.h"

#if !defined(DG_CAMERA)
#define DG_CAMERA

class DGCamera
	:public DGComponent
{
public:
	DGCamera(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void setup(DGContext* ctx);

public:
	DGVector3 eye;
	DGVector3 center;
	DGVector3 up;

	DGfloat fovy;
	DGfloat aspect;
	DGfloat zNear;
	DGfloat zFar;

private:
	DGLog* log; //Out Variable
};

#endif
