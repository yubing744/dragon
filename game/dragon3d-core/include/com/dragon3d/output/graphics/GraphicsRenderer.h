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


#ifndef GraphicsRenderer_Graphics_Output_Dragon3d_Com_H
#define GraphicsRenderer_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, output, graphics)

Import com::dragon3d::output::graphics;

/**
 * graphices renderer.
 */
interface _DragonExport GraphicsRenderer {
public:
	virtual ~GraphicsRenderer(){};

public:
	/**
	 * init the graphics renderer.
	 */
	virtual void init() = 0;
	//virtual void viewport(int x, int y, int width, int height) = 0;
    //virtual void perspective(float fovy, float aspect, float zNear, float zFar) = 0;

	/**
	 * draw a sample shape.
	 */
	virtual void drawSample() = 0;

    /*
	virtual bool init() = 0;
	virtual void reset() = 0;
	virtual void setColor(const Color& color) = 0;
	virtual void drawLine(const Vector3& startV, const Vector3& endV) = 0;
	virtual void drawMesh(Mesh* mesh) = 0;
	*/

	virtual void flushBuffer() = 0;

	/*
	virtual void translate(float x, float y, float z) = 0;
	virtual void rotate(float angle, float x, float y, float z) = 0;
	virtual void scale(float x, float y, float z) = 0;

	virtual void multMatrix(const DGMatrix4x4& matrix) = 0;
	virtual void pushMatrix() = 0;
	virtual void popMatrix() = 0;

	virtual void lookAt(float eyex, float eyey, float eyez, float centerx,
		  float centery, float centerz, float upx, float upy,
		  float upz) = 0;

	virtual void initTexture(Texture* texture) = 0;
	virtual void setTexture(Texture* texture) = 0;
	virtual void destroyTexture(Texture* texture) = 0;
	*/
	
};//GraphicsRenderer

EndPackage4 //(com, dragon3d, output, graphics)

#endif //GraphicsRenderer_Graphics_Output_Dragon3d_Com_H



/*

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


 */