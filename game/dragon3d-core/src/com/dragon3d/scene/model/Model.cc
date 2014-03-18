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
 * Created:     2013/10/04
 **********************************************************************/


#include <com/dragon3d/scene/model/Model.h>

Import com::dragon3d::scene::model;

const Type* Model::TYPE = TypeOf<Model>();

Model::Model() 
    :mesh(null), material(null) {
    this->name = new String("No Name");
}

Model::~Model() {
    SafeRelease(this->mesh);
    SafeRelease(this->material);
    SafeRelease(this->name);
}

bool Model::isTypeOf(const Type* type) {
    return Model::TYPE->equals(type) 
        || Component::isTypeOf(type);
}

void Model::setMesh(Mesh* mesh) {
    SafeRelease(this->mesh);
    SafeRetain(mesh);
    this->mesh = mesh;
}

Mesh* Model::getMesh() {
    Mesh* mesh = this->mesh;
    SafeRetain(mesh);
    return mesh;
}

void Model::setMaterial(Material* material) {
    SafeRelease(this->material);
    SafeRetain(material);
    this->material = material;
}

Material* Model::getMaterial() {
    Material* material = this->material;
    SafeRetain(material);
    return material;
}

void Model::setName(const String& name) {
    SafeRelease(this->name);
    this->name = new String(name);
}

String* Model::getName() {
    String* name = this->name;
    SafeRetain(name);
    return name;  
}
