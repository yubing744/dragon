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
 * Created:     2013/07/07
 **********************************************************************/


#include <gtest/gtest.h>

#include <dragon.h>
#include <dragon/lang/String.h>
#include <dragon/lang/gc/SmartArrayPointer.h>

Import dragon::lang;
Import dragon::lang::gc;

TEST(Dragon_Lang_Gc_SmartArrayPointerTest, New) {
	PArray<dg_char> p = new dg_char[13];
}

TEST(Dragon_Lang_Gc_SmartArrayPointerTest, New2) {
	PArray<dg_char> p = new dg_char[13];
	PArray<dg_char> p2 = p;
}

TEST(Dragon_Lang_Gc_SmartArrayPointerTest, New3) {
	PArray<dg_char> p = new dg_char[13];
	PArray<dg_char> p2 = p;
	p = new dg_char[4];
}

TEST(Dragon_Lang_Gc_SmartArrayPointerTest, NewStringArray01) {
	PArray<String> p = new String[13];
	PArray<String> p2 = p;
	p = new String[4];
}

TEST(Dragon_Lang_Gc_SmartArrayPointerTest, NewStringPointerArray01) {
	PArray<String*> p = new String*[13];
	PArray<String*> p2 = p;
	p = new String*[4];
}

