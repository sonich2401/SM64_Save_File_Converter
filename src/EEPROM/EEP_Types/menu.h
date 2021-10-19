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
#include <_typedefs.h>

#ifndef MENU_H
#define MENU_H

//Struct includes
    #include "magic.h"
    #include "coin_data.h"
//

typedef enum {
    STERO,
    MONO,
    HEADSET
}SOUND_SETTING;

typedef enum {
    ENGLISH,
    FRENCH,
    GERMAN
}LANGUAGE_SETTING;

union Menu{
    struct MenuNamed{
        union CoinAgeData coin_ages;
        
        uint8 sound_mode; //SEE 'SOUND_SETTING'
        uint8 Language;
        uint8 fillerPadding[10]; //UNUSED
        
        //Signature
        union Magic magic;
        uint16 checkSum;
    }GoodName;

    uint8 array[0x20];
};

#endif