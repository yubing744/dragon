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
 * Created:     2014/05/14
 **********************************************************************/


#ifndef PickResults_Intersection_Util_Dragon3d_Com_H
#define PickResults_Intersection_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/util/List.h>
#include <com/dragon3d/util/intersection/RaycastHit.h>

BeginPackage4(com, dragon3d, util, intersection)

Import dragon::lang;
Import dragon::util;

class_ PickResults extends(Object) {
public:
    static const Type* TYPE;
    
public:
    PickResults();
    virtual ~PickResults();

public:
    /**
     * add a hit data
     * 
     * @param pickData [description]
     */
    virtual void addHit(RaycastHit* hit);

protected:
    List<RaycastHit>* hits; 
};//PickResults

EndPackage4 //(com, dragon3d, util, intersection)

#endif //PickResults_Intersection_Util_Dragon3d_Com_H
