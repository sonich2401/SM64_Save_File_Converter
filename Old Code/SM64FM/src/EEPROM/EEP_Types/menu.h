#include "../typedefs.h"

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