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
 * Created:     2013/12/28
 **********************************************************************/

#include <string.h>

#include <dragonx/image/BufferedImage.h>

Import dragonx::image;

const Type* BufferedImage::TYPE = TypeOf<BufferedImage>();

BufferedImage::BufferedImage(int width, int height, const ColorModel* colorModel) 
    :width(width), height(height) {
    this->colorModel = new ColorModel(colorModel);

    int total = this->size();
    byte* data = (byte*)malloc(total);
    memset(data, 0, total);

    this->data = data;
}

BufferedImage::~BufferedImage() {
    SafeDelete(this->colorModel);
    SafeFree(this->data);
}

int BufferedImage::getWidth() const {
    return this->width;
}

int BufferedImage::getHeight() const {
    return this->height;
}

const byte* BufferedImage::getRawData() const {
    return this->data;
}

int BufferedImage::size() const {
    //return this->width * this->height * this->colorModel->getBitCount();
    return this->width * this->height * (this->colorModel->getBitCount() / 8);
}
const Array<byte> BufferedImage::getData() const {
    return Array<byte>(this->data, this->size(), false);
}

const byte* BufferedImage::getPixelData(int index) const {
    const ColorModel* cm = this->getColorModel();
    int pixelByteCount = cm->getBitCount() / 8;
    int offset = index * pixelByteCount;
    byte* data = this->data + offset;
    return data;
}

const byte* BufferedImage::getPixelData(int x, int y) const {
    int index = (this->getWidth() * y) + x;
    return getPixelData(index);
}

void BufferedImage::setPixel(int x, int y, uint32_t val) {
    const byte* data = getPixelData(x, y);
    this->colorModel->setPixel(const_cast<byte*>(data), val);
}

void BufferedImage::setRed(int x, int y, int val) {
    const byte* data = getPixelData(x, y);
    this->colorModel->setRed(data, val); 
}

void BufferedImage::setGreen(int x, int y, int val) {
    const byte* data = getPixelData(x, y);
    this->colorModel->setGreen(data, val); 
}

void BufferedImage::setBlue(int x, int y, int val) {
    const byte* data = getPixelData(x, y);
    this->colorModel->setBlue(data, val); 
}

void BufferedImage::setAlpha(int x, int y, int val) {
    const byte* data = getPixelData(x, y);
    this->colorModel->setAlpha(data, val); 
}

void BufferedImage::setRed(int index, int val) {
    const byte* data = getPixelData(index);
    this->colorModel->setRed(data, val); 
}

void BufferedImage::setGreen(int index, int val) {
    const byte* data = getPixelData(index);
    this->colorModel->setGreen(data, val); 
}

void BufferedImage::setBlue(int index, int val) {
    const byte* data = getPixelData(index);
    this->colorModel->setBlue(data, val); 
}

void BufferedImage::setAlpha(int index, int val) {
    const byte* data = getPixelData(index);
    this->colorModel->setAlpha(data, val); 
}

uint32_t BufferedImage::getPixel(int x, int y) const {
    const byte* data = getPixelData(x, y);
    return this->getColorModel()->getPixel(data);   
}

int BufferedImage::getRed(int x, int y) const {
    const byte* data = getPixelData(x, y);
    return this->getColorModel()->getRed(data);  
}

int BufferedImage::getGreen(int x, int y) const {
    const byte* data = getPixelData(x, y);
    return this->getColorModel()->getGreen(data);  
}

int BufferedImage::getBlue(int x, int y) const {
    const byte* data = getPixelData(x, y);
    return this->getColorModel()->getBlue(data);  
}

int BufferedImage::getAlpha(int x, int y) const {
    const byte* data = getPixelData(x, y);
    return this->getColorModel()->getAlpha(data);  
}

int BufferedImage::getRed(int index) const {
    const byte* data = getPixelData(index);
    return this->getColorModel()->getRed(data);  
}

int BufferedImage::getGreen(int index) const {
    const byte* data = getPixelData(index);
    return this->getColorModel()->getGreen(data);  
}

int BufferedImage::getBlue(int index) const {
    const byte* data = getPixelData(index);
    return this->getColorModel()->getBlue(data);  
}

int BufferedImage::getAlpha(int index) const {
    const byte* data = getPixelData(index);
    return this->getColorModel()->getAlpha(data);    
}

const ColorModel* BufferedImage::getColorModel() const {
    return this->colorModel;
}
