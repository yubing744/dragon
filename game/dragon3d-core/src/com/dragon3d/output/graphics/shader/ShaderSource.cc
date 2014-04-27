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


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/shader/ShaderSource.h>
#include <com/dragon3d/output/graphics/shader/ShaderException.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::shader;

const Type* ShaderSource::TYPE = TypeOf<ShaderSource>();
static Logger* logger = Logger::getLogger(ShaderSource::TYPE, ERROR);

const static String SHADER_TYPE_STR_CG = String("CG");
const static String SHADER_TYPE_STR_GLSL = String("GLSL");
const static String SHADER_TYPE_STR_HLSL = String("HLSL");

com::dragon3d::output::graphics::shader::ShaderType com::dragon3d::output::graphics::shader::ShaderTypeFromString(String* type) {
    if (type->equals("CG")) {
        return CG;
    } else if (type->equals("GLSL")) {
        return GLSL;
    } else if (type->equals("HLSL")) {
        return HLSL;
    } else {
        throw new ShaderException("not support convert shader type from string!");
    }
}

const String& com::dragon3d::output::graphics::shader::ShaderTypeToString(com::dragon3d::output::graphics::shader::ShaderType type) {
    if (type == CG) {
        return SHADER_TYPE_STR_CG;
    } else if (type == GLSL) {
        return SHADER_TYPE_STR_GLSL;
    } else if (type == HLSL) {
        return SHADER_TYPE_STR_HLSL;
    } else {
        throw new ShaderException("not support convert shader type to string");
    }
}

ShaderSource::ShaderSource(const String& name, ShaderType type, String* code) {
    this->name = new String(name);
    this->type = type;
    this->code = (String*)code->retain();
}

ShaderSource::ShaderSource(const String& name, ShaderType type, const String& code) {
    this->name = new String(name);
    this->type = type;
    this->code = new String(code);
}

ShaderSource::~ShaderSource() {
    SafeRelease(this->name);
    SafeRelease(this->code);
}

/**
 * set the shader name.
 * 
 * @param name [description]
 */
void ShaderSource::setName(String* name) {
    SafeReplace(this->name, name);
}

/**
 * get the shader name
 * 
 * @return [description]
 */
String* ShaderSource::getName() {
    return (String*)this->name->retain();
}

/**
 * set the shader type.
 * 
 * @param type [description]
 */
void ShaderSource::setType(ShaderType type) {
    this->type = type;
}

/**
 * get shader type
 * 
 * @return [description]
 */
ShaderType ShaderSource::getType() {
    return this->type;
}

/**
 * set the shader code
 * 
 * @param code [description]
 */
void ShaderSource::setCode(String* code) {
    SafeReplace(this->code, code);
}

/**
 * get the shader code
 * 
 * @return [description]
 */
String* ShaderSource::getCode() {
    return (String*)this->code->retain();
}
