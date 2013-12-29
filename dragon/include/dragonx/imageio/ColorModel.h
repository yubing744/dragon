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


#ifndef ColorModel_Imageio_Dragonx_H
#define ColorModel_Imageio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragonx, imageio)

Import dragon::lang;

class_ ColorModel extends(Object) {
public:
    static const Type* TYPE;

public:
    static const ColorModel* RGB;
    static const ColorModel* RGBA;
    
public:
    ColorModel(int bits, int rmask, int gmask, int bmask);
    ColorModel(int bits, int rmask, int gmask, int bmask, int amask);

    ColorModel(const ColorModel* cm);

    virtual ~ColorModel();
  
public:
    int getBitCount();    

public:
    int getRed(byte* data) const;
    int getGreen(byte* data) const;
    int getBlue(byte* data) const;
    int getAlpha(byte* data) const;

    bool hasAlpha();

protected:
    int getComponentValue(byte* data, int mask) const;

protected:
    int bits;

    int redMask;
    int greenMask;
    int blueMask;
    int alphaMask;
};//ColorModel

EndPackage2 //(dragonx, imageio)

#endif //ColorModel_Imageio_Dragonx_H
