#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_ROOM)
#define DG_ROOM

class DGRoom :
	public DGGameObject
{
public:
	DGRoom(void);
	virtual ~DGRoom(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	
private:
	SECTOR sector;
	GLuint texture[3];
};

#endif
