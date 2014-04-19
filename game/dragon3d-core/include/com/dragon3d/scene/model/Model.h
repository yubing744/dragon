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


#ifndef Model_Model_Scene_Dragon3d_Com_H
#define Model_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/util/List.h>

#include <dragon/lang/reflect/Type.h>

#include <com/dragon3d/framework/Scene.h>
#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/scene/model/Mesh.h>
#include <com/dragon3d/output/graphics/Renderable.h>

BeginPackage4(com, dragon3d, scene, model)

Import dragon::util;
Import dragon::lang::reflect;

Import com::dragon3d::framework;
Import com::dragon3d::scene::model;
Import com::dragon3d::output::graphics;

class _DragonExport Model 
    extends(Component) implements1(Renderable) {
public:
    const static Type* TYPE;

public:
    Model();
    virtual ~Model();

public:
    /**
     * the component is type of type.
     * 
     * @param  type [description]
     * @return      [description]
     */
    virtual bool isTypeOf(const Type* type);

    virtual void setMesh(Mesh* mesh);
    virtual Mesh* getMesh();

    virtual void setMaterial(Material* material);
    virtual Material* getMaterial();
    
    virtual void setName(const String& name);
    virtual String* getName();

    virtual void setMaterials(List<Material>* materials);
    virtual List<Material>* getMaterials();
    virtual void addMaterial(Material* material);

    virtual void setMatrix(const Matrix4x4& matrix);
    virtual Matrix4x4 getMatrix() const;

    /**
     * get matrix by name.
     * 
     * @param name [description]
     */
    virtual Material* getMaterialByName(const String& name);

public: //implements Renderable
    virtual void renderUnto(GraphicsRenderer* gr, Scene* scene, Camera* camera);

protected:
    String* name;

    /**
     * get the model mesh
     * 
     * @return [description]
     */
    Mesh* mesh;

    /**
     * get the model's material
     * 
     * @return [description]
     */
    Material* material;

    /**
     * get the model's materials
     * 
     * @return [description]
     */
    List<Material>* materials;

    /**
     * the child matrix
     */
    Matrix4x4 matrix;
    
};//Model

EndPackage4 //(com, dragon3d, scene, model)

#endif //Model_Model_Scene_Dragon3d_Com_H
