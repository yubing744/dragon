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


#ifndef Float_Lang_Dragon_H
#define Float_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Number.h>
#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/NumberFormatException.h>

BeginPackage2(dragon, lang)

Import dragon::lang;
Import dragon::lang::reflect;

class _DragonExport Float 
	extends(Number) 
{
public:
    static const Type* TYPE;
    static const Type* INNER_TYPE;
       
public:
    static Float* parseFloat(const String& str) throw(NumberFormatException*);
    static String* toString(float val);
    
public:
	Float(float val);
	virtual ~Float();

public:
	virtual float floatValue();
    virtual String* toString() const;

protected:
	float value;

};//Float

EndPackage2 //(dragon, lang)

#endif //Float_Lang_Dragon_H
