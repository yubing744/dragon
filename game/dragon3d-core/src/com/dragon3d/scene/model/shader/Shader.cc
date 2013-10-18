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

Shader::Shader(const char* vertexShader, const char* fragmentShader) {
    char* buf1 = (char*)malloc(strlen(vertexShader) + 1);
    strcpy(buf1, vertexShader);
    this->vertexShader = buf1;

    char* buf2 = (char*)malloc(strlen(fragmentShader) + 1);
    strcpy(buf2, fragmentShader);
    this->fragmentShader = buf2;


    this->colors = new HashMap<String, Color>();
    this->textures = new HashMap<String, Texture>();
    this->floats = new HashMap<String, Float>();
    //this->vector3s = new HashMap<String, Vector3>();
    this->matrix4x4s = new HashMap<String, Matrix4x4>();
}

Shader::~Shader() {
    SafeFree(this->vertexShader);
    SafeFree(this->fragmentShader);
}

void Shader::setColor(const char* name, const Color& color) {
    this->colors->put(String(name), new Color(color));
}

void Shader::setTexture(const char* name, Texture* texture) {
    this->textures->put(String(name), texture);
}

void Shader::setFloat(const char* name, float val) {
    this->floats->put(String(name), new Float(val));
}

void Shader::setVector3(const char* name, const Vector3& v) {
    //this->vector3s->put(String(name), new Vector3(v));
}

void Shader::setMatrix(const char* name, const Matrix4x4& mat) {
    this->matrix4x4s->put(String(name), new Matrix4x4(mat));
}
