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
 * Created:     2013/10/17
 **********************************************************************/


#include <com/dragon3d/scene/model/shader/Shader.h>

#include <dragon/util/HashMap.h>

Import dragon::util;
Import com::dragon3d::scene::model::shader;

AtomicInteger* Shader::sequence = new AtomicInteger(0);

int Shader::GetNextShaderID() {
    return sequence->incrementAndGet();
}

Shader::Shader(const Resource* res) 
    :id(GetNextShaderID()) {

}

Shader::Shader(const String& vertexShader, const String& fragmentShader)  
    :id(GetNextShaderID()){
    this->vertexShader = new String(vertexShader);
    this->fragmentShader = new String(fragmentShader);
}

Shader::~Shader() {
    SafeRelease(this->vertexShader);
    SafeRelease(this->fragmentShader);
}

unsigned int Shader::getID() {
    return this->id;
}