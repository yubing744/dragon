#pragma once
#include "dg_config.h"
#include "dg_game_object.h"

#if !defined(DG_STAR_GROUP)
#define DG_STAR_GROUP

const int starNum = 50;

class DGStarGroup :
	public DGGameObject
{
public:
	DGStarGroup(void);
	virtual ~DGStarGroup(void);

public:
	virtual void start();
	virtual void draw(DGContext* ctx);
	virtual void update(DGContext* ctx);

private:
	typedef struct  {
		GLfloat r, g, b;
		GLfloat dist;
		GLfloat angle;
	} Star;

	Star stars[starNum];

	GLfloat starZoom;
	GLfloat starTilt;;
	GLfloat starSpin;
	GLuint starTextures[1];
};

#endif

