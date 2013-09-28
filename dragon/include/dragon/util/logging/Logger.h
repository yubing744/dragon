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


#ifndef Logger_Logging_Util_Dragon_H
#define Logger_Logging_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/util/logging/Handler.h>

#include <vector>

BeginPackage3(dragon, util, logging)

Import std;
Import dragon::util::logging;

#define LOG_LEVEL_TRACE    1
#define LOG_LEVEL_DEBUG    2
#define LOG_LEVEL_INFO     3
#define LOG_LEVEL_WARN     4 
#define LOG_LEVEL_ERROR    5
#define LOG_LEVEL_FATAL    6

#define TRACE       LOG_LEVEL_TRACE
#define DEBUG       LOG_LEVEL_DEBUG
#define INFO        LOG_LEVEL_INFO
#define WARN        LOG_LEVEL_WARN
#define ERROR       LOG_LEVEL_ERROR
#define FATAL       LOG_LEVEL_FATAL

class _DragonExport Logger {
public:
    static Logger* getLogger(const char* name);
    static Logger* getLogger(const char* name, int level);

public:
    typedef vector<Handler*> HandlerList;
    typedef HandlerList::iterator Iterator;

public:
    Logger(const char* name, int level);
    virtual ~Logger(void);

public:   
    // check if enabled
    virtual bool isTraceEnabled();
    virtual bool isDebugEnabled();
    virtual bool isInfoEnabled();
    virtual bool isWarnEnabled();
    virtual bool isErrorEnabled();
    virtual bool isFatalEnabled();

    // format msg
    virtual void trace(const char *formatStr, ...);
    virtual void debug(const char *formatStr, ...);
    virtual void info(const char *formatStr, ...);
    virtual void warn(const char *formatStr, ...);
    virtual void error(const char *formatStr, ...);
    virtual void fatal(const char *formatStr, ...);

public:
    virtual bool isEnabled(int lovel);
    virtual void log(int level, const char *formatStr, ...);
    virtual void log_v(int level, const char *formatStr, va_list arg);

    virtual const char* getName();
    virtual int getLevel();
    virtual void setLevel(int level);
    
    virtual void addHandler(Handler* handler);

private:
    HandlerList handlers;

    char* name;
    int level;

};//Logger

EndPackage3 //(dragon, util, logging)

#endif //Logger_Logging_Util_Dragon_H
