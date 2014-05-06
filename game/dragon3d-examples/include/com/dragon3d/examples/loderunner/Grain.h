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
 * Created:     2014/05/05
 **********************************************************************/


#ifndef Grain_Loderunner_Examples_Dragon3d_Com_H
#define Grain_Loderunner_Examples_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage4(com, dragon3d, examples, loderunner)

Import dragon::lang;

class_ Grain extends(Object) {
public:
    static const Type* TYPE;
    
public:
    Grain();
    virtual ~Grain();

public:
    
protected:
    
};//Grain

EndPackage4 //(com, dragon3d, examples, loderunner)

#endif //Grain_Loderunner_Examples_Dragon3d_Com_H
