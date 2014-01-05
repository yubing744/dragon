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
 * Created:     2013/12/29
 **********************************************************************/


#include <dragonx/image/ColorModel.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/RuntimeException.h>

Import dragon::lang;
Import dragonx::image;
Import dragon::util::logging;

const Type* ColorModel::TYPE = TypeOf<ColorModel>();
static Logger* logger = Logger::getLogger(ColorModel::TYPE, ERROR);

const ColorModel* ColorModel::TYPE_24_RGB = new ColorModel(24, 
        0xff0000,
        0x00ff00,
        0x0000ff,
        0x000000);

const ColorModel* ColorModel::TYPE_32_RGBA = new ColorModel(32,         
        0xff000000,
        0x00ff0000,
        0x0000ff00,
        0x000000ff);

ColorModel::ColorModel(int bits, uint32_t rmask, uint32_t gmask, uint32_t bmask) 
    :bits(bits), redMask(rmask), greenMask(gmask), blueMask(bmask), alphaMask(0){
    calOffsets();
}

ColorModel::ColorModel(int bits, uint32_t rmask, uint32_t gmask, uint32_t bmask, uint32_t amask) 
    :bits(bits), redMask(rmask), greenMask(gmask), blueMask(bmask), alphaMask(amask) {
    calOffsets();
}

ColorModel::ColorModel(const ColorModel* cm) 
    :bits(cm->bits), redMask(cm->redMask), greenMask(cm->greenMask), blueMask(cm->blueMask), alphaMask(cm->alphaMask) {
    calOffsets();
}

ColorModel::~ColorModel() {

}

int ColorModel::calOffset(uint32_t mask) {
    int off = 0;

    if (mask != 0) {
        while ((mask & 1) == 0) {
            mask >>= 1;
            off++;
        }
    }

    return off;
}

void ColorModel::calOffsets() {
    this->offsetRed = calOffset(this->redMask);
    this->offsetGreen = calOffset(this->greenMask);
    this->offsetBlue = calOffset(this->blueMask);
    this->offsetAlpha = calOffset(this->alphaMask);
}

void ColorModel::validate() {
    if (this->bits % 8 == 0 || this->bits / 8 > 4) {
        throw new RuntimeException("not support bits count!");
    }
}

void ColorModel::setPixel(byte* data, uint32_t val) const {
    int byteCount = this->bits / 8;
    int n = byteCount;

    uint32_t bitsVal = val;

    while(n > 0) {
        byte b = bitsVal & 0xff;
        data[n - 1] = b;

        bitsVal >>= 8;
        n--;
    }
}

void ColorModel::setComponetValue(const byte* data, uint32_t mask, int val) {
    uint32_t color = getPixel(data);
    color = color & (~mask);
    color = color & val;
}

void ColorModel::setRed(const byte* data, int val) {
    setComponetValue(data, this->redMask, val << this->offsetRed);
}

void ColorModel::setGreen(const byte* data, int val) {
    setComponetValue(data, this->greenMask, val << this->offsetGreen);
}

void ColorModel::setBlue(const byte* data, int val) {
    setComponetValue(data, this->blueMask, val << this->offsetBlue);
}

void ColorModel::setAlpha(const byte* data, int val) {
    setComponetValue(data, this->alphaMask, val << this->offsetAlpha);
}

uint32_t ColorModel::getPixel(const byte* data) const {
    int byteCount = this->bits / 8;
    int n = byteCount;

    uint32_t bitsVal = 0;

    while(n > 0) {
        byte b = data[byteCount - n];

        bitsVal <<= 8;
        bitsVal = bitsVal | b;

        n--;
    }

    return bitsVal;
}

int ColorModel::getComponentValue(const byte* data, uint32_t mask) const {
    return getPixel(data) & mask;
}

int ColorModel::getRed(const byte* data) const {
    return getComponentValue(data, this->redMask) >> this->offsetRed;
}

int ColorModel::getGreen(const byte* data) const {
    return getComponentValue(data, this->greenMask) >> this->offsetGreen;
}

int ColorModel::getBlue(const byte* data) const {
    return getComponentValue(data, this->blueMask) >> this->offsetBlue;
}

int ColorModel::getAlpha(const byte* data) const {
    return getComponentValue(data, this->alphaMask) >> this->offsetAlpha;
}

bool ColorModel::hasAlpha() const {
    return this->alphaMask > 0;
}

int ColorModel::getBitCount() const {
    return this->bits;  
}

