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
 * Created:     2013/09/15
 **********************************************************************/


#include <dragon/lang/String.h>
#include <com/dragon3d/examples/helloworld/HelloWorld.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/scene/model/geometry/Box.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/scene/SimpleScene.h>

Import dragon::lang;
Import dragon::util::logging;

Import com::dragon3d::scene;
Import com::dragon3d::examples::helloworld;
Import com::dragon3d::scene::model::geometry;
Import com::dragon3d::scene::camera;


static Logger* logger = Logger::getLogger("com::dragon3d::examples::helloworld::HelloWorld", INFO);


HelloWorld::HelloWorld() {
    Scene* scene = new SimpleScene();
    this->setNextScene(scene);
}

HelloWorld::~HelloWorld() {

}

void HelloWorld::init() {
    logger->info("init");

    Scene* scene = this->getCurrentScene();
    
    myBox = new GameObject();
    Box* box = new Box();
    myBox->addComponent(box);
    //myBox->transform->setPosition(Vector3(5, 5, 5));
    myBox->transform->setPosition(Vector3(0, 2, 2));
    
    mainCamera = new GameObject();
    Camera* camera = new Camera();
    mainCamera->addComponent(camera);
    
    camera->pixelRect = Rect(0, 0, 320, 480);
    //camera->rect = Rect(0.1, 0.1, 0.8, 0.8);
    camera->transform->setPosition(Vector3(0, 1, -5));

    camera->transform->find("abc/bbb/ccc");

    scene->add(myBox);
    scene->add(mainCamera);
}

void HelloWorld::update(Scene* scene, ReadOnlyTimer* timer) {
    myBox->transform->rotate(0, 45, 0, Transform::Space::World);
    //myBox->transform->rotation.y += (timer->getTimePerFrame() * 10000);
    
    logger->info("tps: %d", timer->getFrameRate());
}

void HelloWorld::destroy() {
    logger->info("destroy");
}