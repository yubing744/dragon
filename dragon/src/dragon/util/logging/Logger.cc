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

#include <dragon/lang/Class.h>
#include <dragon/lang/String.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/util/logging/LogManager.h>

Import dragon::lang;
Import dragon::util::logging;

const Type* Logger::TYPE = TypeOf<Logger>();

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
	return Logger::getLogger(name, INFO);
}

Logger* Logger::getLogger(const Type* type, int level) {
	return Logger::getLogger(type->getName());
}

Logger* Logger::getLogger(const Type* type) {
	return Logger::getLogger(type->getName(), INFO);
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

	    this->logV(level, formatStr, params);
	    
	    va_end(params);
	}
}

void Logger::logV(int level, const char *formatStr, va_list arg) {
	if (this->isEnabled(level)) {
		String* msg = String::vformat(formatStr, arg);
		char* utf8Str = msg->toUTF8String();

	    for (Iterator it = handlers.begin(); it!=handlers.end(); ++it) {
    		Handler* handler = *it;
    		handler->publish(this->name, utf8Str);
    	}

    	SafeFree(utf8Str);
    	SafeRelease(msg);
    }
}

void Logger::logThrowable(int level, const String& msg, Throwable* throwable) {
	if (this->isEnabled(level)) {
		String* tMsg = throwable->getMessage();
		char* cMsg = tMsg->toUTF8String();

		const Class* clazz = throwable->getClass();
		char* utf8Msg = msg.toUTF8String();

		String* fmtedMsg = String::format("%s %s \n    casue: %s", clazz->getName(), utf8Msg, cMsg);
		char* utf8Str = fmtedMsg->toUTF8String();

	    for (Iterator it = handlers.begin(); it!=handlers.end(); ++it) {
    		Handler* handler = *it;
    		handler->publish(this->name, utf8Str);
    	}

    	SafeFree(utf8Str);
    	SafeFree(utf8Msg);
    	SafeFree(cMsg);

    	SafeRelease(fmtedMsg);
    	SafeRelease(tMsg);
    }
}

void Logger::trace(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->logV(LOG_LEVEL_TRACE, formatStr, params);

	va_end(params);
}

void Logger::debug(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->logV(LOG_LEVEL_DEBUG, formatStr, params);
	
	va_end(params);
}

void Logger::info(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->logV(LOG_LEVEL_INFO, formatStr, params);
	
	va_end(params);
}

void Logger::warn(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->logV(LOG_LEVEL_WARN, formatStr, params);
	
	va_end(params);
}

void Logger::error(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->logV(LOG_LEVEL_ERROR, formatStr, params);
	
	va_end(params);
}

void Logger::fatal(const char *formatStr, ...) {
	va_list params;
	va_start(params, formatStr);

	this->logV(LOG_LEVEL_FATAL, formatStr, params);
	
	va_end(params);
}


void Logger::traceT(const String& msg, Throwable* throwable) {
	this->logThrowable(LOG_LEVEL_TRACE, msg, throwable);
}

void Logger::debugT(const String& msg, Throwable* throwable) {
	this->logThrowable(LOG_LEVEL_DEBUG, msg, throwable);
}

void Logger::infoT(const String& msg, Throwable* throwable) {
	this->logThrowable(LOG_LEVEL_INFO, msg, throwable);
}

void Logger::warnT(const String& msg, Throwable* throwable) {
	this->logThrowable(LOG_LEVEL_WARN, msg, throwable);
}

void Logger::errorT(const String& msg, Throwable* throwable) {
	this->logThrowable(LOG_LEVEL_ERROR, msg, throwable);
}

void Logger::fatalT(const String& msg, Throwable* throwable) {
	this->logThrowable(LOG_LEVEL_FATAL, msg, throwable);
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