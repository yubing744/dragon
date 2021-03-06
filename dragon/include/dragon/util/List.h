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
 * Created:     2013/09/21
 **********************************************************************/


#ifndef List_Util_Dragon_H
#define List_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Array.h>
#include <dragon/util/Collection.h>

BeginPackage2(dragon, util)

Import dragon::lang;

template<class E>
__interface List extends(Collection<E>)
{
public:
	virtual ~List(){};

public: // extends Collection
	virtual Iterator<E>* iterator() = 0;

	virtual bool add(E* e) = 0;
	virtual bool remove(E* e) = 0;
	virtual int size() = 0;
	virtual bool isEmpty() = 0;
	virtual bool contains(E* e) = 0;
	virtual void clear() = 0;

public:
	virtual void add(int index, E* e) = 0;
	virtual bool addAll(Collection<E>* c) = 0;
	virtual E* get(int index) = 0;
	virtual E* set(int index, E* e) = 0;

public:
	virtual Array<E*> toArray() = 0;
	virtual void toArray(Array<E*>& a) = 0;
};

EndPackage2//(dragon, util)

#endif//List_Util_Dragon_H
