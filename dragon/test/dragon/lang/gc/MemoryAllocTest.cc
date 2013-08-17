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
 * Created:     2013/07/13
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/lang/String.h>
#include <dragon/lang/gc/SmartPointer.h>
#include <dragon/lang/gc/MemoryAlloc.h>

Import dragon::lang;
Import dragon::lang::gc;

TEST(Dragon_Lang_Gc_MemoryAllocTest, New) {
	MemoryAlloc* o = MA::GetInstance();
}

TEST(Dragon_Lang_Gc_MemoryAllocTest, NewWithType01) {
	P<String> str = New<String>();
}

TEST(Dragon_Lang_Gc_MemoryAllocTest, NewWithType02) {
	String* str = New<String>();
}