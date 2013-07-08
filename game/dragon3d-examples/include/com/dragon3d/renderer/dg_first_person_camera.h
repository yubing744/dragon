#pragma once

#include "dg_config.h"
#include "dg_camera.h"

#if !defined(DG_FIRST_PERSON_CAMERA)
#define DG_FIRST_PERSON_CAMERA

static const float piover180 = 0.0174532925f;

class DGFirstPersonCamera :
	public DGCamera
{
public:
	DGFirstPersonCamera(void);
	~DGFirstPersonCamera(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

private:
	GLfloat walkbias;
	GLfloat walkbiasangle;

	DGfloat forwardSpeed;
	DGfloat turnSpeed;
	DGfloat angle;
};

#endif

