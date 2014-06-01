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
 * Created:     2014/02/15
 **********************************************************************/

#include <dragon/lang/gc/Reference.h>

#include <dragon/io/File.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/assets/AssetsManager.h>

Import dragon::lang::gc;
Import dragon::io;
Import dragon::util::logging;
Import com::dragon3d::util::assets;

const Type* AssetsManager::TYPE = TypeOf<AssetsManager>();
static Logger* logger = Logger::getLogger(AssetsManager::TYPE, ERROR);

AssetsManager* AssetsManager::am = null;

AssetsManager* AssetsManager::getInstance() {
    if (am == null) {
        am = new AssetsManager();
    }

    return am;
}

AssetsManager::AssetsManager() {

}

AssetsManager::~AssetsManager() {

}

List<Resource>* AssetsManager::getResources(const String& baseURI, bool recursion) {
    List<Resource>* results = new ArrayList<Resource>();

    Ref<Resource> baseRes = new Resource(baseURI);
    
    List<Resource>* subReses = baseRes->getSubResources();
    int size = subReses->size();

    for (int i=0; i<size; i++) {
        Ref<Resource> res = subReses->get(i);

        if (res->hasSubs()) {
            if (recursion) {
                Ref<String> resURI = res->getPath();
                Ref<List<Resource> >  subReses = this->getResources(resURI, recursion);
                results->addAll(subReses);
            }
        } else {
            results->add(res);
        }
    }

    return results;
}


