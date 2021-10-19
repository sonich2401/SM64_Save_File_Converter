/*RenDev#2616 SM64SFM
    Copyright (C) 2021 RenDev

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
    Permission is also granted to not credit the author in any way as long as you do not take credit
    for this piece of software.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/

#include "Music.h"
#define CHANNEL_COUNT 2
#define SAMPLE_FORMAT ma_format_f32
#define SAMPLE_RATE 48000

Music* mixer;

ma_uint32 read_and_mix_pcm_frames_f32(ma_decoder* pDecoder, float* pOutputF32, float gain, ma_uint32 frameCount)
{
    /*
    The way mixing works is that we just read into a temporary buffer, then take the contents of that buffer and mix it with the
    contents of the output buffer by simply adding the samples together. You could also clip the samples to -1..+1, but I'm not
    doing that in this example.
    */
    #define TEMP_BUFF_SIZE__MIXER 4069
    float temp[TEMP_BUFF_SIZE__MIXER];
    ma_uint32 tempCapInFrames = TEMP_BUFF_SIZE__MIXER / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frameCount) {
        ma_uint32 iSample;
        ma_uint32 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;
        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        framesReadThisIteration = (ma_uint32)ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration);
        if (framesReadThisIteration == 0) {
            break;
        }

        /* Mix the frames together. */
       
        for (iSample = 0; iSample < framesReadThisIteration*CHANNEL_COUNT; ++iSample) {
            //pOutputF32[totalFramesRead*CHANNEL_COUNT + iSample] += temp[iSample];
            pOutputF32[totalFramesRead*CHANNEL_COUNT + iSample] += temp[iSample] *  gain;
        }

        totalFramesRead += framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration) {
            break;  /* Reached EOF. */
        }
    }
    
    return totalFramesRead;
}

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    float* pOutputF32 = (float*)pOutput;
    std::vector<int> to_delete;
    for (int iDecoder = 0; iDecoder < mixer->decoders.size(); iDecoder++) {
        ma_uint32 framesRead = read_and_mix_pcm_frames_f32(&mixer->decoders[iDecoder]->file, pOutputF32, mixer->decoders[iDecoder]->gain, frameCount);
        if (framesRead < frameCount) {
            if(!mixer->decoders[iDecoder]->loops){
                mixer->decoders[iDecoder]->end = true;
                to_delete.push_back(iDecoder);
            }
            else
                mixer->decoders[iDecoder]->GoToStart();
        }
    }

    for(auto& del : to_delete){
        delete mixer->decoders[del];
        mixer->decoders.erase(mixer->decoders.begin() + del);
    }

    (void)pInput;
}


Music::Music(){
    mixer= this;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = NULL;

    ma_device_init(NULL, &deviceConfig, &device);
    ma_device_start(&device);

    decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
    
}

void Music::AddFile(std::string file_path, unsigned char gain, bool loop){
    for(auto& dec : decoders){
        if(dec->fp == file_path){
            dec->GoToStart();
            return;
        }
    }
    decoders.push_back(new MusicFile(file_path, gain, loop));
}

void Music::Clear(){
    for(auto& dec : this->decoders){
        delete dec;
    }
    decoders.clear();
}

Music::~Music(){
    ma_device_uninit(&device);
    for(auto& dec : this->decoders){
        delete dec;
    }
}








MusicFile::MusicFile(std::string fn, unsigned char _gain, bool loop){
    ma_decoder_init_file(fn.c_str(), (const ma_decoder_config*)&mixer->decoderConfig, &file);
    this->loops = loop;
    this->end = false;
    this->paused = false;
    this->fp = fn;
    this->gain = float(_gain)/255;
}

void MusicFile::TogglePause(){
    this->paused = !this->paused;
}

void MusicFile::Pause(){
    this->paused = true;
}

void MusicFile::Play(){
    this->paused = false;
}

void MusicFile::GoToStart(){
   ma_decoder_seek_to_pcm_frame(&file, 0);
}

void MusicFile::SeekTo(float time){
    unsigned long long int frame = ((unsigned long long int)(SAMPLE_RATE * time));
    ma_decoder_seek_to_pcm_frame(&file, frame);
}

MusicFile::~MusicFile(){
    ma_decoder_uninit(&this->file);
}