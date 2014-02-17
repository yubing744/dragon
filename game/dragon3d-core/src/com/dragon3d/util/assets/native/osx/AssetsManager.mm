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
 * Created:     2014/02/15
 **********************************************************************/

#import <Foundation/Foundation.h>

#include <com/dragon3d/util/assets/AssetsManager.h>

Import com::dragon3d::util::assets;

Resource* AssetsManager::getResource(const String& uri) {
    const char* utf8String = uri.toUTF8String();

    NSString *homePath = NSHomeDirectory();
    NSLog(@"App Home Path: %@", homePath);
    
    NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:utf8String] ofType:nil];
    Resource* res = null;

    if (fullpath != nil) {
        res = new Resource([fullpath UTF8String]);
    }

    return res;
}

