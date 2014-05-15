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
 * Created:     2014/05/12
 **********************************************************************/


#ifndef BspScene_Scene_Dragon3d_Com_H
#define BspScene_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/draggon3d/scene/AbstractScene.h>

BeginPackage3(com, dragon3d, scene)

Import dragon::lang;

class_ BspScene extends(AbstractScene) {
public:
    static const Type* TYPE;
    
public:
    BspScene();
    virtual ~BspScene();

public:
    
protected:
    BspNode* rootNode;
    
};//BspScene

EndPackage3 //(com, dragon3d, scene)

#endif //BspScene_Scene_Dragon3d_Com_H
