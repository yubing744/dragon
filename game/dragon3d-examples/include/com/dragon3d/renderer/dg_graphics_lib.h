#pragma once

#include "dg_config.h"

#ifndef DG_GRAPHICS_LIB
#define DG_GRAPHICS_LIB

#include "dg_mesh.h"
#include "dg_color.h"

class DGTexture;

class DGGraphicsLib
{
public:
	DGGraphicsLib(void);
	virtual ~DGGraphicsLib(void);

public:
	virtual void viewport(DGint x, DGint y, DGsizei width, DGsizei height) = 0;
    virtual void perspective(DGfloat fovy, DGfloat aspect, DGfloat zNear, DGfloat zFar) = 0;

	virtual DGboolean init() = 0;
	virtual void reset() = 0;
	virtual void setColor(const DGColor& color) = 0;
	virtual void drawLine(const DGVector3& startV, const DGVector3& endV) = 0;
	virtual void drawMesh(DGMesh* mesh) = 0;
	virtual void swapBuffers() = 0;

	virtual void translate(DGfloat x, DGfloat y, DGfloat z) = 0;
	virtual void rotate(DGfloat angle, DGfloat x, DGfloat y, DGfloat z) = 0;
	virtual void scale(DGfloat x, DGfloat y, DGfloat z) = 0;

	virtual void multMatrix(const DGMatrix4x4& matrix) = 0;
	virtual void pushMatrix() = 0;
	virtual void popMatrix() = 0;

	virtual void lookAt(DGfloat eyex, DGfloat eyey, DGfloat eyez, DGfloat centerx,
		  DGfloat centery, DGfloat centerz, DGfloat upx, DGfloat upy,
		  DGfloat upz) = 0;

	virtual void initTexture(DGTexture* texture) = 0;
	virtual void setTexture(DGTexture* texture) = 0;
	virtual void destroyTexture(DGTexture* texture) = 0;
};

#endif