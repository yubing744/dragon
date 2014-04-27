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
 * Created:     2014/02/15
 **********************************************************************/


#ifndef AssetsManager_Assets_Util_Dragon3d_Com_H
#define AssetsManager_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

#include <dragon/util/List.h>
#include <dragon/util/ArrayList.h>

#include <com/dragon3d/util/assets/Resource.h>

BeginPackage4(com, dragon3d, util, assets)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::util::assets;

class_ AssetsManager extends(Object) {
public:
    static const Type* TYPE;

public:
    static AssetsManager* am;
    static AssetsManager* getInstance();

protected:
    AssetsManager();
public:
    virtual ~AssetsManager();

public:
    /**
     * get the base path for app.
     * 
     * @return [description]
     */
    virtual String* getAppPath();

    /**
     * get a resource from uri.
     * 
     * @param  uri [description]
     * @return     [description]
     */
    virtual Resource* getResource(const String& uri);
    
    /**
     * get all resource from baseURI, if recursion then include sub dir.
     */
    virtual List<Resource>* getResources(const String& baseURI, bool recursion); 

};//AssetsManager

EndPackage4 //(com, dragon3d, util, assets)

#endif //AssetsManager_Assets_Util_Dragon3d_Com_H
