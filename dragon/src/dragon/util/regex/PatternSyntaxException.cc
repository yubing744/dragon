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

#include <dragon/util/regex/PatternSyntaxException.h>

Import dragon::lang;
Import dragon::util::regex;

PatternSyntaxException::PatternSyntaxException(String* desc, String* regex, int index) 
	:IllegalArgumentException() {
	this->desc = new String(desc);
	this->pattern = new String(regex);
	this->index = index;
}

PatternSyntaxException::~PatternSyntaxException() {
	SafeDelete(this->desc);
	SafeDelete(this->pattern);
}

String* PatternSyntaxException::getDescription() {
	return this->desc;
}

dg_int PatternSyntaxException::getIndex(){
	return this->index;
}

String* PatternSyntaxException::getMessage(){
	return new String(this->desc);
}

String* PatternSyntaxException::getPattern(){
	return this->pattern;
}
