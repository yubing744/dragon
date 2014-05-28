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


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/vbo/VBOMeshCache.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::vbo;

const Type* VBOMeshCache::TYPE = TypeOf<VBOMeshCache>();
static Logger* logger = Logger::getLogger(VBOMeshCache::TYPE, ERROR);

VBOMeshCache::VBOMeshCache(Mesh* mesh) 
    :vertexBufferID(0),
    indexBufferID(0),

    posOffset(0),
    normalOffset(0),
    uvOffset(0),
    uv2Offset(0),
    tangentOffset(0),
    colorOffset(0),
    color32Offset(0),

    vtxStride(0) {

    this->mesh = (Mesh*)mesh->retain();
}

VBOMeshCache::~VBOMeshCache() {
    SafeRelease(this->mesh);
}