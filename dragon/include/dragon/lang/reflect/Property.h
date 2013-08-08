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

#ifndef Property_Lang_Dragon_H 
#define Property_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/reflect/Field.h>

BeginPackage3(dragon, lang, reflect)

class _DragonExport Property extends(Field)
{
public:
	Property(const Class* clazz, const char* name, const Class* type);
	virtual ~Property();

public:
	virtual const Method* getGetter();
	virtual const Method* getSetter();

protected:
	Method* setter;
	Method* getter;
};

EndPackage3//(dragon, lang, reflect)

#endif//Property_Lang_Dragon_H