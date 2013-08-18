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

#ifndef Library_Posix_Internal_Lang_Dragon_H 
#define Library_Posix_Internal_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/internal/Library.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

Import dragon::lang::internal;

//---------------------------
//---------------------------
// Resole package

typedef struct {
	char* symbol; // symbol name
	void* address; // the address of invokedescriptor
} export_symbol;


size_t next_offset(const char* symbol, size_t* out_len);

Library::NameSpace* find_package(Library::NameSpace* head, const char* symbol, int offset, size_t len);

Library::NameSpace* create_package(export_symbol * es, int offset, size_t len);

void add_to_package(Library::NameSpace* parent, export_symbol * es, int offset);

void add_to_tree(Library::ClassTree* tree, export_symbol * es, int offset);


#endif//Library_Posix_Internal_Lang_Dragon_H