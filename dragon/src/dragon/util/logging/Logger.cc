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
 * Created:     2013/09/17
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdarg.h>
#include <ctype.h>
 
#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;

Logger::Logger(const char* tagName, int logLevel) 
	: level(logLevel) {
	char* buf = new char[strlen(tagName) + 1];
	strcpy(buf, tagName);
	this->tagName = buf;
}

Logger::~Logger() {
	SafeDeleteArray(this->tagName);
}

bool Logger::isEnableInfo() {
	return this->level >= LOGGER_INFO;
}

bool Logger::isEnableDebug() {
	return this->level >= LOGGER_DEBUG;
}

bool Logger::isEnableError() {
	return this->level >= LOGGER_ERROR;
}

void Logger::info(const char *formatStr, ...) {
	if (this->isEnableInfo()) {
	    va_list params;
	    char buf[BUFSIZ];

	    va_start(params, formatStr);
	    vsprintf(buf, formatStr, params);
	    printf("%s: %s\r\n", this->tagName, buf);
	    va_end(params);
	}
}

void Logger::debug(const char *formatStr, ...){
	if (this->isEnableDebug()) {
	    va_list params;
	    char buf[BUFSIZ];

	    va_start(params, formatStr);
	    vsprintf(buf, formatStr, params);
	    printf("%s: %s\r\n", this->tagName, buf);
	    va_end(params);
	}
}

void Logger::error(const char *formatStr, ...){
	if (this->isEnableError()) {
	    va_list params;
	    char buf[BUFSIZ];

	    va_start(params, formatStr);
	    vsprintf(buf, formatStr, params);
	    printf("%s: %s\r\n", this->tagName, buf);
	    va_end(params);
	}
}