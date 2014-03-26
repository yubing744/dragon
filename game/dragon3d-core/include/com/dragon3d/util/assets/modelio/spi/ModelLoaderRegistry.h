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


#ifndef ModelLoaderRegistry_Spi_Modelio_Assets_Util_Dragon3d_Com_H
#define ModelLoaderRegistry_Spi_Modelio_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/util/Map.h>
#include <com/dragon3d/util/assets/modelio/ModelLoader.h>

BeginPackage6(com, dragon3d, util, assets, modelio, spi)

Import dragon::lang;

class_ ModelLoaderRegistry extends(Object) {
public:
    static const Type* TYPE;
    
private:
    static ModelLoaderRegistry* singleton;
public:
    static ModelLoaderRegistry* getInstance();

public:
    ModelLoaderRegistry();
    virtual ~ModelLoaderRegistry();

protected:
    virtual void init();

public:
    virtual void registerModelLoader(const String& modelType, ModelLoader* loader);
    virtual ModelLoader* getModelLoader(const String& modelType);

protected:
    Map<String, ModelLoader>* loaderMap;
    
};//ModelLoaderRegistry

EndPackage6 //(com, dragon3d, util, assets, modelio, spi)

#endif //ModelLoaderRegistry_Spi_Modelio_Assets_Util_Dragon3d_Com_H
