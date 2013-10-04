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
 * Created:     2013/09/28
 **********************************************************************/


#ifndef Output_Framework_Dragon3d_Com_H
#define Output_Framework_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/framework/Scene.h>
#include <dragon/util/concurrent/CountDownLatch.h>

Import dragon::util::concurrent;

BeginPackage3(com, dragon3d, framework)

Import com::dragon3d::framework;

interface _DragonExport Output {
public:
	virtual ~Output(){};

public:
	/**
	 * init the output
	 */
	virtual void init() = 0;

	/**
	 * output the scene
	 */
	virtual void output(Scene* scene, CountDownLatch* latch) = 0;

	/**
	 * destroy the output
	 */
	virtual void destroy() = 0;	
	
};//Output

EndPackage3 //(com, dragon3d, framework)

#endif //Output_Framework_Dragon3d_Com_H
