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
 * Created:     2013/06/26
 **********************************************************************/


#ifndef Long_Lang_Dragon_H
#define Long_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Number.h>

BeginPackage2(dragon, lang)

class String;

class _DragonExport Long 
    extends(Number) {
public:
    /**
     * A constant holding the minimum value a <code>dg_long</code> can
     * have, -2<sup>63</sup>.
     */
    static const dg_long MIN_VALUE = 0x8000000000000000L;

    /**
     * A constant holding the maximum value a <code>dg_long</code> can
     * have, 2<sup>63</sup>-1.
     */
    static const dg_long MAX_VALUE = 0x7fffffffffffffffL;

    /**
     * Places characters representing the integer i into the
     * character array buf. The characters are placed into
     * the buffer backwards starting with the least significant
     * digit at the specified index (exclusive), and working
     * backwards from there.
     *
     * Will fail if i == Long.MIN_VALUE
     */
    static void getChars(dg_long i, dg_int index, dg_char* buf);

    /**
     * Returns a <code>String</code> object representing the specified
     * <code>long</code>.  The argument is converted to signed decimal
     * representation and returned as a string, exactly as if the
     * argument and the radix 10 were given as arguments to the {@link
     * #toString(long, int)} method.
     *
     * @param   i   a <code>long</code> to be converted.
     * @return  a string representation of the argument in base&nbsp;10.
     */
    static String* toString(dg_long i);

public:
	Long(dg_long val);
	virtual ~Long();

public:
    virtual String* toString();

public: //Implements Number
    virtual dg_int intValue();
    virtual dg_long longValue();
    virtual dg_float floatValue();
    virtual dg_double doubleValue();

protected:
	dg_long value;
};//Long

EndPackage2 //(dragon, lang)

#endif //Long_Lang_Dragon_H
