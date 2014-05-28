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

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/scene/model/Model.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <com/dragon3d/output/graphics/shader/ShaderManager.h>

#include <com/dragon3d/output/graphics/GraphicsOutputController.h>

Import dragon::util;

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene::model;
Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::shader;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsOutputController", INFO);

void GraphicsOutputController::init() {
	logger->info("init");

    // init the render queue.
    this->renderQueue = new RenderQueue();

    // init the graphics render
    this->graphicsRenderer->init();

    // load the built in shader
    ShaderManager::getInstance()->importShaders("shader/built-in"); 

    this->showPlacementGrid = false;
    this->placementGrid = new PlacementGrid();

    this->showBounds = false;
    this->boundsOutline = new BoundingBoxOutline();

    this->showModel = true;

    this->showSample = false;
}

void GraphicsOutputController::destroy() {
    logger->info("destroy");

    SafeRelease(this->renderQueue);
    SafeRelease(this->placementGrid);
}

void GraphicsOutputController::output(Scene* scene) {
	//logger->info("output scene");
    Ref<GameObject> root = scene->getRoot();
    
    // find all cameras and sort
    Ref<List<Component> > cameras = root->getComponentsInChildren(Camera::TYPE);

    // render scene to camera
    Ref<Iterator<Component> > it = cameras->iterator();

    while(it->hasNext()) {
        Ref<Camera> camera = dynamic_cast<Camera*>(it->next());

        camera->resize(graphicsDevice->width, graphicsDevice->height);

        if (camera->enabled) {
            this->outputSceneToCamera(scene, camera);
        }
    }
}

void GraphicsOutputController::culling(Camera* camera, GameObject* gameObject) {
    Ref<String> name = gameObject->getName();

    // culling this game object
    Ref<List<Component> > renderables = gameObject->getComponents(Renderable::TYPE);

    if (renderables != null && renderables->size() > 0) {
        if (logger->isDebugEnabled()) {
            Vector3 pos = gameObject->getPosition();
            Ref<String> posStr = pos.toString();

            logger->debug(name + " finded renderables");
            logger->debug(name + " pos: " + posStr);
        }

        Ref<Iterator<Component> > it = renderables->iterator();

        while(it->hasNext()) {
            Ref<Renderable> renderable = dynamic_cast<Renderable*>(it->next());
            Ref<Bounds> bounds = renderable->getBounds();

            if (logger->isDebugEnabled()) {
                Ref<String> boundsInfo = bounds->toString();
                logger->debug(name + " bounds info:" + boundsInfo);
            }

            if (bounds!=null) {
                FrustumIntersect result = camera->contains(bounds);

                switch(result) {
                    case Inside:
                        logger->debug(name + " Inside camera");
                        this->renderQueue->add(renderable);
                        break;
                    case Intersects:
                        logger->debug(name + " Intersects camera");
                        this->renderQueue->add(renderable);
                        break;
                    case Outside:
                        logger->debug(name + " Outside camera");
                        break;
                    default:
                        logger->warn("no support FrustumIntersect!");
                };
            } else {
                logger->warn("not found bounds in renderable!");
            }
        }
    }

    // culling all child
    Ref<List<GameObject> > gameObjects = gameObject->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> child = it->next();

        if (child->isActiveInHierarchy()) {
            this->culling(camera, child);
        }
    }
}

void GraphicsOutputController::outputSceneToCamera(Scene* scene, Camera* camera) {
    GraphicsRenderer* gr = this->graphicsRenderer;

    gr->clearBuffer();
    //gr->drawSample();

    // 1. clear the queue
    this->renderQueue->clear();

    // draw showPlacementGrid
    if (showPlacementGrid) {
        this->renderQueue->add(placementGrid);
    }

    if (showBounds) {
        this->renderQueue->add(this->boundsOutline);
    }

    // 2. find all visiable renderable object
    if (this->showModel) {
        Ref<GameObject> root = scene->getRoot();
        this->culling(camera, root);
    }

    // 3. sort the queue
    this->renderQueue->sort();
    if (logger->isDebugEnabled()) {
        logger->debug("the renderQueue size: %d", this->renderQueue->size());
    }

    // 4. render all
    Ref<Iterator<Renderable> > it = this->renderQueue->iterator();

    while(it->hasNext()) {
        Ref<Renderable> renderable = it->next();
        renderable->renderUnto(gr, scene, camera);
    }

    if (this->showSample) {
        gr->drawSample();
    }

    gr->flushBuffer();
}

