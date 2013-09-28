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


#ifndef Iterable_Util_Dragon_H
#define Iterable_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/util/Iterator.h>

BeginPackage2(dragon,util)

template<class E>
interface Iterable
{
public:
	virtual ~Iterable(){};

public:
	virtual Iterator<E>* iterator() = 0;
};

EndPackage2//(dragon,util)

#endif//Iterable_Util_Dragon_H
