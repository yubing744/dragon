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

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/scene/SimpleScene.h>
#include <com/dragon3d/scene/collider/Collider.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene;
Import com::dragon3d::scene::collider;

const Type* SimpleScene::TYPE = TypeOf<SimpleScene>();
static Logger* logger = Logger::getLogger(SimpleScene::TYPE, ERROR);

SimpleScene::SimpleScene() {

}

SimpleScene::~SimpleScene() {

}

void SimpleScene::innerDoPick(PickResults* results, GameObject* parent, Ray3* pickRay) {
    Ref<List<GameObject> > gameObjects = parent->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        Ref<Collider> collider = dynamic_cast<Collider*>(gameObject->getFirstComponent(Collider::TYPE));

        if (collider!=null && collider->isEnabled()) {
            RaycastHit* hit = null; 

            if (collider->raycast(pickRay, &hit)) {
                results->addHit(hit);
                SafeRelease(hit);
            }
        }

        this->innerDoPick(results, gameObject, pickRay);
    }  
}

PickResults* SimpleScene::doPick(Ray3* pickRay) {
    PickResults* results = new PickResults();
    GameObject* root = this->root;

    this->innerDoPick(results, root, pickRay);

    return results;
}