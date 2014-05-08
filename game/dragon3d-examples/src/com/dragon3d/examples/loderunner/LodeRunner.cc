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
 * Created:     2014/05/05
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/scene/model/geometry/Box.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/scene/SimpleScene.h>
#include <com/dragon3d/util/math/Mathf.h>

#include <com/dragon3d/examples/loderunner/LodeRunner.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::examples::loderunner;
Import com::dragon3d::examples::loderunner::map;

const Type* LodeRunner::TYPE = TypeOf<LodeRunner>();
static Logger* logger = Logger::getLogger(LodeRunner::TYPE, ERROR);

LodeRunner::LodeRunner() {
    this->mainCamera = new GameObject("MainCamera");
    this->map = new GameMap();
    this->clod = new Clod();
}

LodeRunner::~LodeRunner() {
    SafeRelease(this->map);
    SafeRelease(this->mainCamera);
    SafeRelease(this->clod);
}

void LodeRunner::setupCamera() {
    Ref<Scene> scene = this->getCurrentScene();

    Ref<Camera> camera = new Camera();
    this->mainCamera->addComponent(camera);
    
    //camera->resize(320, 480);
    
    Ref<Transform> ts = camera->getTransform();
    ts->setPosition(Vector3(0, 6, -6));

    scene->add(mainCamera);
}

void LodeRunner::onInit() {
    logger->info("init");
    
    Ref<Scene> scene = this->getCurrentScene();

    // map
    this->map->setSize(64, 64);
    scene->add(this->map);
    
    
    // clod
    Ref<Transform> clodTs = this->clod->getTransform();
    clodTs->setPosition(Vector3(0, 0, 0));
    scene->add(this->clod);

    for(int i=0; i<5; i++) {
        Ref<Clod> clod = new Clod();
        scene->add(clod);
        clod->setPosition(i * 2 + -5.5, 0, 4.5);
    }
    
    // brick
    for(int i=0; i<5; i++) {
        Ref<Brick> brick = new Brick();
        scene->add(brick);
        brick->setPosition(i * 1 + -5.5, 0, 0.5);
    }
    
    // camera
    setupCamera();
    Ref<Transform> cameraTs = this->mainCamera->getTransform();
    Ref<Transform> groundTs = this->map->getTransform();
    cameraTs->lookAt(groundTs);
}

void LodeRunner::onUpdate(Scene* scene, ReadOnlyTimer* timer) {
    //mainCamera->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);

    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), World);
    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //myBox->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //child->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //myBox->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::World);
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //child->transform->rotate(0, timer->getDeltaTime() * 40, 0, Transform::Space::World);
    
    Ref<Transform> cts = this->clod->getTransform();
    cts->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    cts->translate(Vector3::BACK.multiply(timer->getDeltaTime() * 5));
    //Ref<Transform> gts = this->ground->getTransform();
    //gts->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    
    //abc += timer->getDeltaTime() * 2;
    //myBox->transform->setEulerAngles(Vector3(0, abc, 0));
    
    logger->debug("tps: %f fps: %f curTime: %f", timer->getDeltaTime(), timer->getFrameRate(), timer->getTimeInSeconds());
}

void LodeRunner::onDestroy() {
    logger->info("destroy");
}
