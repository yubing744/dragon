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


#include <dragon/util/HashMap.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/Shader.h>
#include <com/dragon3d/framework/GameException.h>
#include <com/dragon3d/output/graphics/ShaderCompiler.h>
#include <com/dragon3d/util/assets/ResourceUtils.h>

Import dragon::util;
Import dragon::util::logging;

Import com::dragon3d::framework;
Import com::dragon3d::util;
Import com::dragon3d::output::graphics;
Import com::dragon3d::util::assets;

const Type* Shader::TYPE = TypeOf<Shader>();
static Logger* logger = Logger::getLogger(Shader::TYPE, ERROR);
AtomicInteger* Shader::sequence = new AtomicInteger(0);

int Shader::GetNextShaderID() {
    return sequence->incrementAndGet();
}

Shader::Shader(const String& source)
    :id(GetNextShaderID()) {
    this->source = new String(source);
}

Shader::Shader(Resource* res)
    :id(GetNextShaderID()) {
    this->source = ResourceUtils::readResourceToString(res, "UTF-8");
}


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
     * build the shader
     * 
     */
    virtual void build();

    /**
     * use the shader
     */
    virtual void use();

    /**
     * unuse the shader
     */
    virtual void unuse();

    /**
     * set the texture unit
     * 
     * @param name    [description]
     * @param texture [description]
     * @param unit    [description]
     */
    virtual void setSampler(const String& name, Texture* texture, int unit);

    /**
     * set the matrix
     * 
     * @param name   [description]
     * @param matrix [description]
     */
    virtual void setMatrix(const String& name, const Matrix4x4& matrix);

    /**
     * set int val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual void setInt(const String& name, int val);

    /**
     * set float val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual void setFloat(const String& name, float val);

    /**
     * set int vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual void setIntVector(const String& name, int numComponents, const Array<int>& data);

    /**
     * set float vector
     * 
     * @param name          [description]
     * @param numComponents [description]
     * @param data          [description]
     */
    virtual void setFloatVector(const String& name, int numComponents, const Array<float>& data);

    /**
     * set bool val
     * 
     * @param name [description]
     * @param val  [description]
     */
    virtual void setBool(const String& name, float val);
