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


#ifndef Box_Geometry_Model_Scene_Dragon3d_Com_H
#define Box_Geometry_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/scene/model/Model.h>


BeginPackage5(com, dragon3d, scene, model, geometry)

Import com::dragon3d::scene::model;
Import com::dragon3d::scene::model::geometry;

class _DragonExport Box 
    extends(Model) {
public:
    Box();
    virtual ~Box();

public:
    float xSize;
    float ySize;
    float zSize; 
};//Box

EndPackage5 //(com, dragon3d, scene, model, geometry)

#endif //Box_Geometry_Model_Scene_Dragon3d_Com_H
