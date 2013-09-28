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
 * Created:     2013/06/29
 **********************************************************************/


#ifndef Number_Lang_Dragon_H
#define Number_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragon, lang)

Import dragon::lang;

/**
 * Subclasses of Number must provide methods to convert the represented numeric value to 
 * byte, double, float, int, long, and short. 
 */
class _DragonExport Number 
	extends(Object) {
public:
	Number();
	virtual ~Number();

public:
	/**
	 * Returns the value of the specified number as an int. This may involve rounding or truncation. 
	 * 
	 * @return the numeric value represented by this object after conversion to type int.
	 */
	virtual dg_int intValue() {return 0;};

	/**
	 * Returns the value of the specified number as a long. This may involve rounding or truncation. 
	 * 
	 * @return the numeric value represented by this object after conversion to type long.
	 */
	virtual dg_long longValue() {return 0;};

	/**
	 * Returns the value of the specified number as a float. This may involve rounding. 
	 * 
	 * @return the numeric value represented by this object after conversion to type float.
	 */
	virtual dg_float floatValue() {return 0;};

	/**
	 * Returns the value of the specified number as a double. This may involve rounding. 
	 * 
	 * @return the numeric value represented by this object after conversion to type double.
	 */
	virtual dg_double doubleValue() {return 0;};

	/**
	 * Returns the value of the specified number as a byte. This may involve rounding or truncation. 
	 * 
	 * @return the numeric value represented by this object after conversion to type byte.
	 */
	virtual dg_byte byteValue();

	/**
	 * Returns the value of the specified number as a short. This may involve rounding or truncation. 
	 * 
	 * @return the numeric value represented by this object after conversion to type short.
	 */
	virtual dg_short shortValue();
	
};//Number

EndPackage2 //(dragon, lang)

#endif //Number_Lang_Dragon_H
