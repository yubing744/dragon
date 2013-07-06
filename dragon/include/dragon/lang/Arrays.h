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

#ifndef Arrays_Lang_H
#define Arrays_Lang_H

#include <dragon/config.h>


BeginPackage2(dragon, lang)

template<class T>
class _DragonExport Arrays {
public:
	Arrays(){};
	~Arrays(){}

public:

	static void copyOf(const T* src, dg_int srcOffset, T* target, dg_int targetOffset, dg_int count) {
		T* p1 = const_cast<T*>(src) + srcOffset;
		T* p2 = target + targetOffset;

		dg_int len = count;
		while(len-- >0) *p2++ = *p1++;
	};

};//Arrays

EndPackage2///(dragon, lang)

#endif //Arrays_Lang_H
