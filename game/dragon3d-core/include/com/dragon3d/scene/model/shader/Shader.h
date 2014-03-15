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
 * Created:     2013/10/17
 **********************************************************************/


#ifndef Shader_Shader_Model_Scene_Dragon3d_Com_H
#define Shader_Shader_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Float.h>
#include <dragon/lang/String.h>
#include <dragon/util/Map.h>

#include <dragon/lang/Object.h>
#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/util/assets/Resource.h>
#include <dragon/util/concurrent/atomic/AtomicInteger.h>

BeginPackage5(com, dragon3d, scene, model, shader)

Import dragon::lang;
Import dragon::util;

Import com::dragon3d::util::math;
Import com::dragon3d::util::assets;
Import dragon::util::concurrent::atomic;

class _DragonExport Shader extends(Object) {
private:
    static AtomicInteger* sequence;

public:
    static int GetNextShaderID();

public:
    Shader(const Resource* res);
    Shader(const String& vertexShader, const String& fragmentShader);
    virtual ~Shader();

public:
    unsigned int getID();
    
public:
    String* name;

    String* vertexShader;
    String* fragmentShader;

private:
    unsigned int id;
};//Shader

EndPackage5 //(com, dragon3d, scene, model, shader)

#endif //Shader_Shader_Model_Scene_Dragon3d_Com_H
