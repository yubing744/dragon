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


#include <dragon/lang/reflect/Member.h>
#include <stdlib.h>
#include <string.h>

Import dragon::lang::reflect;

Member::Member(const Class* clazz, const char* name) 
	: clazz(clazz){
	char* buf = (char*)malloc(strlen(name) + 1);
	strcpy(buf, name);
	this->name = buf;
}

Member::~Member() {
	free(this->name);
	this->name = null;
}

const Class* Member::getDeclaringClass() {
	return this->clazz;
}

const char* Member::getName() {
	return this->name;
}