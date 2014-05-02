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


#ifndef GraphicsOutputController_Graphics_Output_Dragon3d_Com_H
#define GraphicsOutputController_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
 
#include <dragon/lang/Object.h>
#include <dragon/util/List.h>
#include <dragon/util/concurrent/CountDownLatch.h>

#include <com/dragon3d/scene/model/Model.h>

#include <com/dragon3d/output/OutputController.h>
#include <com/dragon3d/output/graphics/GraphicsRenderer.h>
#include <com/dragon3d/output/graphics/renderqueue/RenderQueue.h>

#include <com/dragon3d/util/debug/PlacementGrid.h>

BeginPackage4(com, dragon3d, output, graphics)

Import dragon::lang;
Import dragon::util;

Import com::dragon3d::scene::model;

Import com::dragon3d::output;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderqueue;

Import com::dragon3d::util::debug;

class GraphicsDevice;

class _DragonExport GraphicsOutputController extends(Object) 
    implements1(OutputController){
public:
	GraphicsOutputController(GraphicsDevice* graphicsDevice);
	virtual ~GraphicsOutputController();

public: // implements OutputController
    /**
     * init the output controller
     */
    virtual void init();

    /**
     * control the scene ouput.
     * 
     * @param scene [description]
     */
    virtual void output(Scene* scene);

    /**
     * destroy the output controller
     */
    virtual void destroy(); 

    /**
     * render the scene.
     * 
     * @param scene [description]
     */
    virtual void outputSceneToCamera(Scene* scene, Camera* camera);

protected:
    /**
     * find all camera.
     * 
     */
    virtual List<Camera>* findAllCameras(Scene* scene);

    /**
     * sort the cameras.
     * 
     * @param cameras [description]
     */
    virtual void sortCameras(List<Camera>* cameras);

    /**
     * culling the not visiable game object.
     * 
     * @param gameObjects [description]
     * @param renderQueue [description]
     */
    virtual void culling(Camera* camera, List<GameObject>* gameObjects);

    /**
     * check if culling the game object.
     * 
     * @param  gameObject [description]
     * @return            [description]
     */
    virtual void culling(Camera* camera, GameObject* gameObject);

protected:
    /**
     * the renderQueue for render
     */
    RenderQueue* renderQueue;

    /**
     * graphics renderer.
     */
    GraphicsRenderer* graphicsRenderer;
	
    /**
     * graphics device
     */
    GraphicsDevice* graphicsDevice;

    /**
     * placement grid
     */
    PlacementGrid* placementGrid;
    
    /**
     * whether or not to show PlacementGrid
     */
    bool showPlacementGrid;

};//GraphicsOutputController

EndPackage4 //(com, dragon3d, output, graphics)

#endif //GraphicsOutputController_Graphics_Output_Dragon3d_Com_H
