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
 * Created:     2014/01/01
 **********************************************************************/


#ifndef TGAImageWriter_Tga_Plugins_Io_Image_Dragonx_H
#define TGAImageWriter_Tga_Plugins_Io_Image_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragonx/image/io/plugins/AbstractImageWriter.h>

BeginPackage5(dragonx, image, io, plugins, tga)

Import dragon::lang;
Import dragonx::image::io::plugins;

class_ TGAImageWriter extends(AbstractImageWriter) {
public:
    static const Type* TYPE;
    
public:
    TGAImageWriter();
    virtual ~TGAImageWriter();

public:
    virtual void write(const RenderedImage* image, OutputStream* output) throw(IOException*);
    
};//TGAImageWriter

EndPackage5 //(dragonx, image, io, plugins, tga)

#endif //TGAImageWriter_Tga_Plugins_Io_Image_Dragonx_H
