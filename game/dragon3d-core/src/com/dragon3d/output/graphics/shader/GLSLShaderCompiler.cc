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


#include <com/dragon3d/output/graphics/shader/GLSLShaderCompiler.h>
#include <dragon/util/logging/Logger.h>

Import com::dragon3d::output::graphics::shader;
Import dragon::util::logging;

const Type* GLSLShaderCompiler::TYPE = TypeOf<GLSLShaderCompiler>();
static Logger* logger = Logger::getLogger(GLSLShaderCompiler::TYPE, ERROR);

GLSLShaderCompiler::GLSLShaderCompiler() {

}

GLSLShaderCompiler::~GLSLShaderCompiler() {

}

void GLSLShaderCompiler::build(Shader* shader) {

}

void GLSLShaderCompiler::use(Shader* shader) {

}

void GLSLShaderCompiler::unuse(Shader* shader) {

}

void GLSLShaderCompiler::setSampler(Shader* shader, const String& name, Texture* texture, int unit) {

}

void GLSLShaderCompiler::setMatrix(Shader* shader, const String& name, const Matrix4x4& matrix) {

}

void GLSLShaderCompiler::setInt(Shader* shader, const String& name, int val) {

}

void GLSLShaderCompiler::setFloat(Shader* shader, const String& name, float val) {

}

void GLSLShaderCompiler::setIntVector(Shader* shader, const String& name, int numComponents, const Array<int>& data) {

}

void GLSLShaderCompiler::setFloatVector(Shader* shader, const String& name, int numComponents, const Array<float>& data) {

}

void GLSLShaderCompiler::setBool(Shader* shader, const String& name, float val) {
    
}
