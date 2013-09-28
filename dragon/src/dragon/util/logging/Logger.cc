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
#include <dragon/util/logging/LogManager.h>

Import dragon::util::logging;


Logger* Logger::getLogger(const char* name, int level) {
	LogManager* logManager = LogManager::getInstance();

	Logger* logger = logManager->getLogger(name);

	if (logger == null) {
		Array<Handler*> handlers = logManager->getHandlers(name);
		int initLevel = (level > 0) ? level : logManager->getLogLevel(name);

		logger = new Logger(name, initLevel);

		for (int i=0; i<handlers.size(); i++) {
			logger->addHandler(handlers[i]);
		}

		logManager->addLogger(logger);
	} else {
		if (level > 0) {
			logger->setLevel(level);
		}
	}

	return logger;	
}

Logger* Logger::getLogger(const char* name) {
	return Logger::getLogger(name, 0);
}

//---------------------------------------------
Logger::Logger(const char* name, int logLevel) 
	: level(logLevel) {
	char* buf = new char[strlen(name) + 1];
	strcpy(buf, name);
	this->name = buf;
}

Logger::~Logger() {
	SafeDeleteArray(this->name);
	handlers.clear();
}

void Logger::log(int level, const char *formatStr, ...) {
	if (this->isEnabled(level)) {
		va_list params;
	    va_start(params, formatStr);

	    this->log_v(level, formatStr, params);
	    
	    va_end(params);
	}
}

void Logger::log_v(int level, const char *formatStr, va_list arg) {
	if (this->isEnabled(level)) {
		char msg[BUFSIZ];
	    vsprintf(msg, formatStr, arg);

	    for (Iterator it = handlers.begin(); it!=handlers.end(); ++it) {
    		Handler* handler = *it;
    		handler->publish(this->name, msg);
    	}
    }
}

void Logger::trace(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->log_v(LOG_LEVEL_TRACE, formatStr, params);

	va_end(params);
}

void Logger::debug(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->log_v(LOG_LEVEL_DEBUG, formatStr, params);
	
	va_end(params);
}

void Logger::info(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->log_v(LOG_LEVEL_INFO, formatStr, params);
	
	va_end(params);
}

void Logger::warn(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->log_v(LOG_LEVEL_WARN, formatStr, params);
	
	va_end(params);
}

void Logger::error(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->log_v(LOG_LEVEL_ERROR, formatStr, params);
	
	va_end(params);
}

void Logger::fatal(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->log_v(LOG_LEVEL_FATAL, formatStr, params);
	
	va_end(params);
}

bool Logger::isEnabled(int level) {
	return this->level <= level;	
}

bool Logger::isTraceEnabled() {
	return this->level <= LOG_LEVEL_TRACE;
}

bool Logger::isDebugEnabled() {
	return this->level <= LOG_LEVEL_DEBUG;
}

bool Logger::isInfoEnabled() {
	return this->level <= LOG_LEVEL_INFO;
}

bool Logger::isWarnEnabled() {
	return this->level <= LOG_LEVEL_WARN;
}

bool Logger::isErrorEnabled() {
	return this->level <= LOG_LEVEL_ERROR;
}

bool Logger::isFatalEnabled() {
	return this->level <= LOG_LEVEL_FATAL;
}

const char* Logger::getName() {
	return this->name;
}

int Logger::getLevel() {
	return this->level;
}

void Logger::setLevel(int level) {
	this->level = level;
}

void Logger::addHandler(Handler* handler) {
	this->handlers.push_back(handler);
}