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

#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/scene/model/Mesh.h>

BeginPackage4(com, dragon3d, scene, model)

Import dragon::util;
Import dragon::lang::reflect;
Import com::dragon3d::scene::model;

class _DragonExport Model 
    extends(Component) {
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

public:
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
    
};//Model

EndPackage4 //(com, dragon3d, scene, model)

#endif //Model_Model_Scene_Dragon3d_Com_H
