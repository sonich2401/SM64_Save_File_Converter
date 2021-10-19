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
#pragma once
#include "miniaudio.h"
#include <string>

class MusicFile{
    public:
        MusicFile(std::string file_name, unsigned char gain, bool loops);

    public:
        ma_decoder file;
        std::string fp;

        struct{
            bool loops : 1;
            bool end : 1;
            bool paused : 1;
        };
        float gain;

    public:
        void TogglePause();

        void Pause();

        void Play();

        void GoToStart();

        void SeekTo(float time);
    public:
        ~MusicFile();
};