#pragma once

#include "dg_config.h"

#ifndef DG_OPENGL_V20_LIB
#define DG_OPENGL_V20_LIB

#include <windows.h>

#include "dg_vector3.h"
#include "dg_matrix4x4.h"
#include "dg_graphics_lib.h"

class DGOpenGLV15Lib
	:public DGGraphicsLib
{
public:
	DGOpenGLV15Lib();
	~DGOpenGLV15Lib(void);

public: // Implements Interface DGGraphicsLib
	virtual void viewport(DGint x, DGint y, DGsizei width, DGsizei height);
    virtual void perspective(DGfloat fovy, DGfloat aspect, DGfloat zNear, DGfloat zFar);

	virtual DGboolean init();
	virtual void reset();
	virtual void setColor(const DGColor& color);
	virtual void drawLine(const DGVector3& startV, const DGVector3& endV);
	virtual void drawMesh(DGMesh* mesh);
	virtual void swapBuffers();

	virtual void translate(DGfloat x, DGfloat y, DGfloat z);
	virtual void rotate(DGfloat angle, DGfloat x, DGfloat y, DGfloat z);
	virtual void scale(DGfloat x, DGfloat y, DGfloat z);

	virtual void multMatrix(const DGMatrix4x4& matrix);
	virtual void pushMatrix();
	virtual void popMatrix();

	virtual void lookAt(DGfloat eyex, DGfloat eyey, DGfloat eyez, DGfloat centerx,
		  DGfloat centery, DGfloat centerz, DGfloat upx, DGfloat upy,
		  DGfloat upz);

	virtual void initTexture(DGTexture* texture);
	virtual void setTexture(DGTexture* texture);
	virtual void destroyTexture(DGTexture* texture);

public:
	virtual DGboolean config(HWND hWnd);

private:
	HDC	hDC;
};

#endif