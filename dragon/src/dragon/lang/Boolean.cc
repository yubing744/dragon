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


#include <dragon/lang/Boolean.h>
#include <dragon/lang/String.h>


Import dragon::lang;

const Type* Boolean::TYPE = TypeOf<Boolean>();
const Boolean* Boolean::TRUE = new Boolean(true);
const Boolean* Boolean::FALSE = new Boolean(false);

const Boolean* Boolean::parseBoolean(const String& str) {
    const Array<byte> data = str.getBytes("UTF-8");

    if (strcmp("true", data.raw()) == 0) {
        return Boolean::TRUE;
    } else if (strcmp("false", data.raw()) == 0) {
        return Boolean::FALSE;
    }

    return null;
}

const Boolean* Boolean::valueOf(const String* str) {
    return Boolean::parseBoolean(str);
}

const Boolean* Boolean::valueOf(bool val) {
    if (val) {
        return Boolean::TRUE;
    } else {
        return Boolean::FALSE;
    }
}   

Boolean::Boolean() 
    :value(false) {

}

Boolean::Boolean(bool val) 
    :value(val) {

}

Boolean::~Boolean() {

}

void Boolean::setBoolean(bool value) {
    this->value = value;
}

bool Boolean::booleanValue() const {
    return this->value;
}