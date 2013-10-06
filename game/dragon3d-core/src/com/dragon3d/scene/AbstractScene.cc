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
 * Created:     2013/10/06
 **********************************************************************/


#include <com/dragon3d/scene/AbstractScene.h>
#include <dragon/util/ArrayList.h>

Import dragon::util;
Import com::dragon3d::scene;


AbstractScene::AbstractScene() {
    this->gameObjects = new ArrayList<GameObject>();
}

AbstractScene::~AbstractScene() {
    this->gameObjects->clear();
    SafeDelete(this->gameObjects);
}

void AbstractScene::add(GameObject* gameObject) {
    if (!this->gameObjects->contains(gameObject)) {
        this->gameObjects->add(gameObject);
    }
}

void AbstractScene::remove(GameObject* gameObject) {
    this->gameObjects->remove(gameObject);
}

GameObject* AbstractScene::findFirstWithName(const char* name) {

}

List<GameObject>* AbstractScene::findWithName(const char* name) {

}

GameObject* AbstractScene::findFirstWithType(const Type& type) {

}

List<GameObject>* AbstractScene::findWithType(const Type& type) {

}

GameObject* AbstractScene::findFirstWithTag(const char* tag) {

}

List<GameObject>* AbstractScene::findWithTag(const char* tag) {

}

GameObject* AbstractScene::findFirstWithRay(Ray3* ray) {

}

List<GameObject>* AbstractScene::findWithRay(Ray3* ray) {

}

List<GameObject>* AbstractScene::getAll() {
    return this->gameObjects;
}
