#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;



const directory edit_game_save = {
    NULL,
    4,
    {
        {
            "Edit Cap Data",
            menu_edit_cap_data,
            NULL
        },
        {
            "Edit Level Data",
            menu_edit_star,
            NULL
        },
        {
            "Edit Coin Scores",
            NULL,
            NULL
        },
        {
            "Back",
            NULL,
            NULL
        }
    }

};



const directory root = {
    NULL,
    4,
    {
        {
            "Edit Game Save",
            NULL,
            (directory*)&edit_game_save
        },
        {
            "Edit Menu Save",
            NULL,
            (directory*)&edit_menu_save
        },
        {
            "Edit Game Flags",
            NULL,
            (directory*)&edit_game_flags
        },
        {
            "Exit",
            NULL,
            NULL
        }
    }
};
