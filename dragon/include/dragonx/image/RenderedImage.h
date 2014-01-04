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
 * Created:     2013/12/30
 **********************************************************************/


#ifndef RenderedImage_Image_Dragonx_H
#define RenderedImage_Image_Dragonx_H

#include <dragon/config.h>
#include <dragonx/image/ColorModel.h>

BeginPackage2(dragonx, image)

interface_ RenderedImage {
public:
    virtual ~RenderedImage(){};

public:
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual const byte* getRawData() const = 0;

    virtual uint32_t getPixel(int x, int y) const = 0;

    virtual int getRed(int x, int y) const = 0;
    virtual int getGreen(int x, int y) const = 0;
    virtual int getBlue(int x, int y) const = 0;
    virtual int getAlpha(int x, int y) const = 0;

    virtual const ColorModel* getColorModel() const = 0;
    
};//RenderedImage

EndPackage2 //(dragonx, image)

#endif //RenderedImage_Image_Dragonx_H
