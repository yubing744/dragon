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

#include <dragon.h>
#include <dragon/lang/IllegalArgumentException.h>

Import dragon::lang;

TEST(Dragon_Lang_IllegalArgumentExceptionTest, TryCatchTest) {
	String* msg = new String("abc");

	try {
		throw new IllegalArgumentException(msg);
	} catch (Throwable* e) {
		String* msg = e->getMessage();
		String* testMsg = new String("abc");
		dg_boolean isEqual = msg->equals(testMsg);

		EXPECT_EQ(dg_true, isEqual);

		SafeDelete(msg);
		SafeDelete(testMsg);
		SafeDelete(e);
	} catch (...) {
		FAIL();
	}

	SafeDelete(msg);
}


