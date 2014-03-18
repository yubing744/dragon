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
 * Created:     2014/03/16
 **********************************************************************/


#ifndef ModelLoadException_Modelio_Assets_Util_Dragon3d_Com_H
#define ModelLoadException_Modelio_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/IOException.h>

BeginPackage5(com, dragon3d, util, assets, modelio)

Import dragon::io;
Import dragon::lang;

class_ ModelLoadException extends(IOException) {
public:
    static const Type* TYPE;
    
public:
    ModelLoadException();
    ModelLoadException(const String& message);
    ModelLoadException(const String& message, Throwable* cause);

    virtual ~ModelLoadException();
    
};//ModelLoadException

EndPackage5 //(com, dragon3d, util, assets, modelio)

#endif //ModelLoadException_Modelio_Assets_Util_Dragon3d_Com_H
