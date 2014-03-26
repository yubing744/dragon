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


#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/assets/AssetsManager.h>
#include <com/dragon3d/util/assets/modelio/ModelIO.h>
#include <com/dragon3d/util/assets/modelio/spi/ModelLoaderRegistry.h>

Import dragon::util::logging;
Import com::dragon3d::util::assets::modelio;
Import com::dragon3d::util::assets::modelio::spi;

const Type* ModelIO::TYPE = TypeOf<ModelIO>();
static Logger* logger = Logger::getLogger(ModelIO::TYPE, ERROR);

Model* ModelIO::load(Resource* res) {
    String* type = res->getType();

    ModelLoaderRegistry* registry = ModelLoaderRegistry::getInstance();
    ModelLoader* loader = registry->getModelLoader(type);
    SafeRelease(type);

    if (loader != null) {
        return loader->load(res);
    } else {
        throw new ModelLoadException("not support model type!");
    }
}

Model* ModelIO::load(const String& resPath) {
    Resource* res = AssetsManager::getInstance()->getResource(resPath);

    Model* model = load(res);

    SafeRelease(res);

    return model;
}

Model* ModelIO::load(File* file) {
    String* path = file->getPath();
    Resource* res = new Resource(path);

    Model* model = load(res);
    
    SafeRelease(res);
    SafeRelease(path);

    return model;
}