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
 * Created:     2013/07/25
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/lang/Class.h>
#include <dragon/lang/internal/SystemClassLoader.h>
#include <dragon/lang/internal/platform.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/Integer.h>


Import dragon::lang;
Import dragon::lang::internal;

TEST(Dragon_Lang_Internal_SystemClassLoaderTest, New) {
	ClassLoader* loader = ClassLoader::getSystemClassLoader();
	Class* clazz = loader->loadClass("dragon::lang::internal::SymTestBean");
	ASSERT_TRUE(clazz != NULL);

	void* tb = clazz->newInstance();

	Array<Type*> types(1);
	types[0] = new Type("int");

	Method* setTestValMethod = clazz->getMethod("setTestVal", types);

	int arg1 = 888;
	Array<void*> args(1);
	args[0] = cast_void<int>(arg1);

	setTestValMethod->invoke(tb, args);

	Method* getTestValMethod = clazz->getMethod("getTestVal");
	void* retPtr = getTestValMethod->invoke(tb);
	//dg_int ret1 = *((dg_int*)retPtr);

	//EXPECT_EQ(888, ret1);
}

TEST(Dragon_Lang_Internal_SystemClassLoaderTest, New2) {
	ClassLoader* loader = ClassLoader::getSystemClassLoader();
	Class* clazz = loader->loadClass("dragon::lang::internal::SymTestBean");
	ASSERT_TRUE(clazz != NULL);

	Object* tb = (Object*)clazz->newInstance();

	Array<Type*> types(1);
	types[0] = new Type("int");

	Method* setTestValMethod = clazz->getMethod("setTestVal", types);

	Array<Object*> args(1);
	args[0] = new Integer(888);

	setTestValMethod->invoke(tb, args);

	Method* getTestValMethod = clazz->getMethod("getTestVal");
	void* retPtr = getTestValMethod->invoke(tb);
	//dg_int ret1 = *((dg_int*)retPtr);

	//EXPECT_EQ(888, ret1);
}
