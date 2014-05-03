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

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/ArrayList.h>
#include <com/dragon3d/scene/model/Model.h>
#include <com/dragon3d/scene/GameObject.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene;
Import com::dragon3d::scene::model;
Import com::dragon3d::output::graphics;

const Type* Model::TYPE = TypeOf<Model>();
static Logger* logger = Logger::getLogger(Model::TYPE, ERROR);

Model::Model() 
    :mesh(null), 
    material(null), 
    materials(null) {
    this->name = new String("unnamed");
    this->bounds = new Bounds();
}

Model::~Model() {
    SafeRelease(this->name);
    SafeRelease(this->mesh);
    SafeRelease(this->material);
    SafeRelease(this->materials);
    SafeRelease(this->bounds);
}

bool Model::isTypeOf(const Type* type) {
    return Renderable::TYPE->equals(type) 
        || Model::TYPE->equals(type) 
        || Component::isTypeOf(type);
}

void Model::setMesh(Mesh* mesh) {
    SafeRelease(this->mesh);
    SafeRetain(mesh);
    this->mesh = mesh;
}

Mesh* Model::getMesh() {
    if (this->mesh == null) {
        this->mesh = new Mesh();
    }

    SafeRetain(this->mesh);
    return this->mesh;
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

void Model::setMaterials(List<Material>* materials) {
    SafeRelease(this->materials);
    this->materials = materials;
}

List<Material>* Model::getMaterials() {
    if (this->materials == null) {
        this->materials = new ArrayList<Material>();
    }

    SafeRetain(this->materials);
    return this->materials;      
}

void Model::addMaterial(Material* material) {
    List<Material>* materials = this->getMaterials();

    if (materials != null) {
        materials->add(material);
    }

    SafeRelease(materials);
}

void Model::setMatrix(const Matrix4x4& matrix) {
    this->matrix = matrix;
}

Matrix4x4 Model::getMatrix() const {
    return this->matrix;
}

Material* Model::getMaterialByName(const String& name) {
    Material* mat = this->material;

    if (mat!=null && mat->getName()->equals(name)) {
        mat->retain();
        return mat;
    }

    List<Material>* mats = this->materials;

    if (mats != null) {
        Iterator<Material>* it = mats->iterator();

        while(it->hasNext()) {
            mat = it->next();

            if (mat!=null && mat->getName()->equals(name)) {
                return mat;
            }

            SafeRelease(mat);
        }

        SafeDelete(it);
    }

    return null;
}

Bounds* Model::getBounds() {
    Ref<Transform> ts = this->getTransform();

    if (logger->isDebugEnabled()) {
        Vector3 p = ts->transformDirection(Vector3::ONE);
        Ref<String> pInfo = p.toString();
        logger->debug("model get bounds:" + pInfo);
    }

    Matrix4x4 matrix = ts->getWorldToLocalMatrix();
    return this->bounds->transform(matrix);
}

void Model::renderUnto(GraphicsRenderer* gr, Scene* scene, Camera* camera) {
    Model* model = this;
    const Matrix4x4& matrix = this->gameObject->getTransform()->getLocalToWorldMatrix();

    // draw mesh
    Mesh* mesh = this->getMesh();

    if (mesh!=null && mesh->getVertexCount()>0) {
        int count = mesh->getSubMeshCount();

        for(int i=0; i<count; i++) {
            Material* material = null;
            String* materialName = mesh->getMaterialName(i);

            if (materialName != null) {
                material = model->getMaterialByName(materialName);
                SafeRelease(materialName);
            }

            if (material == null) {
                material = model->getMaterial();
            }

            gr->drawMesh(mesh, matrix, material, camera, i);

            SafeRelease(material);
        }

    }

    SafeRelease(mesh);  
}