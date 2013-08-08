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

#ifndef Constructor_Reflect_Lang_Dragon_H 
#define Constructor_Reflect_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Array.h>
#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/reflect/Member.h>

BeginPackage3(dragon, lang, reflect)

class _DragonExport Constructor 
	extends(Member)
{
public:
	Constructor(const Class* clazz, const char* name, 
		void* procAddress, const Array<Type*>& parameterTypes);
	virtual ~Constructor();

public:
	virtual void* newInstance();
	virtual void* newInstance(const Array<Object*>& args);

	virtual const Array<Type*> getParameterTypes();

protected:
	void* procAddress;
	Array<Type*> parameterTypes;
};


/*
template <class Type>
class TemplateConstructor 
	:public Constructor 
{
	void* invoke() {
		Type* type = new Type();
		return (void*)type;
	};
};

class AddressConstructor 
	:public Constructor
{
public:
	AddressConstructor(int size, FnConstructor constructAddress) {
		this->classSize = size;
		this->fnCreateObject = constructAddress;
	}

public:
	void* invoke() {
		void* pThis = (void*)new char[classSize];
		fnCreateObject(pThis);
		return pThis;
	}

private:
	FnConstructor fnCreateObject;
	int classSize;
};
*/

EndPackage3//(dragon, lang, reflect)

#endif//Constructor_Reflect_Lang_Dragon_H