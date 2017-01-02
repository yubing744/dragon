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
 * Created:     2014/05/13
 **********************************************************************/


#ifndef BspSceneActivtor_Plugin_Dragon3d_Com_H
#define BspSceneActivtor_Plugin_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage3(com, dragon3d, plugin)

Import dragon::lang;

class_ BspSceneActivtor extends(Object) {
public:
    static const Type* TYPE;
    
public:
    BspSceneActivtor();
    virtual ~BspSceneActivtor();

public:
    
protected:
    
};//BspSceneActivtor

EndPackage3 //(com, dragon3d, plugin)

#endif //BspSceneActivtor_Plugin_Dragon3d_Com_H