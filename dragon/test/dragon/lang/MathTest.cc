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

//#include "MathTest.h"

/*
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MathTest, "alltest");

void MathTest::setUp(){

}

void MathTest::tearDown(){

}

void MathTest::testAdd(){
     int result = 5;
     CPPUNIT_ASSERT( result == 5 );
}

void MathTest::testMax(){
	int result = Math::max(10, 12);
    CPPUNIT_ASSERT( result == 12 );
}
*/

#include <gtest/gtest.h>

#include <dragon.h>
#include <dragon/lang/Math.h>

Import dragon::lang;

TEST(Dragon_Lang_Math_Test, Max) {
    EXPECT_EQ(10, Math::max(10, 5));   
    EXPECT_EQ(0, Math::max(-1, 0));
    EXPECT_EQ(100, Math::max(0, 100));
}

TEST(Dragon_Lang_Math_Test, Min){
    EXPECT_EQ(-1, Math::min(-1, 0));
}

