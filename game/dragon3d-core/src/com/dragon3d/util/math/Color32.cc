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
 * Created:     2014/03/27
 **********************************************************************/


#include <com/dragon3d/util/math/Color32.h>
#include <dragon/util/logging/Logger.h>

Import com::dragon3d::util::math;
Import dragon::util::logging;

const Type* Color32::TYPE = TypeOf<Color32>();
static Logger* logger = Logger::getLogger(Color32::TYPE, ERROR);

Color32::Color32() 
    :r(0), g(0), b(0), a(0) {

}

Color32::Color32(byte r, byte g, byte b, byte a) 
    :r(r), g(g), b(b), a(a) {

}

Color32::~Color32() {

}

const byte* Color32::getData() const {
    return (byte*)(&this->r);
}

const Array<byte> Color32::toByteArray() const {
    return Array<byte>(this->getData(), 4, false);
}