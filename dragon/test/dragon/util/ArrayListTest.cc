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
#include <dragon/lang/StringBuffer.h>
#include <dragon/util/ArrayList.h>

Import dragon::util;

TEST(Dragon_Util_ArrayListTest, New) {
	ArrayList<String>* o = new ArrayList<String>();
	SafeDelete(o);
}

TEST(Dragon_Util_ArrayListTest, AddItem) {
	ArrayList<String>* o = new ArrayList<String>();

	String* str = new String("Hello World!");
	o->add(str);
	SafeDelete(str);

	SafeDelete(o);
}

TEST(Dragon_Util_ArrayListTest, IteratorList) {
	ArrayList<String>* list = new ArrayList<String>();

	String* str = new String("A");
	list->add(str);

	String* str1 = new String("B");
	list->add(str1);

	String* str2 = new String("C");
	list->add(str2);

	StringBuffer* sb = new StringBuffer();

	Iterator<String>* it = list->iterator();

	while(it->hasNext()) {
		String* dd = it->next();
		sb->append(dd);
	}

	SafeDelete(it);

	String* expect = new String("ABC");
	String* out = sb->toString();
	EXPECT_EQ(true, expect->equals(out));

	SafeDelete(out);
	SafeDelete(expect);

	SafeDelete(it);
	SafeDelete(sb);

	SafeDelete(str2)
	SafeDelete(str1)
	SafeDelete(str);

	SafeDelete(list);
}