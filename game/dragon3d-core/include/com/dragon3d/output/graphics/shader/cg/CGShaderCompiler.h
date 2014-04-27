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


#ifndef CGShaderCompiler_Cg_Shader_Graphics_Output_Dragon3d_Com_H
#define CGShaderCompiler_Cg_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage6(com, dragon3d, output, graphics, shader, cg)

Import dragon::lang;

class_ CGShaderCompiler extends(Object) {
public:
    static const Type* TYPE;
    
public:
    CGShaderCompiler();
    virtual ~CGShaderCompiler();

public:
    
protected:
    
};//CGShaderCompiler

EndPackage6 //(com, dragon3d, output, graphics, shader, cg)

#endif //CGShaderCompiler_Cg_Shader_Graphics_Output_Dragon3d_Com_H
