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


#ifndef Double_Lang_Dragon_H
#define Double_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Number.h>
#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/String.h>


BeginPackage2(dragon, lang)

Import dragon::lang::reflect;

class _DragonExport Double 
	extends(Number) 
{
public:
    static const Type* TYPE;
    static const Type* PRIMARY_TYPE;
    
public:
    static Double* parseDouble(const String& str);
    static String* toString(double val);

public:
	Double(double val);
	virtual ~Double();

public:
	double doubleValue();
    String* toString() const;

protected:
	double value;	
};//Double

EndPackage2 //(dragon, lang)

#endif //Double_Lang_Dragon_H
