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
#include <dragon/util/regex/Pattern.h>

BeginPackage3(dragon, util, regex)

Import dragon::lang;
Import dragon::util::regex;

class _DragonExport Matcher 
	:public MatchResult {
public:
	friend class Pattern;
	
protected:
	Matcher(Pattern* p, String* text);

public:
	virtual ~Matcher();

// Implements interface MatchResult
public:
	virtual dg_int end();
	virtual dg_int end(dg_int group);
	virtual String* group();
	virtual dg_int groupCount();
	virtual dg_int start();
	virtual dg_int start(dg_int group);
	virtual String* group(dg_int group);

public:
	virtual dg_boolean matches();
	virtual dg_boolean find();
	virtual dg_boolean find(dg_int start);

protected:
	virtual void reset();

protected:
	Pattern* parentPattern;
	String* text;

	dg_int* groups;
	dg_int groupSize;

	dg_int first;
	dg_int last;
};//Matcher

EndPackage3 //(dragon, util, regex)

#endif //Lang_Util_Regex_Matcher_H
