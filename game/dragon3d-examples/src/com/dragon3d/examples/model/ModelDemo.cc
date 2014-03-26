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
 * Created:     2014/03/22
 **********************************************************************/

#include <com/dragon3d/scene/model/geometry/Box.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/scene/SimpleScene.h>
#include <com/dragon3d/util/math/Mathf.h>
#include <com/dragon3d/util/assets/modelio/ModelIO.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/examples/model/ModelDemo.h>

Import com::dragon3d::scene;
Import com::dragon3d::scene::model::geometry;
Import com::dragon3d::scene::camera;
Import com::dragon3d::util::math;
Import com::dragon3d::util::assets::modelio;

Import com::dragon3d::examples::model;
Import dragon::util::logging;

const Type* ModelDemo::TYPE = TypeOf<ModelDemo>();
static Logger* logger = Logger::getLogger(ModelDemo::TYPE, ERROR);

ModelDemo::ModelDemo() {

}

ModelDemo::~ModelDemo() {

}

void ModelDemo::init() {
    logger->info("init");

    Scene* scene = this->getCurrentScene();
    
    myBox = new GameObject();
    Model* model = ModelIO::load("model/complex.obj");
    
    Material* material = new Material();
    material->color = Color::BLACK;
    material->mainTexture = new Texture("Textures/Wood03.jpg");
    model->setMaterial(material);
    
    myBox->addComponent(model);
    
    //myBox->transform->setScale(Vector3(0.2, 0.2, 0.2));
    myBox->transform->setPosition(Vector3(0, 0, 5));
    myBox->transform->setLocalPosition(Vector3(0, 0, 0));
    
    child = new GameObject();
    Box* box2 = new Box();
    child->addComponent(box2);
    
    child->transform->setPosition(Vector3(0, 0, 10));
    child->transform->setLocalPosition(Vector3(0, 2, 0));
    //child->transform->setLocalPosition(Vector3(1, 2, 0));
    child->transform->setParent(myBox->transform);
    
    mainCamera = new GameObject();
    Camera* camera = new Camera();
    mainCamera->addComponent(camera);
    
    camera->pixelRect = Rect(0, 0, 320, 480);
    //camera->rect = Rect(0.1, 0.1, 0.8, 0.8);
    camera->transform->setPosition(Vector3(0, 30, -120));

    camera->transform->find("abc/bbb/ccc");

    scene->add(myBox);
    scene->add(child);
    scene->add(mainCamera);
    
    SafeRelease(scene);
}

//static double abc = 0.1;

void ModelDemo::update(Scene* scene, ReadOnlyTimer* timer) {
    //mainCamera->transform->rotate(0, timer->getDeltaTime() * 40, 0, World);

    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), World);
    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    myBox->transform->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //myBox->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::World);
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //child->transform->rotate(0, timer->getDeltaTime() * 40, 0, Transform::Space::World);
    //child->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //abc += timer->getDeltaTime() * 2;
    //myBox->transform->setEulerAngles(Vector3(0, abc, 0));
    
    logger->debug("tps: %f fps: %f curTime: %f", timer->getDeltaTime(), timer->getFrameRate(), timer->getTimeInSeconds());
}

void ModelDemo::destroy() {
    logger->info("destroy");
}

