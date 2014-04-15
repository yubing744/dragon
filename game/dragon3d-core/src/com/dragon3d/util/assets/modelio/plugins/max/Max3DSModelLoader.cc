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
 * Created:     2014/03/30
 **********************************************************************/

#include <string.h>
#include <stdlib.h>
#include <math.h>
 
#include <lib3ds/file.h>
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>

#include <dragon/lang/gc/Reference.h>
#include <com/dragon3d/scene/GameObject.h>
#include <com/dragon3d/scene/model/Model.h>
#include <com/dragon3d/util/assets/Resource.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/assets/modelio/plugins/max/Max3DSModelLoader.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::assets;
Import com::dragon3d::scene;
Import com::dragon3d::scene::model;
Import com::dragon3d::util::assets::modelio::plugins::max;

const Type* Max3DSModelLoader::TYPE = TypeOf<Max3DSModelLoader>();
static Logger* logger = Logger::getLogger(Max3DSModelLoader::TYPE, INFO);

Max3DSModelLoader::Max3DSModelLoader() {

}

Max3DSModelLoader::~Max3DSModelLoader() {

}


bool Max3DSModelLoader_loadModelFromNode(Resource* res, GameObject* gameObject, Lib3dsFile *file, Lib3dsNode* node, int depth) {
    Lib3dsNode *p;

    for (p=node->childs; p!=0; p=p->next) {
        if (p != null) {
            GameObject* child = new GameObject();
            Max3DSModelLoader_loadModelFromNode(res, child, file, p, depth + 1);
            child->transform->setParent(gameObject->transform);
            SafeRelease(child);
        }
    }

    if (node->type == LIB3DS_OBJECT_NODE) {
        Model* model = new Model();

        logger->info("load sub model '%s' depth %d", node->name, depth);

        Lib3dsMesh *mesh;
        Lib3dsMaterial *mat;

        if (strcmp(node->name,"$$$DUMMY")==0) {
            return false;
        }

        mesh = lib3ds_file_mesh_by_name(file, node->data.object.morph);
        if(mesh == NULL)
            mesh = lib3ds_file_mesh_by_name(file, node->name);

        Mesh* m = model->getMesh();

        Material* material = NULL;

        // copy the model local matrix
        Lib3dsMatrix M;
        lib3ds_matrix_copy(M, node->matrix);
        lib3ds_matrix_inv(M);
        model->setMatrix(Matrix4x4((float*)M));
       
        // vertices
        m->setFloatVertices(Array<float>((float*)mesh->pointL, 3 * mesh->points, false));

        // uvs
        m->setFloatUVs(Array<float>((float*)mesh->texelL, 2 * mesh->texels));

        // normals
        int normals = 3 * mesh->faces;
        Lib3dsVector *normalL = (Lib3dsVector *)malloc(sizeof(Lib3dsVector) * normals);
        lib3ds_mesh_calculate_normals(mesh, normalL);
        m->setFloatNormals(Array<float>((float*)normalL, 3 * normals));

        // indices
        int indexCount = mesh->faces * 3;
        int* indices = (int*)malloc(sizeof(int) * indexCount);

        for (int p=0; p<mesh->faces; ++p) {
            Lib3dsFace *f = &mesh->faceL[p];

            indices[p * 3] = f->points[0];
            indices[p * 3 + 1] = f->points[1];
            indices[p * 3 + 2] = f->points[2];
        } 
        
        m->setTriangles(Array<int>(indices, indexCount));


        // material
        Lib3dsFace *f = &mesh->faceL[0];

        if (f->material[0]) {
            mat = lib3ds_file_material_by_name(file, f->material);

            if (mat) {
                logger->info("load sub model '%s' and  material '%s'", node->name, mat->name);

                material = model->getMaterialByName(mat->name);

                if (material == null) {
                    material = new Material(String(mat->name));

                    material->setColor("_AmbientColor", Color(mat->ambient[0], mat->ambient[1], mat->ambient[2], mat->ambient[3]));
                    material->setColor("_DiffuseColor", Color(mat->diffuse[0], mat->diffuse[1], mat->diffuse[2], mat->diffuse[3]));
                    material->setColor("_SpecularColor", Color(mat->specular[0], mat->specular[1], mat->specular[2], mat->specular[3]));
                    material->setFloat("_Shininess", pow(2, 10.0 * mat->shininess));

                    if (mat->texture1_map.name[0]) {   
                        logger->info("load sub model '%s' and texture '%s'", node->name, mat->texture1_map.name);

                        Lib3dsTextureMap *tex = &mat->texture1_map;
                        
                        Ref<Resource> texRes = res->getResource(tex->name);

                        try {
                            material->mainTexture = new Texture(texRes);
                        } catch(Exception* e) {
                            e->printStackTrace();

                            Ref<String> uri = texRes->getURI();
                            const Array<char> utf8Str = uri->toUTF8CharArray();
                            logger->warn("the texture resource not found %s", utf8Str.raw());

                            SafeRelease(e);
                        }
                    }

                    model->addMaterial(material);
                }
            }

            gameObject->addComponent(model);

            SafeRelease(model);
        }
    }
}

void Max3DSModelLoader_loadModelFrom3dsFile(Resource* res, GameObject* gameObject, Lib3dsFile *file) {
    Lib3dsNode *p;

    for (p=file->nodes; p!=0; p=p->next) {
        if (p != null) {
            GameObject* child = new GameObject();
            Max3DSModelLoader_loadModelFromNode(res, child, file, p, 0);
            child->transform->setParent(gameObject->transform);
        }
    }
}

GameObject* Max3DSModelLoader::load(Resource* res) throw(ModelLoadException*) {
    String* path = res->getURI();
    char* utf8Path = path->toUTF8String();
    Lib3dsFile *file = lib3ds_file_load(utf8Path);
    SafeFree(utf8Path);

    if (!file) {
        throw new ModelLoadException("3dsplayer: Error: Loading 3DS file failed.\n");
    }

    /* No nodes?  Fabricate nodes to display all the meshes. */
    if( !file->nodes) {
        Lib3dsMesh *mesh;
        Lib3dsNode *node;

        for(mesh = file->meshes; mesh != NULL; mesh = mesh->next) {
            node = lib3ds_node_new_object();
            strcpy(node->name, mesh->name);
            node->parent_id = LIB3DS_NO_PARENT;
            lib3ds_file_insert_node(file, node);
        }
    }

    lib3ds_file_eval(file, 1.0f);

    GameObject* gameObject = new GameObject();
    Max3DSModelLoader_loadModelFrom3dsFile(res, gameObject, file);

    return gameObject;
}
