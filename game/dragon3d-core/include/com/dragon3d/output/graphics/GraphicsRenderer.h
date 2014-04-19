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

#include <com/dragon3d/scene/model/Mesh.h>
#include <com/dragon3d/scene/model/Material.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Quaternion.h>
#include <com/dragon3d/scene/camera/Camera.h>

BeginPackage4(com, dragon3d, output, graphics)

Import com::dragon3d::util::math;
Import com::dragon3d::scene::model;
Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;

/**
 * graphices renderer.
 */
__interface _DragonExport GraphicsRenderer {
public:
	virtual ~GraphicsRenderer(){};

public:
	/**
	 * init the graphics renderer.
	 */
	virtual void init() = 0;

	/**
	 * clear buffer
	 */
	virtual void clearBuffer() = 0;

	/**
	 * draw a sample shape.
	 */
	virtual void drawSample() = 0;

	/**
	 * draw line
	 */
	virtual void drawLine(const Vector3& startV, const Vector3& endV, const Color& color, Camera* camera) = 0;

	/**
	 * draw a mesh with 
	 */
	virtual void drawMesh(Mesh* mesh, const Matrix4x4& matrix, Material* material, Camera* camera, int submeshIndex) = 0;

	/**
	 * flush the buffer
	 */
	virtual void flushBuffer() = 0;
	
};//GraphicsRenderer

EndPackage4 //(com, dragon3d, output, graphics)

#endif //GraphicsRenderer_Graphics_Output_Dragon3d_Com_H
