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

#include <iostream>
#include <sstream>
#include <string> 

#include <dragon/lang/String.h>
#include <dragon/lang/Array.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/Math.h>

Import std;
Import dragon::lang;
Import dragon::lang::reflect;

const Type* Float::TYPE = TypeOf<Float>();
const Type* Float::INNER_TYPE = TypeOf<float>();

Float::Float(float val) {
	this->value = val;
}

Float::~Float() {

}

float Float::floatValue() {
	return this->value;
}

Float* Float::parseFloat(const String& str) throw(NumberFormatException*) {
    if (!str.matches("-?\\d+(\\.\\d+)?")) {
        throw new NumberFormatException();
    }

    const Array<byte> data = str.getBytes("UTF-8");
    double val = atof(data.raw());
    return new Float((float)val);
}

String* Float::toString(float val) {
    stringstream ostr("");
    ostr << val;
    return new String(ostr.str().c_str());
}

String* Float::toString() const {
    return Float::toString(this->value);
}