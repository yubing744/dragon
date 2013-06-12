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

#include <gtest/gtest.h>
#include <dragon/lang/Throwable.h>

Import dragon::lang;

TEST(Dragon_Lang_ThrowableTest, New) {
	Throwable* t = new Throwable();
	String* msg = t->getMessage();

	String* emptyStr = new String("");
	dg_boolean isEqual = msg->equals(emptyStr);

	EXPECT_EQ(dg_true, isEqual);
}

TEST(Dragon_Lang_ThrowableTest, NotEmptyMsg) {
	String* tempStr = new String("abc");

	Throwable* t = new Throwable(tempStr);
	String* msg = t->getMessage();

	dg_boolean isEqual = msg->equals(tempStr);

	EXPECT_EQ(dg_true, isEqual);
}
