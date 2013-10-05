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


#include <com/dragon3d/output/graphics/GraphicsOutputController.h>
#include <com/dragon3d/output/graphics/renderer/OpenGLRenderer.h>

#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsOutputController", INFO);

GraphicsOutputController::GraphicsOutputController(GraphicsDevice* graphicsDevice) {
    this->graphicsDevice = graphicsDevice;
	this->graphicsRenderer = new OpenGLRenderer(graphicsDevice);
}

GraphicsOutputController::~GraphicsOutputController() {

}

void GraphicsOutputController::init() {
	logger->info("init");

	this->graphicsRenderer->init();
}

List<Camera>* FindAllCameras(Scene* scene) {
    List<Camera>* cameras = new ArrayList<Camera>();

    List<GameObject>* gameObjects = scene->getAll();
    
    Iterator<GameObject>* it = gameObjects->iterator();

    while(it->hasNext()) {
        GameObject* gameObject = it->next();
        Camera* camera = gameObject->getComponent(Camera::TYPE);

        if (camera != null) {
            cameras->add(camera);
        }
    }

    return cameras;
}

void SortCameras(List<Camera>* cameras) {

}

void RenderSceneToCamera(GraphicsRenderer* gr, Scene* scene, Camera* camera) {

}

void GraphicsOutputController::output(Scene* scene) {
	logger->debug("render scene");

	GraphicsRenderer* gr = this->graphicsRenderer;
    
    gr->clearBuffer();

    // find all cameras and sort
    List<Camera>* cameras = FindAllCameras(scene);
    SortCameras(cameras);

    // render scene to camera
    Iterator<Camera>* it = cameras->iterator();

    while(it->hasNext()) {
        Camera* camera = it->next();
        RenderSceneToCamera(gr, scene, camera);
    }

	gr->flushBuffer();
}

void GraphicsOutputController::destroy() {
    logger->info("destroy");
}

