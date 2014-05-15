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
#include <com/dragon3d/scene/model/Material.h>
#include <com/dragon3d/examples/loderunner/map/GameMap.h>
#include <com/dragon3d/util/assets/AssetsManager.h>
#include <com/dragon3d/util/assets/ResourceUtils.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::assets;
Import com::dragon3d::examples::loderunner::map;

const Type* GameMap::TYPE = TypeOf<GameMap>();
static Logger* logger = Logger::getLogger(GameMap::TYPE, ERROR);

GameMap::GameMap()     
    :floorboard(new com::dragon3d::scene::model::geometry::Plane()), 
    arounds(4), width(1), height(1) {

    for(int i=0; i<4; i++) {
        arounds[i] = new GameObject();
    }

    this->mapRes = null;
}

GameMap::GameMap(const String& mapPath)     
    :floorboard(new com::dragon3d::scene::model::geometry::Plane()), 
    arounds(4), width(1), height(1) {

    for(int i=0; i<4; i++) { 
        arounds[i] = new GameObject();
    }

    this->mapRes = AssetsManager::getInstance()->getResource(mapPath);
}

GameMap::~GameMap() {
    SafeRelease(this->floorboard);

    for(int i=0; i<4; i++) {
        SafeRelease(arounds[i]);
    }

    SafeRelease(this->mapRes);
}

void GameMap::onInit() {
    Ref<Material> material = this->floorboard->getMaterial();

    //Color floorColor("#F8D478");
    //material->setMainColor(floorColor);

    material->setMainColor(Color::BLACK);
    
    Ref<Texture> tex = new Texture("textures/floor_07.png");
    material->setMainTexture(tex);

    this->addComponent(this->floorboard);
    
    // add arounds
    Ref<Material> matAround = new Material();
    matAround->setMainColor(Color::BLACK);
    Ref<Texture> texAround = new Texture("textures/Wood02.tga");
    matAround->setMainTexture(texAround);
    
    // left
    Ref<Transform> leftTs = this->arounds[0]->getTransform();
    leftTs->setParent(this->transform);
    
    Ref<com::dragon3d::scene::model::geometry::Plane> leftPlane = new com::dragon3d::scene::model::geometry::Plane();
    leftPlane->setMaterial(matAround);
    this->arounds[0]->addComponent(leftPlane);

    leftTs->translate(Vector3(-1, -1, 0));
    leftTs->rotate(0, 0, -90);
    
    // front
    Ref<Transform> frontTs = this->arounds[1]->getTransform();
    frontTs->setParent(this->transform);
    
    Ref<com::dragon3d::scene::model::geometry::Plane> frontPlane = new com::dragon3d::scene::model::geometry::Plane();
    frontPlane->setMaterial(matAround);
    this->arounds[1]->addComponent(frontPlane);

    frontTs->translate(Vector3(0, -1, -1));
    frontTs->rotate(90, 0, 0);

    // right
    Ref<Transform> rightTs = this->arounds[2]->getTransform();
    rightTs->setParent(this->transform);
    
    Ref<com::dragon3d::scene::model::geometry::Plane> rightPlane = new com::dragon3d::scene::model::geometry::Plane();
    rightPlane->setMaterial(matAround);
    this->arounds[2]->addComponent(rightPlane);

    rightTs->translate(Vector3(1, -1, 0));
    rightTs->rotate(0, 0, 90);

    // back
    Ref<Transform> backTs = this->arounds[3]->getTransform();
    backTs->setParent(this->transform);
    
    Ref<com::dragon3d::scene::model::geometry::Plane> backPlane = new com::dragon3d::scene::model::geometry::Plane();
    backPlane->setMaterial(matAround);
    this->arounds[3]->addComponent(backPlane);

    backTs->translate(Vector3(0, -1, 1));
    backTs->rotate(-90, 0, 0);

    Ref<Brick> obj = new Brick();
    Ref<Transform> objTs = obj->getTransform();
    objTs->setPosition(Vector3(0, 0, 0));
    objTs->setParent(this->transform);
    
    //initMapWithJsonConfig();
    
    Ref<Transform> ts = this->getTransform();
    ts->setPosition(Vector3(0, 0, 0));
}

void GameMap::initLayerModel(int layerNum, JSONArray* datas) {
    int size = datas->size();

    for(int i=0; i<size; i++) {
        Ref<String> line = (String*)datas->get(i);
        int length = line->length();

        for(int j=0; j<length; j++) {
            wchar_u type = line->charAt(j);

            GameObject* obj = null;

            // create brick
            if (type == '1') {
                obj = new Brick();
            }

            // create clod
            else if (type == '2') {
                obj = new Clod();
            }

            if (obj != null) {
                Ref<Transform> objTS = obj->getTransform();
                //objTS->setLocalPosition(Vector3((i - this->width), layerNum + 2.5, (j - this->height)));
                //obj->setParent(this);
                
                objTS->setParent(this->transform);
            }
        }
    }
}

void GameMap::initMapWithJsonConfig() {
    if (this->mapRes != null) {
        Ref<String> json = ResourceUtils::readResourceToString(mapRes, "UTF-8");
        Ref<JSONObject> jsonObj = JSONObject::parse(json);

        for(int i=0; i<16; i++) {
            Ref<String> num = String::valueOf(i);
            Ref<String> layerName = new String("layer" + num);

            if (jsonObj->hasKey(layerName)) {
                Ref<JSONArray> datas = jsonObj->getJSONArray(layerName);
                
                if (datas != null) {
                    initLayerModel(i, datas);
                }
            }
        }
    }
}

void GameMap::setSize(float width, float height) {
    this->width = width;
    this->height = height;

    Ref<Transform> ts = this->getTransform();
    ts->setScale(Vector3(width, 1, height));

    Ref<Material> material = this->floorboard->getMaterial();
    material->setMainTextureTiling(Vector2(width * 2, height * 2));
}
