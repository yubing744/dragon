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
 * Created:     2013/08/03
 **********************************************************************/


#include <gtest/gtest.h>
 #include <dragon/lang/internal/platform.h>
#include <dragon/lang/internal/LibraryClassLoader.h>

Import dragon::lang::internal;

TEST(Dragon_Lang_Internal_LibraryClassLoaderTest, New) {
	LibraryClassLoader* o = new LibraryClassLoader();
	const char* localLib = GetLocalLibPath();
	o->load(localLib);
	SafeDelete(o);
}

TEST(Dragon_Lang_Internal_LibraryClassLoaderTest, defineClass) {
	LibraryClassLoader* o = new LibraryClassLoader();
	const char* localLib = GetLocalLibPath();
	o->load(localLib);
	Class* clazz = o->loadClass("dragon::lang::String");
	dg_boolean equ = (clazz != null);
	EXPECT_EQ(dg_true, equ);
	SafeDelete(o);
}
