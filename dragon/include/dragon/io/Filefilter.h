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
 * Created:     2013/11/03
 **********************************************************************/


#ifndef FileFilter_Io_Dragon_H
#define FileFilter_Io_Dragon_H

#include <dragon/config.h>

BeginPackage2(dragon, io)

class File;

Import dragon::io;

/**
 * A filter for abstract pathnames. 
 * 
 */
__interface _DragonExport FileFilter {
public:
    virtual ~FileFilter(){};

public:
    /**
     * Tests whether or not the specified abstract pathname should be included in a pathname list.
     * 
     * @param  file [description]
     * @return          [description]
     */
    virtual bool accept(const File* file) const = 0;
    
};//FileFilter

EndPackage2 //(dragon, io)

#endif //FileFilter_Io_Dragon_H
