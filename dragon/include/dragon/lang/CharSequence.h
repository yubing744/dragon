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

#ifndef CharSequence_Lang_H
#define CharSequence_Lang_H

#include <dragon/config.h>

BeginPackage2(dragon, lang)

class String;

interface _DragonExport CharSequence
{
public:
	virtual ~CharSequence(){};

public:
	virtual dg_int length() const = 0;
	virtual dg_char charAt(dg_int index) = 0;
	virtual CharSequence* subSequence(dg_int start, dg_int end) = 0;
	virtual String* toString() = 0;

};

EndPackage2//(dragon, lang)

#endif//CharSequence_Lang_H
