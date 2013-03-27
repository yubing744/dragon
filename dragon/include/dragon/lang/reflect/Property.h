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

#ifndef Lang_Reflect_Property_H 
#define Lang_Reflect_Property_H
#pragma once

#include "Field.h"
/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageReflect

class _DragonExport Property:public Field
{
public:
	Property(String name,String type,P<Method> setter,P<Method> getter);

public:
	virtual void setSetter(P<Method> setter);
	virtual void setGetter(P<Method> getter);
	virtual P<Method> getGetter();
	virtual P<Method> getSetter();

protected:
	P<Method> setter;
	P<Method> getter;
};

EndPackageReflect

#endif