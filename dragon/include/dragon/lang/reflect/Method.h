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

#ifndef Method_Lang_Dragon_H
#define Method_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Array.h>
#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/reflect/Member.h>

BeginPackage2(dragon, lang)
	class Class;
	class Object;
EndPackage2//(dragon, lang)

BeginPackage3(dragon, lang, reflect)

Import dragon::lang;

class _DragonExport Method 
	extends(Member)
{
public:
	Method(const Class* clazz, const char* name, 
		void* procAddress, const Type* returnType, const Array<Type*>& parameterTypes);
	virtual ~Method(){};
	
public:
	virtual const Array<Type*> getParameterTypes();
	virtual const Type* getReturnType();

	virtual void* invoke(void* pThis);
	virtual void* invoke(void* pThis, const Array<void*>& args);

	virtual Object* invoke(Object* obj, const Array<Object*>& args);

protected:
	void* procAddress;
	const Type* returnType;
	const Array<Type*> parameterTypes;
};

EndPackage3//(dragon, lang, reflect)

#endif //Method_Lang_Dragon_H