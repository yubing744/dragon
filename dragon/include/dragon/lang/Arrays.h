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

#include "basic_type.h"

BeginPackage2(dragon, lang)

template<class T>
class _DragonExport Arrays {
public:
	Arrays(){};
	~Arrays(){}

public:
	static T* copyOf(const T* src, int length) {
		return Arrays::copyOf(src, length, 0, length);
	};

	static T* copyOf(const T* src, int length, int offset, int count){
		if ((length < 0 || offset <0 || count<0) 
			|| (offset + count > length)) {
			//TODO throw new IndexOutOfBoundsException("the offset or count is out of rang.");
		}

		T* result = new T[count + 1];

		for (int i=offset; i<count; i+=1){
			result[i - offset] = src[i];
		}

		result[count] = (T)NULL;

		return result;
	};

};//Arrays

EndPackage2///(dragon, lang)

#endif //Arrays_Lang_H
