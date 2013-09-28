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
 * Created:     2013/09/20
 **********************************************************************/


#ifndef Renderer_Renderer_Dragon3d_Com_H
#define Renderer_Renderer_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage3(com, dragon3d, renderer)

Import com::dragon3d::renderer;

/**
 * <code>Renderer</code> defines an interface for classes that handle displaying of graphics data to a render context.
 * 
 * All rendering state and tasks should be handled through this class.
 */
interface _DragonExport Renderer {
public:
	virtual ~Renderer();

public:
	virtual void viewport(int x, int y, int width, int height) = 0;
    virtual void perspective(float fovy, float aspect, float zNear, float zFar) = 0;

    /*
	virtual bool init() = 0;
	virtual void reset() = 0;
	virtual void setColor(const Color& color) = 0;
	virtual void drawLine(const Vector3& startV, const Vector3& endV) = 0;
	virtual void drawMesh(Mesh* mesh) = 0;
	virtual void swapBuffers() = 0;

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

};//Renderer

EndPackage3 //(com, dragon3d, renderer)

#endif //Renderer_Renderer_Dragon3d_Com_H
