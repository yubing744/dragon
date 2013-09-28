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
 * Created:     2013/09/17
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/lang/System.h>

Import dragon::lang;

TEST(Dragon_Lang_SystemTest, TestCurrentTimeMillis) {
	dg_long startTime = System::currentTimeMillis();
	EXPECT_EQ(true, startTime > 0);

	dg_long endTime = System::currentTimeMillis();
	EXPECT_EQ(true, endTime > 0);
}


TEST(Dragon_Lang_SystemTest, TestNanoMillis) {
	dg_long startTime = System::nanoTime();
	EXPECT_EQ(true, startTime > 0);

	dg_long endTime = System::nanoTime();
	EXPECT_EQ(true, endTime > 0);
}