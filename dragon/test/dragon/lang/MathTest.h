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
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <dragon/lang/Math.h>
Import dragon::lang;

class MathTest: public CppUnit::TestFixture {

	 CPPUNIT_TEST_SUITE(MathTest);
	 CPPUNIT_TEST(testAdd);
	 CPPUNIT_TEST(testMax);
	 CPPUNIT_TEST_SUITE_END();

public:
	MathTest() {}

	void setUp();

	void testAdd();
	void testMax();

	void tearDown();
};


