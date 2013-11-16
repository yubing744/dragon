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


#include <gtest/gtest.h>

#include <dragon/lang/String.h>
#include <dragon/util/HashMap.h>

#include <string>

Import std;
Import dragon::lang;
Import dragon::util;

TEST(Dragon_Util_HashMapTest, New) {
	HashMap<string, Object>* myMap = new HashMap<string, Object>();
	SafeDelete(myMap);
}

TEST(Dragon_Util_HashMapTest, AddItem) {
	HashMap<string, Object>* myMap = new HashMap<string, Object>();

	Object* obj1 = new Object();
	myMap->put("abc", obj1);

	SafeDelete(obj1);;
	SafeDelete(myMap);
}

TEST(Dragon_Util_HashMapTest, IteratorMap) {
	HashMap<string, Object>* myMap = new HashMap<string, Object>();

	Object* obj1 = new Object();
	myMap->put("abc1", obj1);

	Object* obj2 = new Object();
	myMap->put("abc2", obj2);

	Object* obj3 = new Object();
	myMap->put("abc3", obj3);

	Object* obj4 = new Object();
	myMap->put("abc4", obj4);

	EXPECT_EQ(4, myMap->size());

	Iterator<Map<string, Object>::Entry>* it = myMap->iterator();

	while(it->hasNext()) {
		Map<string, Object>::Entry* entry = it->next();

		Object* obj = entry->getValue();
		SafeDelete(obj);

		SafeDelete(entry);
	}

	SafeDelete(it);
	SafeDelete(myMap);
}

TEST(Dragon_Util_HashMapTest, IteratorStringMap) {
	HashMap<String, Object>* myMap = new HashMap<String, Object>();

	Object* obj1 = new Object();
	myMap->put("abc1", obj1);

	Object* obj2 = new Object();
	myMap->put("abc2", obj2);

	Object* obj3 = new Object();
	myMap->put("abc3", obj3);

	Object* obj4 = new Object();
	myMap->put("abc4", obj4);

	EXPECT_EQ(4, myMap->size());

	Iterator<Map<String, Object>::Entry>* it = myMap->iterator();

	while(it->hasNext()) {
		Map<String, Object>::Entry* entry = it->next();

		Object* obj = entry->getValue();
		SafeDelete(obj);

		SafeDelete(entry);
	}

	SafeDelete(it);
	SafeDelete(myMap);
}