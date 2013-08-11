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


#include <dragon/lang/Long.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/String.h>

Import dragon::lang;

/**
 * Places dg_characters representing the dg_integer i dg_into the
 * dg_character array buf. The dg_characters are placed dg_into
 * the buffer backwards starting with the least significant
 * digit at the specified index (exclusive), and working
 * backwards from there.
 *
 * Will fail if i == Long.MIN_VALUE
 */
void Long::getChars(dg_long i, dg_int index, dg_char* buf) {
    dg_long q;
    dg_int r;
    dg_int dg_charPos = index;
    dg_char sign = 0;

    if (i < 0) {
        sign = '-';
        i = -i;
    }

    // Get 2 digits/iteration using dg_longs until quotient fits dg_into an dg_int
    while (i > Integer::MAX_VALUE) { 
        q = i / 100;
        // really: r = i - (q * 100);
        r = (dg_int)(i - ((q << 6) + (q << 5) + (q << 2)));
        i = q;
        buf[--dg_charPos] = Integer::DigitOnes[r];
        buf[--dg_charPos] = Integer::DigitTens[r];
    }

    // Get 2 digits/iteration using dg_ints
    dg_uint q2;
    dg_uint i2 = (dg_int)i;
    while (i2 >= 65536) {
        q2 = i2 / 100;
        // really: r = i2 - (q * 100);
        r = i2 - ((q2 << 6) + (q2 << 5) + (q2 << 2));
        i2 = q2;
        buf[--dg_charPos] = Integer::DigitOnes[r];
        buf[--dg_charPos] = Integer::DigitTens[r];
    }

    // Fall thru to fast mode for smaller numbers
    // assert(i2 <= 65536, i2);
    for (;;) {
        q2 = (i2 * 52429) >> (16+3);
        r = i2 - ((q2 << 3) + (q2 << 1));  // r = i2-(q2*10) ...
        buf[--dg_charPos] = Integer::digits[r];
        i2 = q2;
        if (i2 == 0) break;
    }
    if (sign != 0) {
        buf[--dg_charPos] = sign;
    }
}

// Requires positive x
static dg_int stringSize(dg_long x) {
    dg_long p = 10;
    for (dg_int i=1; i<19; i++) {
        if (x < p)
            return i;
        p = 10*p;
    }
    return 19;
}


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
String* Long::toString(dg_long i) {
    if (i == Long::MIN_VALUE)
        return new String("-9223372036854775808");
    dg_int size = (i < 0) ? stringSize(-i) + 1 : stringSize(i);
    dg_char* buf = new dg_char[size];
    getChars(i, size, buf);
    String* result = new String(buf, 0, size);
    SafeDeleteArray(buf);

    return result;
}

//-----------------------------------------------
//
Long::Long(dg_long l) {
	this->value = l;
}

Long::~Long() {

}

//-----------------------------------------------
dg_long Long::longValue(){
	return this->value;
}

String* Long::toString() {
    return Long::toString(this->value);
}
