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

#ifndef SAVE_H
#define SAVE_H

//Struct includes
    #include "cap_data.h"
    #include "level.h"
    #include "coin_data.h"
    #include "game_flags.h"
    #include "magic.h"
    #include "secret_stars.h"
//

union Save
{
    struct Var{
        LostCapData cap_data; //UNUSED

        union Flags flags; //Progression / Star Flags
        
        union Level_Data level_data; //All normal Levels
        
        union CastleSecretStars castle_secret_stars; //Secret stars

        union CoinScoreData coin_score_data; //used to keep track of your coin count


        
        //Save Validation
        union Magic magic;

        uint16 checksum;
    }GoodName;

    uint8 array[0x38];

};


#endif