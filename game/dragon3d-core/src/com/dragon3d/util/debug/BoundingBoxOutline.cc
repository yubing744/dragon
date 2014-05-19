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
 * Created:     2014/05/18
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/debug/BoundingBoxOutline.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::debug;

const Type* BoundingBoxOutline::TYPE = TypeOf<BoundingBoxOutline>();
static Logger* logger = Logger::getLogger(BoundingBoxOutline::TYPE, ERROR);

BoundingBoxOutline::BoundingBoxOutline() {

}

BoundingBoxOutline::~BoundingBoxOutline() {

}

Bounds* BoundingBoxOutline::getBounds() {
    return new Bounds();
}

void BoundingBoxOutline::renderUnto(GraphicsRenderer* gr, Scene* scene, Camera* camera) {
    Ref<GameObject> root = scene->getRoot();

    Ref<List<Component> > renderables = root->getComponentsInChildren(Renderable::TYPE);

    if (renderables != null && renderables->size() > 0) {
        Ref<Iterator<Component> > it = renderables->iterator();

        while(it->hasNext()) {
            Ref<Renderable> renderable = dynamic_cast<Renderable*>(it->next());
            Ref<Bounds> bounds = renderable->getBounds();

            if (bounds!=null) {
                const Array<Vector3> corners = bounds->getCorners();

                gr->drawLine(corners[0], corners[1], Color::GREEN, camera);
                gr->drawLine(corners[1], corners[2], Color::GREEN, camera);
                gr->drawLine(corners[2], corners[3], Color::GREEN, camera);
                gr->drawLine(corners[3], corners[0], Color::GREEN, camera);

                gr->drawLine(corners[4], corners[5], Color::GREEN, camera);
                gr->drawLine(corners[5], corners[6], Color::GREEN, camera);
                gr->drawLine(corners[6], corners[7], Color::GREEN, camera);
                gr->drawLine(corners[7], corners[4], Color::GREEN, camera);

                gr->drawLine(corners[0], corners[4], Color::GREEN, camera);
                gr->drawLine(corners[1], corners[5], Color::GREEN, camera);
                gr->drawLine(corners[2], corners[6], Color::GREEN, camera);
                gr->drawLine(corners[3], corners[7], Color::GREEN, camera);
            } 
        }
    }
}
