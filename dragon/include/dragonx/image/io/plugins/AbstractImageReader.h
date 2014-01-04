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


#ifndef AbstractImageReader_Plugins_Image_IO_Dragonx_H
#define AbstractImageReader_Plugins_Image_IO_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragonx/image/io/ImageReader.h>


BeginPackage4(dragonx, image, io, plugins)

Import dragon::lang;
Import dragonx::image::io;

class_ AbstractImageReader extends(Object) 
    implements1(ImageReader) {
public:
    static const Type* TYPE;
    
public:
    AbstractImageReader();
    virtual ~AbstractImageReader();
    
};//AbstractImageReader

EndPackage4 //(dragonx, image, io, plugins)

#endif //AbstractImageReader_Plugins_Image_IO_Dragonx_H
