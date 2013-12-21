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
#include <dragon/lang/internal/platform.h>

#include <dragon/lang/internal/Library.h>

#include <dragon/lang/internal/Library.cc>
#include <dragon/lang/internal/Library_mac.cc>

Import dragon::lang::internal;

TEST(Dragon_Lang_Internal_LibraryTest, New) {
	const char* local_lib_path = find_image_path_by_name("libdragon.dylib");
	ASSERT_TRUE(local_lib_path);

	Library* o = new Library(local_lib_path);
	SafeDelete(o);
}

TEST(Dragon_Lang_Internal_LibraryTest, resolve) {
	const char* local_lib_path = find_image_path_by_name("libdragon.dylib");
	ASSERT_TRUE(local_lib_path);

	Library* o = new Library(local_lib_path);
	o->resolve();
	SafeDelete(o);
}

TEST(Dragon_Lang_Internal_LibraryTest, find_image_num) {
	const char* local_lib_path = find_image_path_by_name("libdragon.dylib");
	ASSERT_TRUE(local_lib_path);

	size_t image_num = find_image_num(local_lib_path);
	EXPECT_EQ(dg_true, image_num > 0);
}

TEST(Dragon_Lang_Internal_LibraryTest, create_package) {
	const char* name ="dragon";
	export_symbol * es = NULL;

	es = (export_symbol *)malloc(sizeof(export_symbol));
	es->address = (void*)0x12345678;
	es->symbol = const_cast<char*>(name);

	Library::NameSpace* space = create_package(es, 0, 5);
	free_name_space(space);

	free(es);
}

TEST(Dragon_Lang_Internal_LibraryTest, find_symbol_export_table) {
	const char* local_lib_path = find_image_path_by_name("libdragon.dylib");
	ASSERT_TRUE(local_lib_path);
	
	size_t symbol_count = 0;
	export_symbol *table = find_symbol_export_table(local_lib_path, &symbol_count);

	for(int i=0; i<symbol_count; i++) {
		export_symbol *es = table + i;
		//printf("address: 0x%x, symbol: %s\n", es->address, es->symbol);
	}

	EXPECT_EQ(dg_true, symbol_count > 0);

	free_export_symbol_table(table);
}


