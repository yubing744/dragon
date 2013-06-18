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

#ifndef Lang_Util_Regex_Pattern_H
#define Lang_Util_Regex_Pattern_H

#include <dragon/config.h>
#include <dragon/lang/String.h>
#include <pcre.h>
 
BeginPackage3(dragon, util, regex)

Import dragon::lang;

class Matcher;

class _DragonExport Pattern {
public:
	friend class Matcher;

public:
	static Pattern* compile(String* regex);
	static Pattern* compile(String* regex, dg_int flags);
	static dg_boolean matches(String* regex, String* input);
	static void release(Pattern* p);

private:
	Pattern(String* regex, dg_int flags);

public:
	virtual ~Pattern();

public:
	virtual Matcher* matcher(String* input);

protected:
	virtual void compile();

protected:
	pcre32 *re;
	String* pattern;
	dg_boolean compiled;
	dg_int flags;
};//Pattern

EndPackage3 //(dragon, util, regex)

#endif //Lang_Util_Regex_Pattern_H
