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
 * Created:     2013/03/31
 **********************************************************************/

#include "dragon.h"

#ifndef Lang_dragon_Field_H 
#define Lang_dragon_Field_H
#pragma once

BeginPackage3(dragon, lang, reflect)

class _DragonExport Field:public Object
{
public:
	Field(String name,String type);
	virtual ~Field(){};
public:
	virtual void setName(String name);
	virtual String getName();

	virtual void setType(String type);
	virtual String getType();

protected:
	String name;
	String type;
};

EndPackage3//(dragon, lang, reflect)

#endif