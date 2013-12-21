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
#include <dragon/lang/StringBuffer.h>

#include <dragon/util/regex/MatchResult.h>
#include <dragon/util/regex/Pattern.h>

BeginPackage3(dragon, util, regex)

Import dragon::lang;
Import dragon::util::regex;

class _DragonExport Matcher 
	implements(MatchResult) {
public:
	friend class Pattern;
	
protected:
	Matcher(Pattern* p, const CharSequence* text);
	Matcher(Pattern* p, const String* text);

public:
	virtual ~Matcher();

// Implements interface MatchResult
public:
	virtual int end();
	virtual int end(int group);
	virtual String* group();
	virtual int groupCount();
	virtual int start();
	virtual int start(int group);
	virtual String* group(int group);

public:
	virtual bool matches();
	virtual bool find();
	virtual bool find(int start);
	virtual Matcher* appendReplacement(StringBuffer* sb, String* replacement);
	virtual StringBuffer* appendTail(StringBuffer* sb);
	virtual String* replaceAll(String* replacement);

protected:
	virtual void reset();
	virtual bool search(int from);
	virtual int getTextLength();
	virtual CharSequence* getSubSequence(int beginIndex, int endIndex);
	virtual wchar_u charAt(int i);

protected:
	Pattern* parentPattern;
	CharSequence* text;

	int* groups;
	int groupSize;

	int first;
	int last;

	int lastAppendPosition;
};//Matcher

EndPackage3 //(dragon, util, regex)

#endif //Lang_Util_Regex_Matcher_H
