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
	static Pattern* compile(const String& regex);
	static Pattern* compile(const String* regex);
	static Pattern* compile(const String* regex, int flags);

	static bool matches(String* regex, String* input);
	static void release(Pattern* p);

private:
	Pattern(const String* regex, int flags);

public:
	virtual ~Pattern();

public:
	/**
	 * Creates a matcher that will match the given input against this pattern.
	 * 
	 * @param  input [description]
	 * @return       [description]
	 */
	virtual Matcher* matcher(const CharSequence* input);

	/**
	 * Splits the given input sequence around matches of this pattern.
	 */
	virtual Array<String*> split(const CharSequence* input, int limit);

	virtual Array<String*> split(const CharSequence* input);

protected:

	/**
	 * Compiles the given regular expression into a pattern. 
	 */
	virtual void compile();

protected:
	pcre32 *re;
	String* pattern;
	bool compiled;
	int flags;
};//Pattern

EndPackage3 //(dragon, util, regex)

#endif //Lang_Util_Regex_Pattern_H
