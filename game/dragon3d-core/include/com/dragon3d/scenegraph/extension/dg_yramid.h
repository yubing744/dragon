#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_YRAMID)
#define DG_YRAMID

class DGYramid :
	public DGGameObject
{
public:
	DGYramid(void);
	virtual ~DGYramid(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

private:
	GLfloat rotTriangle;

	GLuint texture[1];//三种纹理的存储位置

	BOOL blend;
	BOOL bp;
};

#endif