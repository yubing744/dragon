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
 * Created:     2014/02/23
 **********************************************************************/


#ifndef OggAudioInputStream_Ogg_Plugins_Io_Audio_Dragonx_H
#define OggAudioInputStream_Ogg_Plugins_Io_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragonx/audio/io/plugins/AbstractAudioInputStream.h>

BeginPackage5(dragonx, audio, io, plugins, ogg)

Import dragon::lang;
Import dragonx::audio::io::plugins;

class_ OggAudioInputStream extends(AbstractAudioInputStream) {
public:
    static const Type* TYPE;
    
public:
    OggAudioInputStream(const InputStream* stream);
    virtual ~OggAudioInputStream();

public:
    virtual void open();
    virtual int read(byte* b, int num, int off, int len) throw(IOException*);
    virtual void close() throw(IOException*);
    
};//OggAudioInputStream

EndPackage5 //(dragonx, audio, io, plugins, ogg)

#endif //OggAudioInputStream_Ogg_Plugins_Io_Audio_Dragonx_H
