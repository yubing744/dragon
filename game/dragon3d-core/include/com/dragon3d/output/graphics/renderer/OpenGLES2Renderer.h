/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/


#ifndef OpenGLES2Renderer_Renderer_Graphics_Output_Dragon3d_Com_H
#define OpenGLES2Renderer_Renderer_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage5(com, dragon3d, output, graphics, renderer)

Import com::dragon3d::output::graphics::renderer;

class _DragonExport OpenGLES2Renderer {
public:
	OpenGLES2Renderer();
	virtual ~OpenGLES2Renderer();

public:
	
protected:
	
};//OpenGLES2Renderer

EndPackage5 //(com, dragon3d, output, graphics, renderer)

#endif //OpenGLES2Renderer_Renderer_Graphics_Output_Dragon3d_Com_H


/*

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

 */