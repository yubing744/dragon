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


Import dragon::lang;
Import dragon::util::logging;
Import com::dragon3d::examples::helloworld;
Import com::dragon3d::scene::model::geometry;

static Logger* logger = Logger::getLogger("com::dragon3d::examples::helloworld::HelloWorld", INFO);


HelloWorld::HelloWorld() {

}

HelloWorld::~HelloWorld() {

}

void HelloWorld::init() {
    logger->info("init");
    
    GameObject* gameObject = new GameObject();
    
    Box* box = new Box();
    gameObject->addComponent(box);

    this->root = gameObject;
}

void HelloWorld::update(Scene* scene, ReadOnlyTimer* timer) {
    
}

void HelloWorld::destroy() {
    logger->info("destroy");
}