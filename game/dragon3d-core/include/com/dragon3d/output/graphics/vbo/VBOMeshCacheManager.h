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


#ifndef VBOMeshCacheManager_Vbo_Graphics_Output_Dragon3d_Com_H
#define VBOMeshCacheManager_Vbo_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/util/Map.h>
#include <com/dragon3d/output/graphics/vbo/VBOMeshCache.h>

BeginPackage5(com, dragon3d, output, graphics, vbo)

Import dragon::util;
Import dragon::lang;

class_ VBOMeshCacheManager extends(Object) {
public:
    static const Type* TYPE;
    
public:
    static VBOMeshCacheManager* getInstance();
private:
    static VBOMeshCacheManager* VMC;

public:
    VBOMeshCacheManager();
    virtual ~VBOMeshCacheManager();

public:
    VBOMeshCache* getCacheMeshData(Mesh* mesh);

protected:
    VBOMeshCache* createVBOMeshCache(Mesh* mesh);
    void addVBOMeshCache(Mesh* mesh, VBOMeshCache* cache);

protected:
    Map<int, VBOMeshCache>* caches;
    int maxCacheSize;

};//VBOMeshCacheManager

EndPackage5 //(com, dragon3d, output, graphics, vbo)

#endif //VBOMeshCacheManager_Vbo_Graphics_Output_Dragon3d_Com_H
