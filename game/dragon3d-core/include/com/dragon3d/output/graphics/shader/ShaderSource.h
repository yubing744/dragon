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


#ifndef ShaderSource_Shader_Graphics_Output_Dragon3d_Com_H
#define ShaderSource_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>

BeginPackage5(com, dragon3d, output, graphics, shader)

Import dragon::lang;

enum ShaderType {
    CG,
    GLSL,
    HLSL
};

ShaderType ShaderTypeFromString(String* type);
const String& ShaderTypeToString(ShaderType type);

/**
 * shader source.
 * 
 */
class_ ShaderSource extends(Object) {
public:
    static const Type* TYPE;

public:
    ShaderSource(const String& name, ShaderType type, String* code);
    ShaderSource(const String& name, ShaderType type, const String& code);

    virtual ~ShaderSource();

public:
    /**
     * set the shader name.
     * 
     * @param name [description]
     */
    void setName(String* name);

    /**
     * get the shader name
     * 
     * @return [description]
     */
    String* getName();

    /**
     * set the shader type.
     * 
     * @param type [description]
     */
    void setType(ShaderType type);

    /**
     * get shader type
     * 
     * @return [description]
     */
    ShaderType getType();

    /**
     * set the shader code
     * 
     * @param code [description]
     */
    void setCode(String* code);

    /**
     * get the shader code
     * 
     * @return [description]
     */
    String* getCode();

protected:
    String* name;
    ShaderType type;
    String* code;

};//ShaderSource

EndPackage5 //(com, dragon3d, output, graphics, shader)

#endif //ShaderSource_Shader_Graphics_Output_Dragon3d_Com_H
