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


#ifndef GLSLShader_Glsl_Shader_Graphics_Output_Dragon3d_Com_H
#define GLSLShader_Glsl_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/util/Map.h>
#include <com/dragon3d/output/graphics/shader/Shader.h>


BeginPackage6(com, dragon3d, output, graphics, shader, glsl)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::output::graphics::shader;

enum GLSL_SHADER_TYPE {
    GLSL_VERTEX_SHADER,
    GLSL_FRAGMENT_SHADER
};

class_ GLSLShader extends(Object) 
    implements1(Shader) {
friend
    class GLSLShaderCompiler;

public:
    static const Type* TYPE;
    
public:
    GLSLShader();
    virtual ~GLSLShader();

public: // implements Shader    
    /**
     * get the shader's id
     * 
     * @return [description]
     */
    virtual int getID();

    /**
     * get the name of shader
     * 
     * @return [description]
     */
    virtual String* getName();

    /**
     * use the shader
     */
    virtual bool use();

    /**
     * unuse the shader
     */
    virtual bool unuse();

    /**
     * set the texture unit
     * 
     * @param name    [description]
     * @param texture [description]
     * @param unit    [description]
     */
    virtual bool setSampler(const char* name, Texture* texture, int unit);

    /**
     * set the matrix
     * 
     * @param name   [description]
     * @param matrix [description]
     */
    virtual bool setMatrix(const char* name, const Matrix4x4& matrix);

    /**
     * set int val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual bool setInt(const char* name, int val);

    /**
     * set float val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual bool setFloat(const char* name, float val);

    /**
     * set int vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual bool setIntVector(const char* name, int numComponents, const Array<int>& data);

    /**
     * set float vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual bool setFloatVector(const char* name, int numComponents, const Array<float>& data);

    /**
     * set bool val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual bool setBool(const char* name, bool val);

    /**
     * set vertex attrib pointer.
     * 
     * @param  name   [description]
     * @param  n      [description]
     * @param  t      [description]
     * @param  stride [description]
     * @param  v      [description]
     * @return        [description]
     */
    virtual bool setVertexAttribPointer(const char* name, int n, int t, int stride, const void *v);

protected:
    /**
     * init the shader
     */
    void init();

    /**
     * set the shader's name.
     * 
     * @param name [description]
     */
    void setName(const String& name);

    /**
     * init the texture.
     * 
     * @param texture [description]
     */
    unsigned int loadTextureID(Texture* texture);

    /**
     * query the name mapping
     * 
     * @param  name [description]
     * @return      [description]
     */
    String* queryNameMapping(const char* name);
   
    /**
     * register name and mapping's name.
     * 
     * @param name        [description]
     * @param mappingName [description]
     */
    void registerNameMapping(const String& name, String* mappingName);

protected:
    /**
     * the program object
     */
    unsigned int programObject;

    /**
     * the name of the shader.
     * 
     */
    String* name;

    /**
     * the name mapping
     */
    Map<String, String>* nameMap;

};//GLSLShader

EndPackage6 //(com, dragon3d, output, graphics, shader, glsl)

#endif //GLSLShader_Glsl_Shader_Graphics_Output_Dragon3d_Com_H
