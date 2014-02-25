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


#ifndef AudioFormat_Audio_Dragonx_H
#define AudioFormat_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragonx, audio)

Import dragon::lang;

class_ AudioFormat extends(Object) {
public:
    static const Type* TYPE;
    
public:
    AudioFormat();
    AudioFormat(const AudioFormat& format);
    AudioFormat(const AudioFormat* format);

    virtual ~AudioFormat();

public:
    float getSampleRate() const;
    int getSampleSizeInBits() const;
    int getChannels() const;
    bool isBigEndian() const;
    int getFrameSize() const;

    void setSampleRate(float sampleRate);
    void setSampleSizeInBits(int sampleBitsSize);
    void setChannels(int channels);
    void setBigEndian(bool isBigEndian);

protected:
    /**
     * The number of samples played or recorded per second, for sounds that have this format.
     */
    float sampleRate;

    /**
     * The number of bits in each sample of a sound that has this format.
     */
    int sampleSizeInBits;

    /**
     * The number of audio channels in this format (1 for mono, 2 for stereo).
     */
    int channels;

    /**
     * Indicates whether the audio data is stored in big-endian or little-endian order.
     */
    bool bigEndian;

};//AudioFormat

EndPackage2 //(dragonx, audio)

#endif //AudioFormat_Audio_Dragonx_H
