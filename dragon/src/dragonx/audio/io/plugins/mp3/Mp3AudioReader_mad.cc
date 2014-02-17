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
#include <mad.h>

#include <dragon/util/logging/Logger.h>
#include <dragon/io/ByteArrayOutputStream.h>
#include <dragonx/audio/io/plugins/mp3/Mp3AudioReader.h>

Import dragon::io;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::mp3;

const Type* Mp3AudioReader::TYPE = TypeOf<Mp3AudioReader>();
static Logger* logger = Logger::getLogger(Mp3AudioReader::TYPE, ERROR);

Mp3AudioReader::Mp3AudioReader() {

}

Mp3AudioReader::~Mp3AudioReader() {

}

#define BUFSIZE 8192

typedef struct _MadDecodeContext {
    InputStream* input;
    unsigned int fpos; /*current position*/
    unsigned char fbuf[BUFSIZE]; /*buffer*/
    unsigned int fbsize; /*indeed size of buffer*/

    OutputStream* output;
    AudioFormat* format;
    Exception* exception;
} MadDecodeContext;

/*
 * This is the input callback. The purpose of this callback is to (re)fill
 * the stream buffer which is to be decoded. In this example, an entire file
 * has been mapped into memory, so we just call mad_stream_buffer() with the
 * address and length of the mapping. When this callback is called a second
 * time, we are finished decoding.
 */
static enum mad_flow input_callback(void *data, struct mad_stream *stream) {
    MadDecodeContext* ctx = (MadDecodeContext*)data;
    InputStream* input = (InputStream*)ctx->input;;

    enum mad_flow ret_code;
    int unproc_data_size; /*the unprocessed data's size*/
    int copy_size;

    unproc_data_size = stream->bufend - stream->next_frame;
    memcpy(ctx->fbuf, ctx->fbuf + ctx->fbsize - unproc_data_size, unproc_data_size);
    copy_size = BUFSIZE - unproc_data_size;

    int read = input->read((byte*)(ctx->fbuf + unproc_data_size), copy_size);

    if (read > 0) {
        ctx->fbsize = unproc_data_size + read;
        ctx->fpos += read;

        /*Hand off the buffer to the mp3 input stream*/
        mad_stream_buffer(stream, ctx->fbuf, ctx->fbsize);

        ret_code = MAD_FLOW_CONTINUE;
    } else {
        ret_code = MAD_FLOW_STOP;
    }
    
    return ret_code;
}

/*
 * The following utility routine performs simple rounding, clipping, and
 * scaling of MAD's high-resolution samples down to 16 bits. It does not
 * perform any dithering or noise shaping, which would be recommended to
 * obtain any exceptional audio quality. It is therefore not recommended to
 * use this routine if high-quality output is desired.
 */
static inline signed int scale(mad_fixed_t sample) {
  /* round */
  sample += (1L << (MAD_F_FRACBITS - 16));

  /* clip */
  if (sample >= MAD_F_ONE)
      sample = MAD_F_ONE - 1;
  else if (sample < -MAD_F_ONE)
      sample = -MAD_F_ONE;

  /* quantize */
  return sample >> (MAD_F_FRACBITS + 1 - 16);
}

/*
 * This is the header callback function. It is called after each frame of
 * MPEG audio data has been completely decoded. The purpose of this callback
 * is to output (or play) the decoded PCM audio.
 */
static enum mad_flow header_callback(void *data, struct mad_header const *header) {
    MadDecodeContext* ctx = (MadDecodeContext*)data;
    AudioFormat* fmt = (AudioFormat*)ctx->format;

    fmt->setSampleRate(header->samplerate);

    if (header->mode == MAD_MODE_SINGLE_CHANNEL) {
        fmt->setChannels(1);
    } else if (header->mode == MAD_MODE_DUAL_CHANNEL) {
        fmt->setChannels(2);
    } else {
        return MAD_FLOW_BREAK;
    }

    return MAD_FLOW_CONTINUE;
}

/*
 * This is the output callback function. It is called after each frame of
 * MPEG audio data has been completely decoded. The purpose of this callback
 * is to output (or play) the decoded PCM audio.
 */
static enum mad_flow output_callback(void *data, struct mad_header const *header,
    struct mad_pcm *pcm)
{
    MadDecodeContext* ctx = (MadDecodeContext*)data;
    OutputStream* output = (OutputStream*)ctx->output;

    unsigned int nchannels, nsamples;
    mad_fixed_t const *left_ch, *right_ch;

    /* pcm->samplerate contains the sampling frequency */

    nchannels = pcm->channels;
    nsamples  = pcm->length;
    left_ch   = pcm->samples[0];
    right_ch  = pcm->samples[1];

    while (nsamples--) {
        signed int sample;

        /* output sample(s) in 16-bit signed little-endian PCM */
        sample = scale(*left_ch++);

        output->write((sample >> 0) & 0xff);
        output->write((sample >> 8) & 0xff);

        if (nchannels == 2) {
            sample = scale(*right_ch++);

            output->write((sample >> 0) & 0xff);
            output->write((sample >> 8) & 0xff);
        }
    }

    return MAD_FLOW_CONTINUE;
}

/*
 * This is the error callback function. It is called whenever a decoding
 * error occurs. The error is indicated by stream->error; the list of
 * possible MAD_ERROR_* errors can be found in the mad.h (or
 * libmad/stream.h) header file.
 */

static
enum mad_flow error_callback(void *data,
            struct mad_stream *stream,
            struct mad_frame *frame)
{
    MadDecodeContext* ctx = (MadDecodeContext*)data;

    String* msg = String::format("decoding error 0x%04x (%s)!", stream->error, mad_stream_errorstr(stream));
    logger->error(msg->toCString());
    IOException* e = new IOException(msg);
    SafeDelete(msg);

    ctx->exception = e;

    return MAD_FLOW_BREAK;
}


AudioClip* Mp3AudioReader::read(const InputStream* input) const throw(IOException*) {
    MadDecodeContext ctx;
    struct mad_decoder decoder;

    AudioClip* clip = new AudioClip();
    const AudioFormat* fmt = clip->getAudioFormat();
    ByteArrayOutputStream* baos = new ByteArrayOutputStream();

    /* initialize our private message structure */
    ctx.format = const_cast<AudioFormat*>(fmt);
    ctx.input  = const_cast<InputStream*>(input);
    ctx.output = baos;

    /* configure input, output, and error functions */

    mad_decoder_init(&decoder, &ctx,
           input_callback, header_callback, 0 /* filter */, output_callback,
           error_callback, 0 /* message */);

    /* start decoding */
    if (mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC) == -1) {
        //throw ctx.exception;
        throw new IOException("error in decode mp3!", ctx.exception);
    }

    Array<byte> data = baos->toByteArray();
    clip->setAudioData(data.raw(), data.size());
    SafeDelete(baos);

    /* release the decoder */
    mad_decoder_finish(&decoder);

    return clip;
}