#pragma once

#include "dg_game.h"
#include "dg_component.h"
#include "dg_game_object.h"

#if !defined(DG_TEXT_MESH)
#define DG_TEXT_MESH

class DGTextMesh :
	public DGComponent
{
public:
	DGTextMesh(void);

	DGTextMesh(const char *text);
	DGTextMesh(const char *text, DGColor color);

	virtual ~DGTextMesh(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	const char *text;
	DGColor color;

private:
	GLuint base; // 绘制字体的显示列表的开始位置
	GLYPHMETRICSFLOAT gmf[256];	// 记录256个字符的信息
};

#endif
