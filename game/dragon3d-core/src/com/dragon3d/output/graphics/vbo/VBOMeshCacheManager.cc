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
 * Created:     2014/05/21
 **********************************************************************/

#include <dragon/util/HashMap.h>
#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/vbo/VBOMeshCacheManager.h>

Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::vbo;

const Type* VBOMeshCacheManager::TYPE = TypeOf<VBOMeshCacheManager>();
static Logger* logger = Logger::getLogger(VBOMeshCacheManager::TYPE, ERROR);


VBOMeshCacheManager* VBOMeshCacheManager::VMC = null;

VBOMeshCacheManager* VBOMeshCacheManager::getInstance() {
    if (VMC == null) {
        VMC = new VBOMeshCacheManager();
    }

    return VMC;
}

VBOMeshCacheManager::VBOMeshCacheManager() :maxCacheSize(8) {
    this->caches = new HashMap<int, VBOMeshCache>();
}

VBOMeshCacheManager::~VBOMeshCacheManager() {
    SafeRelease(this->caches);
}

VBOMeshCache* VBOMeshCacheManager::getCacheMeshData(Mesh* mesh) {
    int meshID = mesh->getID();

    Ref<VBOMeshCache> cache = this->caches->get(meshID);

    if (cache.raw() == null) {
        cache = createVBOMeshCache(mesh);
        addVBOMeshCache(mesh, cache);
    }

    return (VBOMeshCache*)cache->retain();
}

VBOMeshCache* VBOMeshCacheManager::createVBOMeshCache(Mesh* mesh) {
    VBOMeshCache* cache = new VBOMeshCache(mesh);

    if (cache != null) {
        cache->init();
    }

    return cache;
}

void VBOMeshCacheManager::addVBOMeshCache(Mesh* mesh, VBOMeshCache* cache) {
    int meshID = mesh->getID();

    int size = this->caches->size();

    if (size > this->maxCacheSize) {
        Ref<Iterator<Map<int, VBOMeshCache>::Entry> > it = this->caches->iterator();

        if (it->hasNext()) {
            it->remove();
        }
    }

    this->caches->put(meshID, cache);
}
