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


#ifndef Shader_Shader_Graphics_Output_Dragon3d_Com_H
#define Shader_Shader_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/String.h>
#include <dragon/util/Map.h>

#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/scene/texture/Texture.h>

BeginPackage5(com, dragon3d, output, graphics, shader)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::util::math;
Import com::dragon3d::scene::texture;

/**
 * shader
 */
interface_ Shader {
public:
    virtual ~Shader(){};

public:    
    /**
     * get the shader's id
     * 
     * @return [description]
     */
    virtual int getID() = 0;

    /**
     * get the name of shader
     * 
     * @return [description]
     */
    virtual String* getName() = 0;

    /**
     * use the shader
     */
    virtual bool use() = 0;

    /**
     * unuse the shader
     */
    virtual bool unuse() = 0;

    /**
     * set the texture unit
     * 
     * @param name    [description]
     * @param texture [description]
     * @param unit    [description]
     */
    virtual bool setSampler(const char* name, Texture* texture, int unit) = 0;

    /**
     * set the matrix
     * 
     * @param name   [description]
     * @param matrix [description]
     */
    virtual bool setMatrix(const char* name, const Matrix4x4& matrix) = 0;

    /**
     * set int val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual bool setInt(const char* name, int val) = 0;

    /**
     * set float val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual bool setFloat(const char* name, float val) = 0;

    /**
     * set int vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual bool setIntVector(const char* name, int numComponents, const Array<int>& data) = 0;

    /**
     * set float vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual bool setFloatVector(const char* name, int numComponents, const Array<float>& data) = 0;

    /**
     * set bool val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual bool setBool(const char* name, bool val) = 0;
       
    /**
     * set vertex attrib pointer.
     * 
     * @param  name    [description]
     * @param  size    [description]
     * @param  type    [description]
     * @param  stride  [description]
     * @param  pointer [description]
     * @return         [description]
     */
    virtual bool setVertexAttribPointer(const char* name, int size, int type, int stride, const void *pointer) = 0;

};//Shader

EndPackage5 //(com, dragon3d, output, graphics, shader)

#endif //Shader_Shader_Graphics_Output_Dragon3d_Com_H
