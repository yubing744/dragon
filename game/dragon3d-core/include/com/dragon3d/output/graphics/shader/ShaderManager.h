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
 * Created:     2014/04/23
 **********************************************************************/


#ifndef ShaderManager_Shader_Graphics_Output_Dragon3d_Com_H
#define ShaderManager_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Integer.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/String.h>
#include <dragon/util/Map.h>

#include <dragon/lang/Object.h>
#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/util/assets/Resource.h>
#include <dragon/util/concurrent/atomic/AtomicInteger.h>

#include <com/dragon3d/output/graphics/shader/ShaderCompiler.h>

BeginPackage5(com, dragon3d, output, graphics, shader)

Import dragon::lang;
Import dragon::util;

Import com::dragon3d::util::math;
Import com::dragon3d::util::assets;
Import dragon::util::concurrent::atomic;

class_ ShaderManager extends(Object) {
public:
    static const Type* TYPE;

private:
    static ShaderManager* instance;
public:
    static ShaderManager* getInstance();

private:
    static AtomicInteger* sequence;

public:
    static int GetNextShaderID();

public:
    ShaderManager();
    virtual ~ShaderManager();

protected:
    /**
     * init the shader manager.
     */
    void init();

public:
    /**
     * get shader by shader ID
     * 
     * @param  shaderID [description]
     * @return          [description]
     */
    Shader* getShader(int shaderID);

    /**
     * get shader by shader name
     * 
     * @param  name [description]
     * @return      [description]
     */
    Shader* getShader(const String& name);

    /**
     * register shader with name, type and code.
     * 
     * @param name [description]
     * @param type [description]
     * @param code [description]
     */
    void registerShader(const String& name, ShaderType type, String* code);

    /**
     * import shader from res path.
     * 
     * @param path [description]
     */
    void importShader(const String& shaderPath);

    /**
     * import shader from res.
     * 
     * @param shaderRes [description]
     */
    void importShader(Resource* shaderRes);

    /**
     * import shader from dir.
     * 
     * @param shaderDirPath [description]
     */
    void importShaders(const String& shaderDirPath);

    /**
     * register shader compiler.
     * 
     * @param type     [description]
     * @param compiler [description]
     */
    void registerShaderCompiler(ShaderType type, ShaderCompiler* compiler);

    /**
     * check if current support shader type.
     * 
     * @param  type [description]
     * @return      [description]
     */
    bool supportShaderType(const String& type);
    
protected:
    Map<Integer, Shader>* shaders;
    Map<String, ShaderCompiler>* compilers;
    
};//ShaderManager

EndPackage5 //(com, dragon3d, output, graphics, shader)

#endif //ShaderManager_Shader_Graphics_Output_Dragon3d_Com_H
