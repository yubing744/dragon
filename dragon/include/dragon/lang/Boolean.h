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
 * Created:     2013/12/16
 **********************************************************************/


#ifndef Boolean_Lang_Dragon_H
#define Boolean_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragon, lang)

Import dragon::lang::reflect;

DragonClass Boolean
    extends(Object) {
public:
    static const Type* TYPE;
    static const Boolean* TRUE;
    static const Boolean* FALSE;

public:
    static const Boolean* parseBoolean(const String& str);
    static const Boolean* valueOf(const String* str);
    static const Boolean* valueOf(bool val);

public:
    Boolean();
    Boolean(bool val);
    virtual ~Boolean();

public:
    void setBoolean(bool value);
    bool booleanValue() const;

protected:
   bool value; 
};

EndPackage2 //(dragon, lang)

#endif //Boolean_Lang_Dragon_H
