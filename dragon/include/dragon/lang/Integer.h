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


#ifndef Integer_Lang_Dragon_H
#define Integer_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Number.h>
#include <dragon/lang/reflect/Type.h>

BeginPackage2(dragon, lang)

class String;
Import dragon::lang::reflect;

class _DragonExport Integer 
    extends(Number) 
{
public:
    static const Type* TYPE;
    static const Type* INNER_TYPE;

public:
	/**
     * A constant holding the minimum value an <code>int</code> can
     * have, -2<sup>31</sup>.
     */
	static const int MIN_VALUE = 0x80000000;

    /**
     * A constant holding the maximum value an <code>int</code> can
     * have, 2<sup>31</sup>-1.
     */	
	static const int MAX_VALUE = 0x7fffffff;

    /**
     * All possible dg_chars for representing a number as a String
     */
    const static char digits[];

    const static char DigitTens[];

    const static char DigitOnes[];

	/**
     * Places dg_characters representing the integer i into the
     * dg_character array buf. The dg_characters are placed into
     * the buffer backwards starting with the least significant
     * digit at the specified index (exclusive), and working
     * backwards from there.
     *
     * Will fail if i == Integer.MIN_VALUE
     */
    static void getChars(int i, int index, dg_char* buf);

    /**
     * Returns a <code>String</code> object representing the
     * specified integer. The argument is converted to signed decimal
     * representation and returned as a string, exactly as if the
     * argument and radix 10 were given as arguments to the {@link
     * #toString(int, int)} method.
     *
     * @param   i   an integer to be converted.
     * @return  a string representation of the argument in base&nbsp;10.
     */
    static String* toString(int i);

    /**
     * parse string as int
     * 
     * @param  str [description]
     * @return     [description]
     */
    static Integer* parseInt(const String& str);

public:
    Integer();
	Integer(int val);
	virtual ~Integer();

public:
    virtual String* toString() const;

public: //Implements Number
    virtual int intValue();
    virtual dg_long longValue();
    virtual dg_float floatValue();
    virtual double doubleValue();

protected:
	int value;
	
};//Integer

EndPackage2 //(dragon, lang)

#endif //Integer_Lang_Dragon_H
