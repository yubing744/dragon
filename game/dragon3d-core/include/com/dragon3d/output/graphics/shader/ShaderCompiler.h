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


#ifndef ShaderCompiler_Shader_Graphics_Output_Dragon3d_Com_H
#define ShaderCompiler_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>

#include <com/dragon3d/output/graphics/shader/ShaderException.h>
#include <com/dragon3d/output/graphics/shader/ShaderSource.h>
#include <com/dragon3d/output/graphics/shader/Shader.h>

BeginPackage5(com, dragon3d, output, graphics, shader)

interface_ ShaderCompiler {
public:
    virtual ~ShaderCompiler(){};

public:
    /**
     * compile the shader source to shader
     * 
     */
    virtual Shader* compile(ShaderSource* source) throw(ShaderException*) = 0;
  
};//ShaderCompiler

EndPackage5 //(com, dragon3d, output, graphics, shader)

#endif //ShaderCompiler_Shader_Graphics_Output_Dragon3d_Com_H
