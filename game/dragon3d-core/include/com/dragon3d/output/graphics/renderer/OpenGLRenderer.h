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


#ifndef OpenGLRenderer_Renderer_Graphics_Output_Dragon3d_Com_H
#define OpenGLRenderer_Renderer_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
 
#include <com/dragon3d/output/graphics/GraphicsRenderer.h>
#include <com/dragon3d/scene/camera/Camera.h>

BeginPackage4(com, dragon3d, output, graphics)
    class GraphicsDevice;
EndPackage4

BeginPackage5(com, dragon3d, output, graphics, renderer)

Import dragon::lang;

Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

class _DragonExport OpenGLRenderer extends(Object) 
	implements1(GraphicsRenderer) {
public:
	OpenGLRenderer(GraphicsDevice* graphicsDevice);
	virtual ~OpenGLRenderer();

public: // implements GraphicsRenderer
	virtual void init();

    virtual void clearBuffer();

	virtual void drawSample();

    virtual void drawMesh(Mesh* mesh, const Vector3& position, const Vector3& rotation, Material* material, Camera* camera);

	virtual void flushBuffer();

protected:
    /**
     * the graphics device.
     */
    GraphicsDevice* graphicsDevice;

};//OpenGLRenderer

EndPackage5 //(com, dragon3d, output, graphics, renderer)

#endif //OpenGLRenderer_Renderer_Graphics_Output_Dragon3d_Com_H
