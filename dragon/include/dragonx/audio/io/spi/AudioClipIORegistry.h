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


#ifndef AudioClipIORegistry_Spi_Io_Audio_Dragonx_H
#define AudioClipIORegistry_Spi_Io_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/util/Map.h>
#include <dragonx/audio/io/AudioReader.h>


BeginPackage4(dragonx, audio, io, spi)

Import dragon::lang;
Import dragon::util;
Import dragonx::audio::io;

class_ AudioClipIORegistry extends(Object) {
public:
    static const Type* TYPE;

private:
    static AudioClipIORegistry* singleton;
public:
    static AudioClipIORegistry* getInstance();

public:
    AudioClipIORegistry();
    virtual ~AudioClipIORegistry();

protected:
    void init();

public:
    void registerAudioReader(const String& audioType, AudioReader* reader);
    
    const AudioReader* getAudioReader(const String& audioType);

protected:
    Map<String, AudioReader>* readerMap;
};//AudioClipIORegistry

EndPackage4 //(dragonx, audio, io, spi)

#endif //AudioClipIORegistry_Spi_Io_Audio_Dragonx_H
