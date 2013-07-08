#pragma once

#include "dg_config.h"

#ifndef DG_OPENGL_ES_20_LIB
#define DG_OPENGL_ES_20_LIB

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "dg_log.h"
#include "dg_platform.h"
#include "dg_vector3.h"
#include "dg_matrix4x4.h"
#include "dg_graphics_lib.h"

#define GL_MODELVIEW                  0x0001
#define GL_PROJECTION                 0x0002

#include <stack>
using std::stack;

class DGOpenGLES20Lib
	:public DGGraphicsLib
{
public:
	struct Context {
		GLuint programObject;

		// Matrix Stack
		DGMatrix4x4 mvpMatrix;
		DGMatrix4x4 modelViewMatrix;
		DGMatrix4x4 perspectiveMatrix;
		DGMatrix4x4* currentMatrix;
		
		// Sampler location
	    GLint samplerLoc;

		// Color
		DGColor color;

		// Attribute locations
		GLint  mvpLoc;
	    GLint  positionLoc;
	    GLint  texCoordLoc;
		GLint  colorLoc;

		// Sampler locations
	    GLint baseMapLoc;
	    GLint lightMapLoc;

	    // Texture handle
	    GLuint baseMapTexId;
	    GLuint lightMapTexId;

		// Matrix Stack
		stack<DGMatrix4x4> modelViewMatrixStack;
		stack<DGMatrix4x4> perspectiveMatrixStack;
		stack<DGMatrix4x4>* currentMatrixStack;
	};

public:
	DGOpenGLES20Lib();
	~DGOpenGLES20Lib(void);

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

	virtual void initTexture(DGTexture* texture);
	virtual void setTexture(DGTexture* texture);
	virtual void destroyTexture(DGTexture* texture);

public: // Implements OpenGL ES 1.1 Fixed Function Vertex Pipeline
	void matrixMode(GLenum mode);
	void loadIdentity();
	void frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
	void ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);

public: // Implements OpenGL glu Function
	virtual void lookAt(DGfloat eyex, DGfloat eyey, DGfloat eyez, DGfloat centerx,
	  DGfloat centery, DGfloat centerz, DGfloat upx, DGfloat upy,
	  DGfloat upz);



public:
	virtual DGboolean config(EGLNativeWindowType winType);
	virtual void makeMvpMatrix();

private:
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	Context ctx;

public:
	DGLog* log; //Out Variable
};

#endif