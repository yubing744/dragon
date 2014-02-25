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

#include <dragonx/audio/io/plugins/mp3/Mp3AudioReader.h>
#include <dragonx/audio/io/plugins/mp3/Mp3AudioInputStream.h>

Import dragonx::audio::io::plugins::mp3;

Mp3AudioReader::Mp3AudioReader() {

}

Mp3AudioReader::~Mp3AudioReader() {

}

AudioInputStream* Mp3AudioReader::getAudioInputStream(const InputStream* input) const {
    return new Mp3AudioInputStream(input);
}