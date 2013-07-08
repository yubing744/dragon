#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_3D_TEXT)
#define DG_3D_TEXT

class DG3DText :
	public DGGameObject
{
public:
	DG3DText(void);

	DG3DText(const char *text);
	DG3DText(const char *text, DGColor color);
	DG3DText(DGVector3 position, const char *text, DGColor color);

	virtual ~DG3DText(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	const char *text;
	DGColor color;
};

#endif
