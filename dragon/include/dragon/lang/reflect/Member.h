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
 * Created:     2013/07/25
 **********************************************************************/


#ifndef Member_Reflect_Lang_Dragon_H
#define Member_Reflect_Lang_Dragon_H

#include <dragon/config.h>

BeginPackage2(dragon, lang)
	class Class;
	class Object;
EndPackage2//(dragon, lang)

BeginPackage3(dragon, lang, reflect)

Import dragon::lang;

class _DragonExport Member {
public:
	Member(const Class* clazz, const char* name);
	virtual ~Member();

public:
	virtual const Class* getDeclaringClass();
	virtual const char* getName();

protected:
	const Class* clazz;	
	char* name;
};//Member

EndPackage3 //(dragon, lang, reflect)

#endif //Member_Reflect_Lang_Dragon_H
