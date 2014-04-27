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

#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/scene/model/Model.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <com/dragon3d/output/graphics/shader/ShaderManager.h>

Import dragon::util;

Import dragon::util::logging;
Import com::dragon3d::scene::model;
Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::shader;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsOutputController", INFO);

void GraphicsOutputController::init() {
	logger->info("init");

    // init the graphics render
    this->graphicsRenderer->init();

    // load the built in shader
    ShaderManager::getInstance()->importShaders("shader/built-in"); 
}

List<Camera>* GraphicsOutputController_findAllCameras(Scene* scene) {
    List<Camera>* cameras = new ArrayList<Camera>();

    List<GameObject>* gameObjects = scene->findWithType(Camera::TYPE);
    Iterator<GameObject>* it = gameObjects->iterator();

    while(it->hasNext()) {
        GameObject* gameObject = it->next();
        Camera* camera = (Camera*)gameObject->getComponent(Camera::TYPE);

        if (camera != null) {
            cameras->add(camera);
        }

        SafeRelease(gameObject);
    }

    SafeDelete(it);
    SafeRelease(gameObjects);

    return cameras;
}

void GraphicsOutputController_sortCameras(List<Camera>* cameras) {

}

void GraphicsOutputController::renderSceneToCamera(Scene* scene, Camera* camera) {
    GraphicsRenderer* gr = this->graphicsRenderer;

    camera->pixelRect.x = 0;
    camera->pixelRect.y = 0;
    camera->pixelRect.width = graphicsDevice->width;
    camera->pixelRect.height = graphicsDevice->height;

    // draw showPlacementGrid
    if (showPlacementGrid) {
        placementGrid->renderUnto(gr, scene, camera);
    }

    // draw game objects
    List<GameObject>* gameObjects = scene->findWithType(Renderable::TYPE);
    
    Iterator<GameObject>* it = gameObjects->iterator();

    while(it->hasNext()) {
        GameObject* gameObject = it->next();

        Renderable* renderable = dynamic_cast<Renderable*>(gameObject->getComponent(Renderable::TYPE));

        if (renderable != null) {
            renderable->renderUnto(gr, scene, camera);
        }

        SafeRelease(gameObject);
    }

    SafeDelete(it);
}

void GraphicsOutputController::output(Scene* scene) {
	//logger->info("output scene");

	GraphicsRenderer* gr = this->graphicsRenderer;
    
    gr->clearBuffer();

    //gr->drawSample();

    // find all cameras and sort
    List<Camera>* cameras = GraphicsOutputController_findAllCameras(scene);
    GraphicsOutputController_sortCameras(cameras);

    // render scene to camera
    Iterator<Camera>* it = cameras->iterator();

    while(it->hasNext()) {
        Camera* camera = it->next();
        this->renderSceneToCamera(scene, camera);
        SafeRelease(camera);
    }

    SafeDelete(it);
    SafeRelease(cameras);

	gr->flushBuffer();
}

void GraphicsOutputController::destroy() {
    logger->info("destroy");
}

