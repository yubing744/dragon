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

#ifndef PLATFORM_POSIX_Internal_Lang_Dragon_H
#define PLATFORM_POSIX_Internal_Lang_Dragon_H

#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;

#define INT_ARGS_COUNT 5
#define FLOATING_ARGS_COUNT 8

string query_prefix_symbol();

string query_name_end_symbol();

string parse_basic_type_symbol(const char* sname);

string query_byte_symbol();

string query_short_symbol();

string query_int_symbol();

string query_long_symbol();

string query_float_symbol();

string query_double_symbol();

string query_char_symbol();

string query_boolean_symbol();

string query_void_symbol();

#endif//PLATFORM_POSIX_Internal_Lang_Dragon_H