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
 * Created:     2013/07/01
 **********************************************************************/


#include <gtest/gtest.h>

#include <dragon.h>
#include <dragon/lang/String.h>
#include <dragon/lang/gc/Reference.h>

Import dragon::lang;
Import dragon::lang::gc;

TEST(Dragon_Lang_Gc_SmartPointerTest, New) {
	Ref<String> p = new String("abc");
}

TEST(Dragon_Lang_Gc_SmartPointerTest, New2) {
	Ref<String> p = new String("abc");
	Ref<String> p2 = p;
}

TEST(Dragon_Lang_Gc_SmartPointerTest, New3) {
	Ref<String> p = new String("abc");
    Ref<String> p2 = new String("bcd");
    p = p2;
}
