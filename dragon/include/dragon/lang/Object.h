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

#ifndef Object_Lang_Dragon_H
#define Object_Lang_Dragon_H

#include <dragon/config.h>

BeginPackage2(dragon, lang)

class String;

class _DragonExport Object {
public:
	Object();
	virtual ~Object();

public:
	virtual dg_boolean equals(const Object* obj);
	virtual dg_int hashCode();
	virtual String* toString();

protected:
	virtual void finalize();

/*
	template<class Type>
	friend class Class;

public:
	virtual Class<Object>* getClass();
protected:
	Class<Object>* clazz;
*/
};

EndPackage2//(dragon, lang)

#endif//Object_Lang_Dragon_H

