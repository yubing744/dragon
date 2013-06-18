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

#ifndef Lang_Util_Regex_MatchResult_H
#define Lang_Util_Regex_MatchResult_H

#include <dragon/config.h>

#include <dragon/lang/String.h>

BeginPackage3(dragon, util, regex)

Import dragon::lang;

interface _DragonExport MatchResult {
public:
	MatchResult(){};
	~MatchResult(){}

public:
	virtual dg_int end() = 0;
	virtual dg_int end(dg_int group) = 0;
	virtual String* group() = 0;
	virtual dg_int groupCount() = 0;
	virtual dg_int start() = 0;
	virtual dg_int start(dg_int group) = 0;
	virtual String* group(dg_int group) = 0;

};//Arrays

EndPackage3 //(dragon, lang)

#endif //Lang_Util_Regex_MatchResult_H
