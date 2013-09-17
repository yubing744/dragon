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

#define LOGGER_INFO 0
#define LOGGER_DEBUG 1
#define LOGGER_ERROR 2

BeginPackage3(dragon, util, logging)

Import dragon::util::logging;

class _DragonExport Logger {
public:
    Logger(const char* tagName, int level);
    virtual ~Logger(void);

public:
    virtual void info(const char *formatStr, ...);
    virtual void debug(const char *formatStr, ...);
    virtual void error(const char *formatStr, ...);

public:
    virtual bool isEnableInfo();
    virtual bool isEnableDebug();
    virtual bool isEnableError();

private:
    char* tagName;
    int level;
	
};//Logger

EndPackage3 //(dragon, util, logging)

#endif //Logger_Logging_Util_Dragon_H
