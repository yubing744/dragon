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

#include <dragon/lang/Double.h>
#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/Array.h>

Import dragon::lang;
Import dragon::lang::reflect;

const Type* Double::TYPE = TypeOf<double>();
const Type* Double::PRIMARY_TYPE = TypeOf<Double>();

Double* Double::parseDouble(const String& str) throw(NumberFormatException*) {
    const Array<byte> data = str.getBytes("UTF-8");
    double val = atof(data.raw());

    if (Math::abs(val) < (1e-8) && !str.matches("-?\\d+(\\.\\d+)?")) {
        throw new NumberFormatException();
    }

    return new Double(val);
}

String* Double::toString(double val) {
    stringstream ostr("");
    ostr << val;
    return new String(ostr.str().c_str());
}

Double::Double(double val) {
	this->value = val;
}

Double::~Double() {

}

double Double::doubleValue() {
	return this->value;
}

String* Double::toString() const {
    return Double::toString(this->value);
}