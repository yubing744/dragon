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
 * Created:     2014/03/19
 **********************************************************************/

#include <dragon/util/TreeMap.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/assets/modelio/spi/ModelLoaderRegistry.h>

#include <com/dragon3d/util/assets/modelio/plugins/obj/ObjModelLoader.h>
#include <com/dragon3d/util/assets/modelio/plugins/max/Max3DSModelLoader.h>

Import dragon::util::logging;
Import com::dragon3d::util::assets::modelio::spi;
Import com::dragon3d::util::assets::modelio::plugins::obj;
Import com::dragon3d::util::assets::modelio::plugins::max;

const Type* ModelLoaderRegistry::TYPE = TypeOf<ModelLoaderRegistry>();
static Logger* logger = Logger::getLogger(ModelLoaderRegistry::TYPE, ERROR);

ModelLoaderRegistry* ModelLoaderRegistry::singleton = null;

ModelLoaderRegistry* ModelLoaderRegistry::getInstance() {
    if (ModelLoaderRegistry::singleton == null) {
        ModelLoaderRegistry::singleton = new ModelLoaderRegistry();
    }
    
    return ModelLoaderRegistry::singleton;
}

ModelLoaderRegistry::ModelLoaderRegistry() {
    this->loaderMap = new TreeMap<String, ModelLoader>();

    this->init();
}

ModelLoaderRegistry::~ModelLoaderRegistry() {
    SafeRelease(this->loaderMap);
}

void ModelLoaderRegistry::init() {
    registerModelLoader("OBJ", new ObjModelLoader());
    registerModelLoader("3DS", new Max3DSModelLoader());
}

void ModelLoaderRegistry::registerModelLoader(const String& modelType, ModelLoader* loader) {
    this->loaderMap->put(modelType, loader);
}

ModelLoader* ModelLoaderRegistry::getModelLoader(const String& modelType) {
    return this->loaderMap->get(modelType);
}
