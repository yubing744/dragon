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


#ifndef GLSLShaderCompiler_Glsl_Shader_Graphics_Output_Dragon3d_Com_H
#define GLSLShaderCompiler_Glsl_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/util/Scanner.h>

#include <com/dragon3d/output/graphics/shader/ShaderCompiler.h>
#include <com/dragon3d/output/graphics/shader/glsl/GLSLShader.h>

BeginPackage6(com, dragon3d, output, graphics, shader, glsl)

Import dragon::util;
Import dragon::lang;
Import com::dragon3d::output::graphics::shader;

class_ GLSLShaderCompiler extends(Object) 
    implements1(ShaderCompiler) {
public:
    static const Type* TYPE;
    
public:
    GLSLShaderCompiler();
    virtual ~GLSLShaderCompiler();

public:
    /**
     * compile the shader source to shader
     * 
     */
    virtual Shader* compile(ShaderSource* source) throw(ShaderException*);
   
protected:
    /**
     * load shader by type.
     * 
     * @param  type    [description]
     * @param  define  [description]
     * @param  program [description]
     * @return         [description]
     */
    virtual unsigned int loadShader(int type, const char *define, const char *program);

    /**
     * load program.
     * 
     * @param  shader [description]
     * @param  source [description]
     * @return        [description]
     */
    virtual bool loadProgram(GLSLShader* shader, ShaderSource* source);

    /**
     * parse and set the shader name mapping.
     * 
     * @param source [description]
     * @param shader [description]
     */
    virtual void parseAndSetNameMapping(ShaderSource* source, GLSLShader* shader);
    virtual void parseShaderNameMapping(Scanner* scanner, const String& startPattern, GLSLShader* shader);
    virtual void parseTokenNameMapping(String* line, GLSLShader* shader);

};//GLSLShaderCompiler

EndPackage6 //(com, dragon3d, output, graphics, shader, glsl)

#endif //GLSLShaderCompiler_Glsl_Shader_Graphics_Output_Dragon3d_Com_H
