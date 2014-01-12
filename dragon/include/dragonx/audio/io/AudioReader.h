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
 * Created:     2014/01/05
 **********************************************************************/


#ifndef AudioReader_Io_Audio_Dragonx_H
#define AudioReader_Io_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/io/IOException.h>
#include <dragon/io/InputStream.h>
#include <dragonx/audio/AudioClip.h>

BeginPackage3(dragonx, audio, io)

Import dragon::io;
Import dragonx::audio;

interface_ AudioReader {
public:
    virtual ~AudioReader(){};

public:
    virtual AudioClip* read(const InputStream* input) const throw(IOException*) = 0;

};//AudioReader

EndPackage3 //(dragonx, audio, io)

#endif //AudioReader_Io_Audio_Dragonx_H
