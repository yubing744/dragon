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


#ifndef LogManager_Logging_Util_Dragon_H
#define LogManager_Logging_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Array.h>

#include <dragon/util/logging/Logger.h>
#include <dragon/util/logging/Handler.h>

#include <map>
#include <vector>

#ifdef ENABLE_LOG_LEVEL
 	#define DEFAULT_LOG_LEVEL ENABLE_LOG_LEVEL
#else
	#define DEFAULT_LOG_LEVEL 3 // info
#endif

BeginPackage3(dragon, util, logging)

Import std;
Import dragon::lang;
Import dragon::util::logging;

class _DragonExport LogManager {
private:
    static LogManager* LM;

public:
	static LogManager* getInstance();
	static void clearAll();
	
// ------------------------------------------
public:
    typedef map<string, Logger*> LoggerMap;
    typedef LoggerMap::iterator MapIterator;

    typedef vector<Handler*> HandlerList;
    typedef HandlerList::iterator ListIterator;

private:
	LogManager();
	virtual ~LogManager();

public:
	Logger* getLogger(const char* name);
	int getLogLevel(const char* name);
	Array<Handler*> getHandlers(const char* name);

	bool addLogger(Logger* logger);

private:
	void init();

protected:
	LoggerMap loggerMap;
	HandlerList defaultHandlers;

	int globalLogLevel;

};//LogManager

EndPackage3 //(dragon, util, logging)

#endif //LogManager_Logging_Util_Dragon_H
