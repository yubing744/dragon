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

BeginPackage2(dragonx, audio)

Import dragon::lang;

class_ AudioClip extends(Object) {
public:
    static const Type* TYPE;
    
public:
    AudioClip();
    AudioClip(const AudioFormat* format);
    AudioClip(const AudioFormat* format, byte* data, size_t size);

    virtual ~AudioClip();

public:
    const AudioFormat* getAudioFormat() const;

    const byte* getAudioData() const;
    int getAudioDataSize() const;

    void setAudioFormat(const AudioFormat* format);
    void setAudioData(byte* data, size_t size);

protected:
    AudioFormat* format;

    byte* data;
    size_t size;

};//AudioClip

EndPackage2 //(dragonx, audio)

#endif //AudioClip_Audio_Dragonx_H
