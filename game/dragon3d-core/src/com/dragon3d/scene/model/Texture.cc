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
 * Created:     2013/09/28
 **********************************************************************/

#include <stdlib.h>
#include <string.h>

#include <dragon/lang/gc/Reference.h>
#include <dragon/io/FileInputStream.h>
#include <dragon/util/logging/Logger.h>
#include <dragonx/image/io/ImageIO.h>
#include <com/dragon3d/scene/model/Texture.h>
#include <com/dragon3d/util/assets/Resource.h>
#include <com/dragon3d/util/assets/AssetsManager.h>
 
Import dragon::io;
Import dragon::lang::gc;
Import dragon::util::logging;
Import dragonx::image::io;
Import com::dragon3d::scene::model;
Import com::dragon3d::util::assets;

static Logger* logger = Logger::getLogger("com::dragon3d::scene::model::Texture", INFO);

AtomicInteger* Texture::sequence = new AtomicInteger(0);

int Texture::GetNextTextureID() {
    return sequence->incrementAndGet();
}

Texture::Texture(Resource* res) {
    Ref<InputStream> is = res->getInputStream();
    Ref<String> type = res->getType();

    this->image = ImageIO::read(is.raw(), type.raw());

    is->close();
}

Texture::Texture(const String& resPath) 
    :id(GetNextTextureID()) {
    Ref<Resource> res = AssetsManager::getInstance()->getResource(resPath);
    Ref<InputStream> is = res->getInputStream();
    Ref<String> type = res->getType();

    this->image = ImageIO::read(is.raw(), type.raw());

    is->close();
}

Texture::~Texture(void){
    SafeRelease(this->image);
}

unsigned int Texture::getID() {
    return this->id;
}

int Texture::getWidth() {
    return this->image->getWidth();
}

int Texture::getHeight() {
    return this->image->getHeight();
}

Array<byte> Texture::getData() {
    return this->image->getData();
}

