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

#include <xlocale.h>
#include <mach/mach.h>
#include <Cocoa/Cocoa.h>

#include <dragon/io/File.h>

Import dragon::lang;
Import dragon::io;

bool File::isHidden() {
    NSNumber* hidden = nil;
    NSError* err = nil;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    NSString* nsPath = [NSString stringWithUTF8String: utf8Path.raw()];

    return [[NSURL fileURLWithPath: nsPath]
                getResourceValue: &hidden forKey: NSURLIsHiddenKey error: &err]
            && [hidden boolValue];
}
