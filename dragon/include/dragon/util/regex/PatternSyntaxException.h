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

#ifndef Lang_Util_Regex_PatternSyntaxException_H
#define Lang_Util_Regex_PatternSyntaxException_H

#include <dragon/config.h>
#include <dragon/lang/String.h>
#include <dragon/lang/IllegalArgumentException.h>

BeginPackage3(dragon, util, regex)

Import dragon::lang;

class _DragonExport PatternSyntaxException
	:public IllegalArgumentException {
public:
	PatternSyntaxException(String* desc, String* regex, int index);
	virtual ~PatternSyntaxException();

public:
	virtual String* getDescription();
	virtual dg_int getIndex();
	virtual String* getMessage();
	virtual String* getPattern();

protected:
	String* desc;
	String* regex;
	String* pattern;
	dg_int index;

};//PatternSyntaxException

EndPackage3 //(dragon, util, regex)

#endif //Lang_Util_Regex_PatternSyntaxException_H
