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
    Ref<String> appBase = this->getAppPath();
    Ref<File> baseDir = new File(appBase, baseURI);

    List<Resource>* results = new ArrayList<Resource>();
    const Array<File*> files = baseDir->listFiles();
    
    for (int i=0; i<files.size(); i++) {
        Ref<File> file = files[i];
        Ref<String> path = file->getPath();

        if (file->isDirectory()) {
            if (recursion) {
                Ref<String> subPath = file->getRelativePath(appBase);

                Ref<List<Resource> >  subReses = this->getResources(subPath, recursion);
                results->addAll(subReses);
            }
        } else {
            Ref<Resource> res = new Resource(path);
            results->add(res);
        }
    }

    return results;
}
