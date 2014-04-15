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


#ifndef Max3DSModelLoader_Max_Plugins_Modelio_Assets_Util_Dragon3d_Com_H
#define Max3DSModelLoader_Max_Plugins_Modelio_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/util/assets/modelio/ModelLoader.h>

BeginPackage7(com, dragon3d, util, assets, modelio, plugins, max)

Import dragon::lang;

class_ Max3DSModelLoader extends(Object) 
    implements1(ModelLoader) {
public:
    static const Type* TYPE;
    
public:
    Max3DSModelLoader();
    virtual ~Max3DSModelLoader();

public:
    virtual GameObject* load(Resource* res) throw(ModelLoadException*);
    
};//Max3DSModelLoader

EndPackage7 //(com, dragon3d, util, assets, modelio, plugins, max)

#endif //Max3DSModelLoader_Max_Plugins_Modelio_Assets_Util_Dragon3d_Com_H
