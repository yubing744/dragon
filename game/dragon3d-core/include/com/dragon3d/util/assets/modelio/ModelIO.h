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
 * Created:     2014/03/19
 **********************************************************************/


#ifndef ModelIO_Modelio_Assets_Util_Dragon3d_Com_H
#define ModelIO_Modelio_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/File.h>
#include <com/dragon3d/scene/GameObject.h>
#include <com/dragon3d/scene/model/Model.h>
#include <com/dragon3d/util/assets/Resource.h>

BeginPackage5(com, dragon3d, util, assets, modelio)

Import dragon::io;
Import dragon::lang;
Import com::dragon3d::scene;
Import com::dragon3d::scene::model;
Import com::dragon3d::util::assets;


class_ ModelIO extends(Object) {
public:
    static const Type* TYPE;
    
public:
    static GameObject* load(File* file);
    static GameObject* load(Resource* res);
    static GameObject* load(const String& resPath);

};//ModelIO

EndPackage5 //(com, dragon3d, util, assets, modelio)

#endif //ModelIO_Modelio_Assets_Util_Dragon3d_Com_H
