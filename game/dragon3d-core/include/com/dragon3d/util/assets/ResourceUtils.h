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
 * Created:     2014/04/18
 **********************************************************************/


#ifndef ResourceUtils_Assets_Util_Dragon3d_Com_H
#define ResourceUtils_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <com/dragon3d/util/assets/Resource.h>

BeginPackage4(com, dragon3d, util, assets)

Import dragon::lang;
Import com::dragon3d::util::assets;

class_ ResourceUtils extends(Object) {
public:
    static const Type* TYPE;
    
public:
    /**
     * read resource to string
     * 
     * @param  res     [description]
     * @param  charset [description]
     * @return         [description]
     */
    static String* readResourceToString(Resource* res, const String& charset);
    
};//ResourceUtils

EndPackage4 //(com, dragon3d, util, assets)

#endif //ResourceUtils_Assets_Util_Dragon3d_Com_H
