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


#ifndef VBOMeshCache_Vbo_Graphics_Output_Dragon3d_Com_H
#define VBOMeshCache_Vbo_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/scene/model/Mesh.h>

BeginPackage5(com, dragon3d, output, graphics, vbo)

Import dragon::lang;
Import com::dragon3d::scene::model;

class_ VBOMeshCache extends(Object) {
public:
    static const Type* TYPE;
    
public:
    VBOMeshCache(Mesh* mesh);
    virtual ~VBOMeshCache();

public:
    void init();
    
public:
    unsigned int vertexBufferID;
    unsigned int indexBufferID;

    unsigned int posOffset;
    unsigned int normalOffset;
    unsigned int uvOffset;
    unsigned int uv2Offset;
    unsigned int tangentOffset;
    unsigned int colorOffset;
    unsigned int color32Offset;

    int vtxStride;

protected:
    Mesh* mesh;

};//VBOMeshCache

EndPackage5 //(com, dragon3d, output, graphics, vbo)

#endif //VBOMeshCache_Vbo_Graphics_Output_Dragon3d_Com_H
