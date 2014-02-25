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
 * Created:     2014/01/06
 **********************************************************************/


#ifndef AudioClip_Audio_Dragonx_H
#define AudioClip_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>
#include <dragonx/audio/AudioFormat.h>
#include <dragonx/audio/io/AudioInputStream.h>

BeginPackage2(dragonx, audio)

Import dragon::lang;
Import dragonx::audio;
Import dragonx::audio::io;

class_ AudioClip extends(Object) {
public:
    static const Type* TYPE;
    
public:
    AudioClip(const AudioFormat* format, const byte* data, size_t off, size_t len);
    AudioClip(AudioInputStream* stream);
    AudioClip(InputStream* stream, const String& format);

    virtual ~AudioClip();

public:
    AudioInputStream* getAudioInputStream() const;

    const AudioFormat* getFormat() const;
    const Array<byte> getData() const;

protected:
    AudioInputStream* stream;
};//AudioClip

EndPackage2 //(dragonx, audio)

#endif //AudioClip_Audio_Dragonx_H
