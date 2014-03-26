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
 * Created:     2014/03/26
 **********************************************************************/


#ifndef ObjMTLLoader_Obj_Plugins_Modelio_Assets_Util_Dragon3d_Com_H
#define ObjMTLLoader_Obj_Plugins_Modelio_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/util/List.h>
#include <com/dragon3d/scene/model/Material.h>
#include <com/dragon3d/util/assets/Resource.h>
#include <com/dragon3d/util/assets/modelio/ModelLoadException.h>

BeginPackage7(com, dragon3d, util, assets, modelio, plugins, obj)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::scene::model;
Import com::dragon3d::util::assets;
Import com::dragon3d::util::assets::modelio;

class_ ObjMTLLoader extends(Object) {
public:
    static const Type* TYPE;
    
public:
    ObjMTLLoader();
    virtual ~ObjMTLLoader();

public:
    List<Material>* load(Resource* res) throw(ModelLoadException*);  
    
};//ObjMTLLoader

EndPackage7 //(com, dragon3d, util, assets, modelio, plugins, obj)

#endif //ObjMTLLoader_Obj_Plugins_Modelio_Assets_Util_Dragon3d_Com_H
