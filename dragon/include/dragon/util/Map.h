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


#ifndef Map_Util_Dragon_H
#define Map_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/util/Iterator.h>

BeginPackage2(dragon, util)

template<class K, class V>
__interface Map {
public:
	__interface Entry {
	public:
		virtual ~Entry(){};

	public:
		virtual K getKey()=0;
		virtual V* getValue()=0;
	};

public:
	virtual ~Map(){};

public:
	virtual int size() = 0;
	virtual bool containsKey(K key) = 0;
	virtual V* get(K key) = 0;
	virtual V* put(K key, V* value) = 0;
	virtual V* remove(K key) = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual Iterator<Entry>* iterator() = 0;
};

EndPackage2//(dragon, util)

#endif//Map_Util_Dragon_H
