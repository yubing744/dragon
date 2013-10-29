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


#ifndef Input_Framework_Dragon3d_Com_H
#define Input_Framework_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/reflect/Type.h>

BeginPackage3(com, dragon3d, framework)

Import dragon::lang::reflect;
Import com::dragon3d::framework;

__interface _DragonExport Input {
public:
	virtual ~Input(){};

public:
    /**
     * output the scene
     */
    virtual int queryStatus(Type* deviceType, int statusType) = 0;
	
};//Input

EndPackage3 //(com, dragon3d, framework)

#endif //Input_Framework_Dragon3d_Com_H


/*

#pragma once

#include "dg_config.h"

#ifndef DG_INPUT
#define DG_INPUT

class DGInput
{
public:
	DGInput(void);
	virtual ~DGInput(void);

public:
	virtual DGboolean getKey(char keyCode) = 0;
	virtual DGboolean getAxis(const char* axis) = 0;
};

#endif

 */
