#pragma once

#include "dg_game.h"

#if !defined(DG_SPATIAL)
#define DG_SPATIAL

//空间物体基类
class DGSpatial
{
protected:
	//顶点
	typedef struct tagVERTEX {
		GLfloat x, y, z;
		GLfloat u, v;
	} VERTEX;

	//三角形
	typedef struct tagTRIANGLE {
		VERTEX vertexs[3];
	} TRIANGLE;

	//区段
	typedef struct tagSECTOR {
		int numTriangles;
		TRIANGLE* triangle;
	} SECTOR;
	   
public:
	DGSpatial(void);
	virtual ~DGSpatial(void);

public:
	virtual bool init()=0;
	virtual void draw()=0;
	virtual void update(DGContext* ctx)=0;
};

#endif
