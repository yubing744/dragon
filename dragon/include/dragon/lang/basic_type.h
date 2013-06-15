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

BeginPackage2(dragon, lang)

	//match java type
	typedef dg_boolean Boolean;
	typedef dg_byte Byte;
	typedef dg_char Character;
	typedef dg_short Short;
	typedef dg_int Integer;
	typedef dg_long Long;
	typedef dg_float Float;
	typedef dg_double Double;

    /**
     * check current system whether is 
     * big endian order.
     */
    inline dg_int IsBigEndian() {
		union {
			dg_char i;
			dg_byte c[4];
		} bint = {0x01020304};

		return bint.c[0] == 1;
	}


    /**
     * if current system is big endian, then 
     * swap the order.
     */
	#define __bswap_unicode_char(xx)       ((((dg_char)(xx) << 24) & 0xff000000UL) | \
       (((dg_char)(xx) <<  8) & 0x00ff0000UL) | \
       (((dg_char)(xx) >>  8) & 0x0000ff00UL) | \
       (((dg_char)(xx) >> 24) & 0x000000ffUL))

    inline void SwapChar(const dg_char* pch){
    	__bswap_unicode_char(*pch);
    }

    /**
     * change the char to Unicode Char.
     */
	inline dg_char ToChar(char ch) {
		dg_char uch = ch;
		return uch;	
	}

	/**
     * change the wchar_t to Unicode Char.
     */
	inline dg_char ToChar(wchar_t ch) {
		dg_char uch = ch;
		return uch;	
	}

	/**
     * get char code.
     */
	inline dg_int CharCode(dg_char ch) {
		SwapChar(&ch);
		return (dg_int)ch;
	}

EndPackage2//(dragon, lang)

#endif//BASIC_TYPE_Lang_Dragon_H
