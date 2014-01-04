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


#ifndef ColorModel_Image_Dragonx_H
#define ColorModel_Image_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragonx, image)

Import dragon::lang;

class_ ColorModel extends(Object) {
public:
    static const Type* TYPE;

public:
    static const ColorModel* TYPE_24_RGB;
    static const ColorModel* TYPE_32_RGBA;
    
public:
    ColorModel(int bits, uint32_t rmask, uint32_t gmask, uint32_t bmask);
    ColorModel(int bits, uint32_t rmask, uint32_t gmask, uint32_t bmask, uint32_t amask);

    ColorModel(const ColorModel* cm);

    virtual ~ColorModel();
  
public:
    int getBitCount() const;    

public:
    int getRed(const byte* data) const;
    int getGreen(const byte* data) const;
    int getBlue(const byte* data) const;
    int getAlpha(const byte* data) const;

    bool hasAlpha() const;

    void setPixel(byte* data, uint32_t val) const;
    uint32_t getPixel(const byte* data) const;

protected:
    int getComponentValue(const byte* data, uint32_t mask) const;
    void validate();
    
    int calOffset(uint32_t mask);
    void calOffsets();

protected:
    int bits;

    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;

    int offsetRed;
    int offsetGreen;
    int offsetBlue;
    int offsetAlpha;

};//ColorModel

EndPackage2 //(dragonx, image)

#endif //ColorModel_Image_Dragonx_H
