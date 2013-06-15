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

#ifndef Lang_Util_Regex_Matcher_H
#define Lang_Util_Regex_Matcher_H

#include <dragon/config.h>
#include <dragon/lang/String.h>
#include <dragon/lang/Array.h>

#include <dragon/util/regex/MatchResult.h>

BeginPackage3(dragon, util, regex)

Import dragon::lang;
Import dragon::util::regex;

class _DragonExport Matcher 
	:public MatchResult {
public:
	friend class Pattern;
	
protected:
	Matcher(const dg_char* subject, int* ovector, int length);

public:
	virtual ~Matcher();

// Implements interface MatchResult
public:
	virtual int end();
	virtual int end(int group);
	virtual const String* group();
	virtual int groupCount();
	virtual int start();
	virtual int start(int group);

public:
	virtual dg_boolean matches();

protected:
	String* input;
	Array<dg_int>* ovector;
};//Matcher

EndPackage3 //(dragon, util, regex)

#endif //Lang_Util_Regex_Matcher_H
