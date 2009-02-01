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

#ifndef Util_Dragon_H
#define Util_Dragon_H

#include <dragon/config.h>

BeginPackage2(dragon, util)

	template<class E>
	interface Iterable;

	template<class E>
	interface Iterator;

	template<class E>
	interface Collection;

	template<class K,class V>
	interface Map;

	template<class K,class V>
	class HashMap;

	template<class E>
	interface List;

	template<class E>
	class ArrayList;

	template<class E>
	class LinkedList;

	template<class E>
	class Stack;

	template<class E>
	class Queue;

	template<class E>
	class PriorityQueue;
	

	template<class E>
	interface Set;

	template<class E>
	class HashSet;

	class TemplateType;
	class Properties;

EndPackage2

#include <dragon/lang/lang.h>

Import dragon::lang;

#include "Iterable.h"
#include "Iterator.h"

#include "Collection.h"

#include "Map.h"
#include "HashMap.h"

#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

#include "Set.h"
#include "HashSet.h"

#include "TemplateType.h"
#include "Properties.h"

#endif//Util_Dragon_H