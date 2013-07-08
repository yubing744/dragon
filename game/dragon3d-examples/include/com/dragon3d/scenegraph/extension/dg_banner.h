#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_BANNER)
#define DG_BANNER

class DGBanner
	:public DGGameObject
{
public:
	DGBanner(void);
	virtual ~DGBanner(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

private:
	DGVector3 points[45][45]; // Points网格顶点数组
	int wiggle_count; // 指定旗形波浪的运动速度
	DGfloat hold;

	DGuint texture[1];//纹理
};

#endif