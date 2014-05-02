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


#include <com/dragon3d/util/debug/PlacementGrid.h>

Import com::dragon3d::util::debug;

PlacementGrid::PlacementGrid() 
    :size(200), color(Color::hexColor("#5D5C5C")){
    this->bounds = new Bounds(Vector3::ZERO, Vector3(size, 0.1f, size));
}

PlacementGrid::~PlacementGrid() {
    SafeRelease(this->bounds);
}

Bounds* PlacementGrid::getBounds() {
    return (Bounds*)this->bounds->retain();
}

void PlacementGrid::renderUnto(GraphicsRenderer* gr, Scene* scene, Camera* camera) {
    Vector3 v = camera->getTransform()->getPosition();

    int gridSize = (v.y / 10);
    gridSize = (gridSize<=0) ? 1: gridSize;
    gridSize *= 2;
    
    int radius = size / 2;

    float iif = 0.0f;
    float radiusf = radius * gridSize * 1.0f;

    for(int i=-radius; i<=radius; i++) {
        iif = i * gridSize * 1.0f;
        gr->drawLine(Vector3(radiusf, 0, iif), Vector3(-radiusf, 0, iif), this->color, camera);
        gr->drawLine(Vector3(iif, 0, radiusf), Vector3(iif, 0, -radiusf), this->color, camera);
    }
}
