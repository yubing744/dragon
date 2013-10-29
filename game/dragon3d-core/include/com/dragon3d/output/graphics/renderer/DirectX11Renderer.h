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


#ifndef DirectX11Renderer_Renderer_Graphics_Output_Dragon3d_Com_H
#define DirectX11Renderer_Renderer_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
 
#include <com/dragon3d/scene/model/shader/Shader.h>
#include <com/dragon3d/output/graphics/GraphicsRenderer.h>

BeginPackage4(com, dragon3d, output, graphics)
    class GraphicsDevice;
EndPackage4

BeginPackage5(com, dragon3d, output, graphics, renderer)

Import com::dragon3d::scene::model::shader;
Import com::dragon3d::output::graphics::renderer;

class _DragonExport DirectX11Renderer extends(Object) 
    implements1(GraphicsRenderer) {
public:
	DirectX11Renderer(GraphicsDevice* graphicsDevice);
	virtual ~DirectX11Renderer();

public: // implements GraphicsRenderer
    virtual void init();

    virtual void clearBuffer();

    virtual void drawSample();

    virtual void drawLine(const Vector3& startV, const Vector3& endV, const Color& color, Camera* camera);

    virtual void drawMesh(Mesh* mesh, const Matrix4x4& matrix, Material* material, Camera* camera);

    virtual void flushBuffer();

protected:
    /**
     * the graphics device.
     */
    GraphicsDevice* graphicsDevice;
    
    /**
     * native data.
     */
    void* nativeData;

};//DirectX11Renderer

EndPackage5 //(com, dragon3d, output, graphics, renderer)

#endif //DirectX11Renderer_Renderer_Graphics_Output_Dragon3d_Com_H
