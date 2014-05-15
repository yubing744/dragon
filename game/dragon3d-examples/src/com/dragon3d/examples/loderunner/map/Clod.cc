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
 * Created:     2014/05/07
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/scene/model/geometry/Box.h>
#include <com/dragon3d/examples/loderunner/map/Clod.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene::model::geometry;
Import com::dragon3d::examples::loderunner::map;

const Type* Clod::TYPE = TypeOf<Clod>();
static Logger* logger = Logger::getLogger(Clod::TYPE, ERROR);

Clod::Clod() {

}

Clod::~Clod() {

}

void Clod::onInit() {
    Ref<Box> box = new Box();
    
    Ref<Material> material = new Material();
    material->setMainColor(Color::BLACK);
    Ref<Texture> tex = new Texture("textures/wall_10.png");
    material->setMainTexture(tex);
    box->setMaterial(material);
    
    this->addComponent(box);
}

void Clod::onUpdate(Input* input, ReadOnlyTimer* timer) {

}

void Clod::onDestroy() {
    
}
