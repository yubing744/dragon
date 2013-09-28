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
 * Created:     2013/09/15
 **********************************************************************/


#ifndef HelloWorld_Dragon3D_H
#define HelloWorld_Dragon3D_H

#include <dragon3d.h>
#include <com/dragon3d/Application.h>

BeginPackage4(com, dragon3d, examples, helloworld)

Import com::dragon3d::framework;

class _DragonExport HelloWorld extends(Application) {
public:
	HelloWorld();
	virtual ~HelloWorld();

public:
	
protected:
	
};//HelloWorld

EndPackage4 //(com, dragon3d, examples, helloworld)

#endif //HelloWorld_Dragon3D_H
