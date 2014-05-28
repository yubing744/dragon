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

static Logger* logger = Logger::getLogger("VBOMeshCache#opengl", ERROR);

void VBOMeshCache::init() {
    glGenBuffers(1, &this->vertexBufferID);
    glGenBuffers(1, &this->indexBufferID);

    int offset = 0;

    if (mesh->hasVertices()) {
        this->posOffset = offset;
        offset += (3 * sizeof(float));
    }

    if (mesh->hasUV()) {
        this->uvOffset = offset;
        offset += (2 * sizeof(float));
    }

    if (mesh->hasUV2()) {
        this->uv2Offset = offset;
        offset += (2 * sizeof(float));
    }

    this->vtxStride = offset;

    int vtxStride = this->vtxStride / sizeof(float);

    int vc = mesh->getVertexCount();
    int meshDataSize = sizeof(float) * vtxStride * vc;
    float* meshBuf = (float*)malloc(meshDataSize);

    if (mesh->hasVertices()) {
        Array<float> vertices = mesh->getFloatVertices();
        offset = this->posOffset / sizeof(float);

        for (int i=0; i<vc; i++) {
            meshBuf[i * vtxStride + offset] = vertices[i * 3];
            meshBuf[i * vtxStride + offset + 1] = vertices[i * 3 + 1];
            meshBuf[i * vtxStride + offset + 2] = vertices[i * 3 + 2];
        }
    }

    if (mesh->hasUV()) {
        Array<float> uvs = mesh->getFloatUVs();
        offset = this->uvOffset / sizeof(float);

        for (int i=0; i<vc; i++) {
            meshBuf[i * vtxStride + offset] = uvs[i * 2];
            meshBuf[i * vtxStride + offset + 1] = uvs[i * 2 + 1];
        }
    }

    if (mesh->hasUV2()) {
        Array<float> uv2s = mesh->getFloatUV2s();
        offset = this->uv2Offset / sizeof(float);

        for (int i=0; i<vc; i++) {
            meshBuf[i * vtxStride + offset] = uv2s[i * 2];
            meshBuf[i * vtxStride + offset + 1] = uv2s[i * 2 + 1];
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID); 
    glBufferData(GL_ARRAY_BUFFER, meshDataSize, meshBuf, GL_STATIC_DRAW); 
    SafeFree(meshBuf);

    // cache indices data
    Array<unsigned short> indices = mesh->getShortIndices(0);
    int numIndices = indices.length();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numIndices, indices.raw(), GL_STATIC_DRAW);
}