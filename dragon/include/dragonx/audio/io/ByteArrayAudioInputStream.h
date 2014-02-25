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
 * Created:     2014/02/25
 **********************************************************************/


#ifndef ByteArrayAudioInputStream_Io_Audio_Dragonx_H
#define ByteArrayAudioInputStream_Io_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragonx/audio/io/AudioInputStream.h>

BeginPackage3(dragonx, audio, io)

Import dragon::lang;

class_ ByteArrayAudioInputStream extends(AudioInputStream) {
public:
    static const Type* TYPE;
    
public:
    ByteArrayAudioInputStream(const AudioFormat* format, const Array<byte> buf);
    ByteArrayAudioInputStream(const AudioFormat* format, const Array<byte> buf, int offset, int length);
    virtual ~ByteArrayAudioInputStream();

public:
    virtual void open();
    virtual const AudioFormat* getFormat() const;
    virtual void checkReadSize(int size) throw(IOException*);

public:
    virtual wlong_u skip(wlong_u n) throw(IOException*);
    virtual int read(byte* b, int num, int off, int len) throw(IOException*);
    virtual void close() throw(IOException*);

public:
    virtual bool markSupported() const;
    virtual void mark(int readlimit);
    virtual void reset() throw(IOException*);
    virtual int available() const;

protected:
    AudioFormat* format;

    Array<byte> buf;
    int pos;
    int markPos;
    int count;  
};//ByteArrayAudioInputStream

EndPackage3 //(dragonx, audio, io)

#endif //ByteArrayAudioInputStream_Io_Audio_Dragonx_H
