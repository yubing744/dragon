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
 * Created:     2014/04/18
 **********************************************************************/


#ifndef GLSLShaderCompiler_Shader_Graphics_Output_Dragon3d_Com_H
#define GLSLShaderCompiler_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage5(com, dragon3d, output, graphics, shader)

Import dragon::lang;

class_ GLSLShaderCompiler extends(Object) {
public:
    static const Type* TYPE;
    
public:
    GLSLShaderCompiler();
    virtual ~GLSLShaderCompiler();

public:
    /**
     * build the shader
     * 
     */
    virtual void build(Shader* shader);

    /**
     * use the shader
     */
    virtual void use(Shader* shader);

    /**
     * unuse the shader
     */
    virtual void unuse(Shader* shader);

    /**
     * set the texture unit
     * 
     * @param name    [description]
     * @param texture [description]
     * @param unit    [description]
     */
    virtual void setSampler(Shader* shader, const String& name, Texture* texture, int unit);

    /**
     * set the matrix
     * 
     * @param name   [description]
     * @param matrix [description]
     */
    virtual void setMatrix(Shader* shader, const String& name, const Matrix4x4& matrix);

    /**
     * set int val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual void setInt(Shader* shader, const String& name, int val);

    /**
     * set float val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual void setFloat(Shader* shader, const String& name, float val);

    /**
     * set int vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual void setIntVector(Shader* shader, const String& name, int numComponents, const Array<int>& data);

    /**
     * set float vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual void setFloatVector(Shader* shader, const String& name, int numComponents, const Array<float>& data);

    /**
     * set bool val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual void setBool(Shader* shader, const String& name, float val); 
    
};//GLSLShaderCompiler

EndPackage5 //(com, dragon3d, output, graphics, shader)

#endif //GLSLShaderCompiler_Shader_Graphics_Output_Dragon3d_Com_H
