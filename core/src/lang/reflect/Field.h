/*
* Copyright 2006 the original author or authors.
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

#include "reflect.h"

#ifndef Lang_Reflect_Field_H 
#define Lang_Reflect_Field_H
#pragma once

/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageReflect

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

EndPackageReflect

#endif