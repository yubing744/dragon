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


#include <dragonx/imageio/ColorModel.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::imageio;
Import dragon::util::logging;

const Type* ColorModel::TYPE = TypeOf<ColorModel>();
static Logger* logger = Logger::getLogger(ColorModel::TYPE, ERROR);

const ColorModel* ColorModel::RGB = new ColorModel(24, 
        0xff0000,
        0x00ff00,
        0x0000ff,
        0x000000);

const ColorModel* ColorModel::RGBA = new ColorModel(32,         
        0xff000000,
        0x00ff0000,
        0x0000ff00,
        0x000000ff);

ColorModel::ColorModel(int bits, int rmask, int gmask, int bmask) 
    :bits(bits), redMask(rmask), greenMask(gmask), blueMask(bmask), alphaMask(0){

}

ColorModel::ColorModel(int bits, int rmask, int gmask, int bmask, int amask) 
    :bits(bits), redMask(rmask), greenMask(gmask), blueMask(bmask), alphaMask(0) {

}

ColorModel::ColorModel(const ColorModel* cm) 
    :bits(cm->bits), redMask(cm->redMask), greenMask(cm->greenMask), blueMask(cm->blueMask), alphaMask(cm->alphaMask) {

}

ColorModel::~ColorModel() {

}

int ColorModel::getComponentValue(byte* data, int mask) const {

}

int ColorModel::getRed(byte* data) const {

}

int ColorModel::getGreen(byte* data) const {

}

int ColorModel::getBlue(byte* data) const {

}

int ColorModel::getAlpha(byte* data) const {

}

bool ColorModel::hasAlpha() {
    return this->alphaMask > 0;
}

int ColorModel::getBitCount() {
    return this->bits;  
}
