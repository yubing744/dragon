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

#include <dragon.h>

#include <dragon/lang/Class.h>

#include <dragon/lang/internal/SystemClassLoader.h>
#include <dragon/lang/internal/platform.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Void.h>
 
Import dragon::lang;
Import dragon::lang::internal;

TEST(Dragon_Lang_Internal_SystemClassLoaderTest, New) {
	ClassLoader* loader = ClassLoader::getSystemClassLoader();
	
	Class* clazz = loader->loadClass("dragon::lang::internal::SymTestBean");
	ASSERT_TRUE(clazz != null);

	Object* tb = clazz->newInstance();
	ASSERT_TRUE(tb != null);

	// 1. Setter
	Array<Type*> types(1);
	types[0] = new Type("int");
	Method* setTestValMethod = clazz->getMethod("setTestVal", types);

	Array<Object*> args(1);
	args[0] = new Integer(888);
	setTestValMethod->invoke(tb, Void::TYPE, args);

	// 1. Getter
	Method* getTestValMethod = clazz->getMethod("getTestVal");

	Type* retType02 = new Type("int");
	Object* retPtr = getTestValMethod->invoke(tb, Integer::TYPE);
	ASSERT_TRUE(retPtr != null);

	Integer* ret1 = dynamic_cast<Integer*>(retPtr);

	EXPECT_EQ(888, ret1->intValue());

	SafeDelete(retType02);
	SafeDelete(types[0]);
	SafeDelete(args[0]);

	SafeDelete(retPtr);
	SafeDelete(tb);
}