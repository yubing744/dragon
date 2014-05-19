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
#include <com/dragon3d/util/prefab/PrefabUtility.h>
#include <com/dragon3d/scene/model/geometry/Box.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::assets;
Import com::dragon3d::util::prefab;
Import com::dragon3d::examples::loderunner::map;
Import com::dragon3d::scene::model::geometry;

const Type* GameMap::TYPE = TypeOf<GameMap>();
static Logger* logger = Logger::getLogger(GameMap::TYPE, INFO);

GameMap::GameMap(const String& mapPath) 
    :width(16), height(16) {
    this->mapRes = AssetsManager::getInstance()->getResource(mapPath);
}

GameMap::~GameMap() {
    SafeRelease(this->mapRes);
}

void GameMap::onInit() {
    logger->info("init");
    
    // the ground
    Ref<Ground> ground = new Ground();
    ground->setSize(this->width, this->height);
    this->addChild(ground);
    
    // clod prefab
    this->clodPrefab = new Clod();
    this->clodPrefab->init();

    // brick prefab
    this->brickPrefab = new Brick();
    this->brickPrefab->init();
    
    /*
    Ref<GameObject> brick = PrefabUtility::instantiatePrefab(this->brickPrefab);
    this->addChild(brick);
 
    Ref<GameObject> brick2 = PrefabUtility::instantiatePrefab(this->brickPrefab);
    brick2->setPosition(0, 1, 2);
    this->addChild(brick2);
    
    brick2->setPosition(5, 5, 5);
    */
    
    /*
    Ref<String> json = ResourceUtils::readResourceToString(this->mapRes, "UTF-8");
    Ref<JSONObject> jsonObj = JSONObject::parse(json);

    for(int i=1; i<this->width; i++) {
        Ref<String> num = String::valueOf(i);
        Ref<String> layerName = new String("layer" + num);

        if (jsonObj->hasKey(layerName)) {
            Ref<JSONArray> datas = jsonObj->getJSONArray(layerName);
            
            if (datas != null) {
                initLayerModel(i, datas);
            }
        }
    }
     */
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
                obj = PrefabUtility::instantiatePrefab(this->brickPrefab);
                //obj = new Brick();
            }

            // create clod
            else if (type == '2') {
                obj = PrefabUtility::instantiatePrefab(this->clodPrefab);
                //obj = new Clod();
            }

            if (obj != null) {
                Ref<Transform> objTS = obj->getTransform();
                objTS->setLocalPosition(Vector3((i - this->width + 0.5), layerNum, (j - this->height + 0.5)));
                obj->setParent(this);
            }
        }
    }
}
