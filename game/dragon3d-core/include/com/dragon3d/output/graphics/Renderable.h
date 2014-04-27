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
 * Created:     2014/04/06
 **********************************************************************/


#ifndef Renderable_Graphics_Output_Dragon3d_Com_H
#define Renderable_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/framework/Scene.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/output/graphics/GraphicsRenderer.h>

BeginPackage4(com, dragon3d, output, graphics)

Import com::dragon3d::framework;
Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;

interface_ Renderable {
public:
    static const Type* TYPE;

public:
    virtual ~Renderable(){};

public:
    virtual void renderUnto(GraphicsRenderer* gr, Scene* scene, Camera* camera) = 0;

};//Renderable

EndPackage4 //(com, dragon3d, output, graphics)

#endif //Renderable_Graphics_Output_Dragon3d_Com_H
