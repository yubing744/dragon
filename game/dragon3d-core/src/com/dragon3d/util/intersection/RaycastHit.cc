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
 * Created:     2014/05/14
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/intersection/RaycastHit.h>
#include <com/dragon3d/scene/collider/Collider.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::intersection;
Import com::dragon3d::scene::collider;

const Type* RaycastHit::TYPE = TypeOf<RaycastHit>();
static Logger* logger = Logger::getLogger(RaycastHit::TYPE, ERROR);

RaycastHit::RaycastHit(Collider* collider, float distance) {
    this->collider = (Collider*)collider->retain();
    this->distance = distance;
}

RaycastHit::~RaycastHit() {
    SafeRelease(this->collider);
}

Collider* RaycastHit::getCollider() {
    return (Collider*)collider->retain();
}

float RaycastHit::getDistance() {
    return this->distance;
}