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

#ifndef BASIC_TYPE_Lang_Dragon_H
#define BASIC_TYPE_Lang_Dragon_H

#include <dragon/config.h>

#include <endian2.h>

BeginPackage2(dragon, lang)

	//basic type
	typedef bool Boolean;
	typedef unsigned char Byte;
	typedef unsigned int Char;
	typedef short Short;
	typedef int Integer;
	typedef long long Long;
	typedef float Float;
	typedef double Double;

	typedef unsigned long Void;
    
    inline void SwapChar(const Char* pch) {
    	__uint32_t *n = (__uint32_t*)(pch);

  		if (is_big_endian()) {
			*n = bswap32(*n);
		} 	
    }

	inline Char ToChar(char ch){
		Char uch;
		char* pdata = (char*)(&uch);

		pdata[0] = '\0';
		pdata[1] = '\0';
		pdata[2] = '\0';
		pdata[3] = ch;

		SwapChar(&uch);

		return uch;	
	}

	#define NULL_CHAR (Char)NULL;

EndPackage2//(dragon, lang)

#endif//BASIC_TYPE_Lang_Dragon_H
