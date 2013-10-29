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


#include <dragon/util/logging/ConsoleHandler.h>

#include <stdio.h>
#include <debugapi.h>
#include <stringapiset.h>

Import dragon::util::logging;

void ConsoleHandler::publish(const char* loggerName, const char* msg) {
    char buffer[1024];
    sprintf(buffer, "%s: %s\n", loggerName, msg);

    size_t nu = strlen(buffer);
    size_t n = (size_t)MultiByteToWideChar(CP_ACP, 0, (const char *)buffer, (int)nu, NULL, 0);

    wchar_t* output = new wchar_t[n + 1];
    MultiByteToWideChar(CP_ACP, 0, (const char *)buffer, (int)nu, output, (int)(n + 1));
    output[n] = L'\0';
	OutputDebugStringW(output);

    delete[] output;
}