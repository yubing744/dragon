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

#ifndef Reflect_Lang_Dragon_H
#define Reflect_Lang_Dragon_H


#include <dragon/config.h>

BeginPackage3(dragon, lang, dragon)

	interface Constructor;

	class Method;
	class Field;
	class Property;
	class Library;
	class LibraryManager;

EndPackage3 //(dragon, lang, dragon)


#include "Method.h"
#include "Field.h"
#include "Property.h"
#include "Constructor.h"
#include "Library.h"
#include "DllLibrary.h"
#include "LibraryManager.h"


#define ImplRuntimeGetClass(Type) Class<Object>* getClass(){return (Class<Object>*)new Class<Type>();}
#define ImplGetClassSize(Type)  int getClassSize(){return sizeof(Type);}


#endif // Reflect_Lang_Dragon_H