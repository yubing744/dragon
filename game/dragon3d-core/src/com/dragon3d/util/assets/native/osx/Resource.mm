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
 * Created:     2014/02/11
 **********************************************************************/

#include <dragon/io/File.h>
#include <dragon/lang/System.h>
#include <dragon/lang/StringBuffer.h>
#include <dragon/io/FileInputStream.h>

#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/assets/Resource.h>
#include <com/dragon3d/util/assets/AssetsManager.h>

Import dragon::lang;
Import dragon::io;

Import com::dragon3d::util::assets;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("Resource#ios", ERROR);

InputStream* Resource::getInputStream() {
    Ref<File> file = new File(this->uri);
    return new FileInputStream(file);
}

bool Resource::exists() {
    Ref<File> file = new File(this->uri);
    return file->exists();
}

List<Resource>* Resource::getSubResources() {
    List<Resource>* results = new ArrayList<Resource>();
    
    Ref<File> baseDir = new File(this->uri);
    const Array<File*> files = baseDir->listFiles();
    
    for (int i=0; i<files.size(); i++) {
        Ref<File> file = files[i];
        Ref<String> path = file->getPath();

        Ref<Resource> res = new Resource(path);
        results->add(res);
    }

    return results;
}

bool Resource::hasSubs() {
    Ref<File> baseDir = new File(this->uri);
    return baseDir->exists() && baseDir->isDirectory();
}
