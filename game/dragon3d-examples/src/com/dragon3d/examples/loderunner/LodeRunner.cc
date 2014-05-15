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
    this->map = new GameMap("scene/map.js");
    this->clod = new Clod();
}

LodeRunner::~LodeRunner() {
    SafeRelease(this->map);
    SafeRelease(this->mainCamera);
    SafeRelease(this->clod);
}

void LodeRunner::setupCamera() {
    Ref<Scene> scene = this->getCurrentScene();
    Ref<GameObject> root = scene->getRoot();
    
    Ref<Camera> camera = new Camera();
    this->mainCamera->addComponent(camera);
        
    Ref<Transform> ts = camera->getTransform();
    ts->setPosition(Vector3(-32, 62, -62));
    ts->rotate(0, 180, 0);
    
    root->addChild(mainCamera);
}

void LodeRunner::onInit() {
    logger->info("init");
    
    Ref<Scene> scene = this->getCurrentScene();
    Ref<GameObject> root = scene->getRoot();

    // map
    //this->map->setSize(16, 16);
    //root->addChild(this->map);
    
    /*
    // brick
    for(int i=0; i<5; i++) {
        Ref<Brick> brick = new Brick();
        scene->add(brick);
        brick->setPosition(i * 1 + 3.5, 0.5, 3.5);
    }
    
    for(int i=0; i<5; i++) {
        Ref<Brick> brick = new Brick();
        scene->add(brick);
        brick->setPosition(i * 1 + 3.5, 1.5, 3.5);
    }
    
    // clod
    Ref<Transform> clodTs = this->clod->getTransform();
    clodTs->setPosition(Vector3(0, 0.5, 0));
    

    for(int i=0; i<32; i++) {
        Ref<Clod> clod = new Clod();
        scene->add(clod);
        clod->setPosition(i * 1 - 16, 0.5, 4.5);
    }
  
    for(int i=0; i<32; i++) {
        Ref<Clod> clod = new Clod();
        scene->add(clod);
        clod->setPosition(i * 1 - 16, 1.5, 4.5);
    }
    */

    //root->addChild(this->clod);
    
    // camera
    //setupCamera();
    mainCamera = new GameObject("MainCamera");
    Camera* camera = new Camera();
    mainCamera->addComponent(camera);
    
    //camera->rect = Rect(0.1, 0.1, 0.8, 0.8);
    camera->getTransform()->setPosition(Vector3(0, 5, -10));
    camera->getTransform()->rotate(0, 180 + 30, 0);
    camera->getTransform()->find("abc/bbb/ccc");
    root->addChild((mainCamera));
    
    //Ref<Transform> cameraTs = this->mainCamera->getTransform();
    //Ref<Transform> groundTs = this->map->getTransform();
    //Ref<Transform> clodTs = this->clod->getTransform();
    //cameraTs->lookAt(clodTs);
}

void LodeRunner::onUpdate(Scene* scene, ReadOnlyTimer* timer) {
    Ref<Transform> cameraTs = this->mainCamera->getTransform();
    cameraTs->rotate(0, timer->getDeltaTime() * 40, 0, World);

    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), World);
    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //myBox->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //child->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //myBox->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::World);
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //child->transform->rotate(0, timer->getDeltaTime() * 40, 0, Transform::Space::World);
    
    //Ref<Transform> cts = this->clod->getTransform();
    //cts->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    //cts->translate(Vector3::RIGHT.multiply(timer->getDeltaTime() * 1));
    //Ref<Transform> gts = this->ground->getTransform();
    //gts->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    
    //abc += timer->getDeltaTime() * 2;
    //myBox->transform->setEulerAngles(Vector3(0, abc, 0));
    
    //mainCamera->getTransform()->lookAt(clod->getTransform());
    
    logger->debug("tps: %f fps: %f curTime: %f", timer->getDeltaTime(), timer->getFrameRate(), timer->getTimeInSeconds());
}

void LodeRunner::onDestroy() {
    logger->info("destroy");
}
