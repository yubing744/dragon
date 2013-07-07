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

#ifndef Regex_Util_Lang_Dragon_H
#define Regex_Util_Lang_Dragon_H

#include <dragon/config.h>

BeginPackage3(dragon, util, regex)
	class PatternSyntaxException;
	class MatchResult;
	class Pattern;
	class Matcher;
EndPackage3//(dragon, util, regex)

#include <dragon/util/regex/PatternSyntaxException.h>
#include <dragon/util/regex/MatchResult.h>
#include <dragon/util/regex/Pattern.h>
#include <dragon/util/regex/Matcher.h>

#endif //Regex_Util_Lang_Dragon_H
