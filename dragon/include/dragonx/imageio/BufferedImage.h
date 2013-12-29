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


#ifndef BufferedImage_Imageio_Dragonx_H
#define BufferedImage_Imageio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

#include <dragonx/imageio/ColorModel.h>

BeginPackage2(dragonx, imageio)

Import dragon::lang;
Import dragonx::imageio;

class_ BufferedImage extends(Object) {
public:
    static const Type* TYPE;
    
public:
    BufferedImage(int width, int height, const ColorModel* colorModel);

    virtual ~BufferedImage();

public:
    int getWidth() const;
    int getHeight() const;

    const byte* getRawData() const;
    int size() const;

    const Array<byte> getData() const;
protected:
    int width;
    int height;
    byte* data;

    ColorModel* colorModel;
};//BufferedImage

EndPackage2 //(dragonx, imageio)

#endif //BufferedImage_Imageio_Dragonx_H
