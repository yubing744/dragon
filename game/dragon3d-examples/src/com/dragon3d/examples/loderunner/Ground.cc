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

#include <com/dragon3d/scene/model/Material.h>
#include <com/dragon3d/examples/loderunner/Ground.h>

Import dragon::lang::gc;
Import dragon::util::logging;

Import com::dragon3d::scene::model;
Import com::dragon3d::examples::loderunner;

const Type* Ground::TYPE = TypeOf<Ground>();
static Logger* logger = Logger::getLogger(Ground::TYPE, ERROR);

Ground::Ground() 
    :floorboard(new com::dragon3d::scene::model::geometry::Plane()), 
    arounds(4) {

}

Ground::~Ground() {
    SafeRelease(this->floorboard);

    for(int i=0; i<4; i++) {
        SafeRelease(arounds[i]);
    }
}

void Ground::onInit() {
    Ref<Material> material = this->floorboard->getMaterial();

    Color floorColor("#F8D478");
    material->setMainColor(floorColor);

    Ref<Texture> tex = new Texture("textures/floor_texture_1.png");
    material->setMainTexture(tex);

    this->addComponent(this->floorboard);
}