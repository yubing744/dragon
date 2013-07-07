#pragma once

#include "dg_game.h"
#include "dg_game_object.h"
#include "dg_camera.h"

#if !defined(DG_MAIN_CAMERA)
#define DG_MAIN_CAMERA

class DGMainCamera
	:public DGGameObject
{
public:
	DGMainCamera(void);
	virtual ~DGMainCamera(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
};

#endif