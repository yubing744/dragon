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
 * Created:     2013/09/19
 **********************************************************************/


#include <dragon/util/logging/LogManager.h>
#include <dragon/util/logging/ConsoleHandler.h>

Import dragon::util::logging;

LogManager* LogManager::LM = null;

LogManager* LogManager::getInstance() {
	if (LM == null) {
		LM = new LogManager();
		atexit(LogManager::clearAll);
	}

	return LM;
}

void LogManager::clearAll() {
	SafeDelete(LM);
}

// ----------------------------------------------
// 
LogManager::LogManager() :
	globalLogLevel(DEFAULT_LOG_LEVEL){
	init();
}

LogManager::~LogManager() {
 	LoggerMap& logMap = this->loggerMap;

	for(MapIterator it = logMap.begin(); it!=logMap.end(); ++it) { 
		Logger* logger = it->second;
		SafeDelete(logger);
	}

	logMap.clear();
}

void LogManager::init() {
	defaultHandlers.push_back(new ConsoleHandler());
}

Logger* LogManager::getLogger(const char* name) {
	MapIterator it = loggerMap.find(name);

	if(it != loggerMap.end()) {
		return it->second;
	}

	return null;
}

bool LogManager::addLogger(Logger* logger) {
	if (logger != null) {
		loggerMap[logger->getName()] = logger;
		return true;
	}

	return false;
}

int LogManager::getLogLevel(const char* name) {
	return this->globalLogLevel;
}

Array<Handler*> LogManager::getHandlers(const char* name) {
	Array<Handler*> outs(defaultHandlers.size());

	for (int i=0; i<defaultHandlers.size(); i++) {
		outs[i] = defaultHandlers[i];
	}

	return outs;
}