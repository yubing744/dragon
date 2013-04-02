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

#include <dragon/lang/Number.h>

Import dragon::lang;

Number::Number(){}


int Number::ParseInt(String num) throw(NumberFormatException)
{
	int result = _wtoi(num);

	if ( !num.equals(L"0") && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

long  Number::ParseLong(String num) throw(NumberFormatException)
{
	long result = _wtol(num);

	if ((!num.equals(L"0")) && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

double  Number::ParseDouble(String num) throw(NumberFormatException)
{
	double result = _wtof(num);

	if ((!num.equals(L"0.0")) && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

float  Number::ParseFloat(String num) throw(NumberFormatException)
{
	float result = (float)_wtof(num);

	if ((!num.equals(L"0.0")) && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

