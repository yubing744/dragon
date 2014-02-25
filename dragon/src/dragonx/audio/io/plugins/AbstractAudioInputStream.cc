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

#include <dragon/util/logging/Logger.h>
#include <dragonx/audio/AudioFormat.h>
#include <dragonx/audio/io/plugins/AbstractAudioInputStream.h>

Import dragonx::audio;
Import dragon::util::logging;
Import dragonx::audio::io::plugins;

const Type* AbstractAudioInputStream::TYPE = TypeOf<AbstractAudioInputStream>();
static Logger* logger = Logger::getLogger(AbstractAudioInputStream::TYPE, ERROR);

AbstractAudioInputStream::AbstractAudioInputStream(const InputStream* stream) 
    :stream(const_cast<InputStream*>(stream)), format(new AudioFormat()) {

}

AbstractAudioInputStream::~AbstractAudioInputStream() {
    SafeDelete(this->format);
}

const AudioFormat* AbstractAudioInputStream::getFormat() const {
    return this->format;
}

wlong_u AbstractAudioInputStream::skip(wlong_u n) throw(IOException*) {
    this->checkReadSize(n);

    byte* buf = (byte*)malloc(n);
    int read = InputStream::read(buf, n);
    free(buf);

    return read;
}

void AbstractAudioInputStream::checkReadSize(int size) throw(IOException*) {
    const AudioFormat* fmt = this->getFormat();
    int frameSize = fmt->getFrameSize();

    if (size % frameSize != 0) {
        throw new IOException("the skip size must be multiple of frame size.");
    }
}