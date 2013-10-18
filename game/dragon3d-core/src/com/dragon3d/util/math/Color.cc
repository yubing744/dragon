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
 * Created:     2013/10/04
 **********************************************************************/


#include <com/dragon3d/util/math/Color.h>

#include <string.h>

Import com::dragon3d::util::math;

static int HexMap[] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,1,2,3, 4,5,6,7, 8,9,0,0, 0,0,0,0,

    0,10,11,12, 13,14,15,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,10,11,12, 13,14,15,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
};

Color Color::hexColor(const char* hexColor){
    if (hexColor[0] == '#') {
        hexColor++;
    }

    int lenght = strlen(hexColor);

    if (lenght >= 6) {
        int offset = -1;
        int r = (HexMap[hexColor[offset + 1]] * 16) + HexMap[hexColor[offset + 2]];
        int g = (HexMap[hexColor[offset + 3]] * 16) + HexMap[hexColor[offset + 4]];
        int b = (HexMap[hexColor[offset + 5]] * 16) + HexMap[hexColor[offset + 6]];

        if (lenght < 8) {
            return Color(r, g, b);
        } else {
            int a = (HexMap[hexColor[offset + 7]] * 16) + HexMap[hexColor[offset + 8]];
            return Color(r, g, b, a);
        }
    }

    return Color::BLACK;
}

const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::RED = Color(1.0f, 0.0f, 0.0f);
const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f);
const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f);
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);

Color::Color(void) {
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
    this->a = 0.0f;
}

Color::Color(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 0.0f;
}

Color::Color(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(int r, int g, int b){
    this->r = r / 256.0f;
    this->g = g / 256.0f;
    this->b = b / 256.0f;
    this->a = 0.0f;
}

Color::Color(int r, int g, int b, int a){
    this->r = r / 256.0f;
    this->g = g / 256.0f;
    this->b = b / 256.0f;
    this->a = a / 256.0f;
}

Color::Color(dg_byte r, dg_byte g, dg_byte b){
    this->r = r / 256.0f;
    this->g = g / 256.0f;
    this->b = b / 256.0f;
    this->a = 0.0f;
}

Color::Color(dg_byte r, dg_byte g, dg_byte b, dg_byte a){
    this->r = r / 256.0f;
    this->g = g / 256.0f;
    this->b = b / 256.0f;
    this->a = a / 256.0f;
}

Color::Color(const char* hexColor){
    *this = Color::hexColor(hexColor);
}


const float* Color::getData() const {
    return (float*)(&this->r);
}