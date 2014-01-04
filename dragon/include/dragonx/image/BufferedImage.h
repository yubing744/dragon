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


#ifndef BufferedImage_Image_Dragonx_H
#define BufferedImage_Image_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

#include <dragonx/image/Image.h>
#include <dragonx/image/ColorModel.h>
#include <dragonx/image/RenderedImage.h>

BeginPackage2(dragonx, image)

Import dragon::lang;

class_ BufferedImage extends(Image) 
    implements1(RenderedImage) {
public:
    static const Type* TYPE;
    
public:
    BufferedImage(int width, int height, const ColorModel* colorModel);

    virtual ~BufferedImage();

public:
    virtual int getWidth() const;
    virtual int getHeight() const;

    virtual const byte* getRawData() const;
    virtual int size() const;

    virtual const Array<byte> getData() const;

    virtual void setPixel(int x, int y, uint32_t val);
    virtual uint32_t getPixel(int x, int y) const;

    virtual int getRed(int x, int y) const;
    virtual int getGreen(int x, int y) const;
    virtual int getBlue(int x, int y) const;
    virtual int getAlpha(int x, int y) const;

    virtual int getRed(int index) const;
    virtual int getGreen(int index) const;
    virtual int getBlue(int index) const;
    virtual int getAlpha(int index) const;

    virtual const ColorModel* getColorModel() const;
    
protected:
    virtual const byte* getPixelData(int index) const;
    virtual const byte* getPixelData(int x, int y) const;

protected:
    int width;
    int height;
    byte* data;

    ColorModel* colorModel;
};//BufferedImage

EndPackage2 //(dragonx, image)

#endif //BufferedImage_Image_Dragonx_H
