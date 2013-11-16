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


#ifndef FilenameFilter_Io_Dragon_H
#define FilenameFilter_Io_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/String.h>

BeginPackage2(dragon, io)

class File;

Import dragon::io;
Import dragon::lang;

/**
 * Instances of classes that implement this interface are used to filter filenames. 
 * These instances are used to filter directory listings in the list method of class File, 
 * and by the Abstract Window Toolkit's file dialog component. 
 */
__interface _DragonExport FilenameFilter {
public:
    virtual ~FilenameFilter(){};

public:
    /**
     * Tests if a specified file should be included in a file list.
     * 
     * @param  dir  [description]
     * @param  name [description]
     * @return      [description]
     */
    virtual bool accept(const File* dir, const String* name) const = 0;
    
};//FilenameFilter

EndPackage2 //(dragon, io)

#endif //FilenameFilter_Io_Dragon_H
