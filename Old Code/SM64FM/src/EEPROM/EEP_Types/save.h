#include "../typedefs.h"

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