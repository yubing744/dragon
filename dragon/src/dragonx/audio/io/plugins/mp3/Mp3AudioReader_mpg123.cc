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

#include <stdio.h>
#include <strings.h>
#include <mpg123.h>

#include <dragonx/audio/io/plugins/mp3/Mp3AudioReader.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::audio::io::plugins::mp3;
Import dragon::util::logging;

const Type* Mp3AudioReader::TYPE = TypeOf<Mp3AudioReader>();
static Logger* logger = Logger::getLogger(Mp3AudioReader::TYPE, ERROR);

Mp3AudioReader::Mp3AudioReader() {

}

Mp3AudioReader::~Mp3AudioReader() {

}

void cleanup(mpg123_handle *mh) {
    /* It's really to late for error checks here;-) */
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
}

typedef struct _InputStreamFile {
    InputStream* input;
    long current;
} InputStreamFile;

/* Read callback needs nothing special. */
ssize_t inputstream_read(int handle, void *buf, size_t count) {
    InputStreamFile* isf = (InputStreamFile*)handle;
    InputStream* input = isf->input;

    int read = input->read((byte*)buf, count);
    isf->current += read;
    return read;
}

/* Seek callback needs protection from too big offsets. */
off_t inputstream_lseek(int handle, off_t offset, int whence) {
    InputStreamFile* isf = (InputStreamFile*)handle;
    InputStream* input = isf->input;

    int skip = offset - isf->current;
    input->skip(skip);
    return skip;    
}

AudioClip* Mp3AudioReader::read(const InputStream* input) const throw(IOException*) {
    mpg123_handle *mh = NULL;
    unsigned char* buffer = NULL;
    size_t buffer_size = 0;
    size_t done = 0;
    int  channels = 0, encoding = 0;
    long rate = 0;
    int  err  = MPG123_OK;
    off_t samples = 0;

    err = mpg123_init();
    if(err != MPG123_OK || (mh = mpg123_new(NULL, &err)) == NULL) {
        cleanup(mh);

        String* msg = String::format("Basic setup goes wrong: %s", mpg123_plain_strerror(err));
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    mpg123_param(mh, MPG123_ADD_FLAGS, MPG123_FORCE_FLOAT, 0.);

    InputStreamFile isf;
    isf.input = const_cast<InputStream*>(input);
    isf.current = 0;

    mpg123_replace_reader(mh, inputstream_read, inputstream_lseek);

    if(mpg123_open_handle(mh, &isf) != MPG123_OK
        || mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK ) {
        cleanup(mh);
        
        String* msg = String::format("Trouble with mpg123: %s\n", mpg123_strerror(mh));
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    /* Signed 16 is the default output format anyways; it would actually by only different if we forced it.
       So this check is here just for this explanation. */
    if(encoding != MPG123_ENC_SIGNED_16 && encoding != MPG123_ENC_FLOAT_32) { 
        cleanup(mh);

        String* msg = String::format("Bad encoding: 0x%x!\n", encoding);
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    /* Ensure that this output format will not change (it could, when we allow it). */
    mpg123_format_none(mh);
    mpg123_format(mh, rate, channels, encoding);

    AudioFormat* fmt = new AudioFormat();
    fmt->setSampleRate(rate);
    fmt->setChannels(channels);

    AudioClip* clip = new AudioClip(fmt);

    return clip;
}