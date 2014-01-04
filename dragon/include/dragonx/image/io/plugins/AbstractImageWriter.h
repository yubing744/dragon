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


#ifndef AbstractImageWriter_Plugins_Image_IO_Dragonx_H
#define AbstractImageWriter_Plugins_Image_IO_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragonx/image/io/ImageWriter.h>

BeginPackage4(dragonx, image, io, plugins)

Import dragon::lang;
Import dragonx::image::io;

class_ AbstractImageWriter extends(Object) 
    implements1(ImageWriter) {
public:
    static const Type* TYPE;
    
public:
    AbstractImageWriter();
    virtual ~AbstractImageWriter();
        
};//AbstractImageWriter

EndPackage4 //(dragonx, image, io, plugins)

#endif //AbstractImageWriter_Plugins_Image_IO_Dragonx_H
