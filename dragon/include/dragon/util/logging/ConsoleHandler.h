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


#ifndef ConsoleHandler_Logging_Util_Dragon_H
#define ConsoleHandler_Logging_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/util/logging/Handler.h>

BeginPackage3(dragon, util, logging)

Import dragon::util::logging;

/**
 * console log handler.
 */
class _DragonExport ConsoleHandler 
	implements(Handler) {
public:
	ConsoleHandler();
	virtual ~ConsoleHandler();

public:
	virtual void publish(const char* loggerName, const char* msg);
	
};//ConsoleHandler

EndPackage3 //(dragon, util, logging)

#endif //ConsoleHandler_Logging_Util_Dragon_H
