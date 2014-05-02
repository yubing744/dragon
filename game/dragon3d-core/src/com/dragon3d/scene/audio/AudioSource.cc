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
 * Created:     2013/09/28
 **********************************************************************/

#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/scene/gameObject.h>

#include <com/dragon3d/scene/audio/AudioSource.h>
#include <com/dragon3d/framework/GameException.h>

Import dragon::util::logging;

Import com::dragon3d::scene;
Import com::dragon3d::util::math;
Import com::dragon3d::scene::audio;
Import com::dragon3d::framework;

const Type* AudioSource::TYPE = TypeOf<AudioSource>();

static Logger* logger = Logger::getLogger(AudioSource::TYPE, DEBUG);

/* Define the number of buffers and buffer size (in samples) to use. 4 buffers
 * with 8192 samples each gives a nice per-chunk size, and lets the queue last
 * for almost 3/4ths of a second for a 44.1khz stream. */
#define BUFFER_SIZE 8192


AudioSource::AudioSource() 
    : clip(null), playing(false),
    loop(false), mute(false), volume(1.0), 
    autoPlay(true) {
}

AudioSource::~AudioSource() {
    SafeDelete(this->clip);
}

bool AudioSource::isTypeOf(const Type* type) {
    return AudioSource::TYPE->equals(type) 
        || Behaviour::isTypeOf(type);
}

void AudioSource::init() {
    logger->info("init");

    // validate clip
    if (clip == null) {
        throw new GameException("the audio source must be config a AudioClip!");
    }

    // gen buffers
    alGenBuffers(NUM_BUFFERS, this->buffers);

    if (alGetError() != AL_NO_ERROR) {
        throw new GameException("error in gen openal buffer!");
    }

    // audio format
    const AudioFormat* fmt = clip->getFormat();

    this->frequency = fmt->getSampleRate();
    this->bitSize = fmt->getSampleSizeInBits();
    this->channels = fmt->getChannels();

    if (fmt->getChannels() == 1) {
        this->format = AL_FORMAT_MONO16;

        this->dataSize = this->frequency >> 1;
        this->dataSize -= (this->dataSize % 2);
    } else if (fmt->getChannels() == 2) {
        this->format = AL_FORMAT_STEREO16;

        this->dataSize = this->frequency;
        this->dataSize -= (this->dataSize % 4);
    } else if (fmt->getChannels() == 4) {
        this->format = alGetEnumValue("AL_FORMAT_QUAD16");

        this->dataSize = this->frequency * 2;
        this->dataSize -= (this->dataSize % 8);
    } else if (fmt->getChannels() == 6) {
        this->format = alGetEnumValue("AL_FORMAT_51CHN16");

        this->dataSize = this->frequency * 3;
        this->dataSize -= (this->dataSize % 12);
    } else {
        throw new GameException("not support clip channels!");
    }

    // init buffer 
    this->data = (byte*)malloc(this->dataSize);


    // bind source
    alGenSources(1, &this->source);

    if (alGetError() != AL_NO_ERROR) {
        throw new GameException("error in gen openal source!");
    }

    alSourcef(this->source, AL_PITCH,    1.0f      );
    alSourcef(this->source, AL_GAIN,     1.0f      );
    alSourcei(this->source, AL_LOOPING,  this->loop);

    GameObject* gameObject = this->gameObject;
    Vector3 sourcePos = gameObject->getTransform()->getPosition();
    Vector3 sourceVel(0, 0, 0);

    alSourcefv(this->source, AL_POSITION, sourcePos.getData());
    alSourcefv(this->source, AL_VELOCITY, sourceVel.getData());

    // try play at start
    if (this->autoPlay) {
        this->play();
    }
}

void AudioSource::update(Input* input, ReadOnlyTimer* timer) {
    logger->debug("update");

    GameObject* gameObject = this->gameObject;
    Vector3 sourcePos = gameObject->getTransform()->getPosition();
    Vector3 sourceVel(0, 0, 0);

    alSourcefv(this->source, AL_POSITION, sourcePos.getData());
    alSourcefv(this->source, AL_VELOCITY, sourceVel.getData());
}

void AudioSource::destroy() {
    logger->info("destroy");

    alDeleteSources(1, &this->source);
    alDeleteBuffers(NUM_BUFFERS, this->buffers);

    if(alGetError() != AL_NO_ERROR) {
        throw new GameException("Failed to delete object IDs\n");
    }

    SafeFree(this->data);
}

bool AudioSource::isPlaying() {
    ALint status;
    alGetSourcei(this->source, AL_SOURCE_STATE, &status);

    return status != AL_PLAYING;
}

bool AudioSource::isLoop() {
    return loop;
}

void AudioSource::setAudioClip(AudioClip* clip) {
    SafeDelete(this->clip);
    this->clip = clip;
}

void AudioSource::play() {
    int i;

     /* Rewind the source position and clear the buffer queue */
    alSourceRewind(source);
    alSourcei(source, AL_BUFFER, 0);

    AudioInputStream* stream = const_cast<AudioInputStream*>(clip->getAudioInputStream());

    /* Fill the buffer queue */
    for(i = 0;i < NUM_BUFFERS;i++) {
        int read = stream->read((byte*)this->data, this->dataSize, 0, this->dataSize);

        if (read > 0) {
            alBufferData(this->buffers[i], this->format, this->data, read, this->frequency);
        }
    }

    if(alGetError() != AL_NO_ERROR) {
        throw new GameException("Error buffering for playback\n");
    }

    /* Now queue and start playback! */
    alSourceQueueBuffers(this->source, i, this->buffers);
    alSourcePlay(this->source);

    if(alGetError() != AL_NO_ERROR){
        throw new GameException("Error starting playback\n");
    }
}

void AudioSource::mixing() {
    ALint processed, state;

    /* Get relevant source info */
    alGetSourcei(this->source, AL_SOURCE_STATE, &state);
    alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &processed);

    if(alGetError() != AL_NO_ERROR) {
        throw new GameException("Error checking source state\n");
    }

    AudioInputStream* stream = const_cast<AudioInputStream*>(clip->getAudioInputStream());

    /* Unqueue and handle each processed buffer */
    while(processed > 0) {
        ALuint bufid;
        size_t got;

        alSourceUnqueueBuffers(this->source, 1, &bufid);
        processed--;

        got = stream->read((byte*)this->data, this->dataSize, 0, this->dataSize);

        if (got > 0) {
            alBufferData(bufid, this->format, this->data, got, this->frequency);
            alSourceQueueBuffers(this->source, 1, &bufid);
        }

        if(alGetError() != AL_NO_ERROR) {
            throw new GameException("Error buffering data for update\n");
        }
    }

    /* Make sure the source hasn't underrun */
    if(state != AL_PLAYING && state != AL_PAUSED) {
        ALint queued;

        /* If no buffers are queued, playback is finished */
        alGetSourcei(this->source, AL_BUFFERS_QUEUED, &queued);
        if(queued == 0) {
            return;
        }

        alSourcePlay(this->source);

        if(alGetError() != AL_NO_ERROR) {
            throw new GameException("Error restarting playback\n");
        }
    }
}

void AudioSource::playDelayed(float delay) {
    alSourcePlay(source);
}

void AudioSource::pause() {
    alSourcePause(source);
}

void AudioSource::stop() {
    alSourceStop(source);
}
