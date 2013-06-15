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
#include <dragon/lang/RuntimeException.h>

Import dragon::lang;

TEST(Dragon_Lang_RuntimeExceptionTest, TryCatchTest) {
	String* msg = new String("abc");

	try {
		throw new RuntimeException(msg);
	} catch (Throwable* e) {
		String* msg = e->getMessage();
		dg_boolean isEqual = msg->equals(new String("abc"));

		EXPECT_EQ(dg_true, isEqual);

		SafeDelete(e);
	}

	SafeDelete(msg);
}


