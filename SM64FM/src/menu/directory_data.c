#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;


//GAME EDIT OPTIONS
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
            menu_edit_level_coin,
            NULL
        },
        {
            "Back",
            NULL,
            NULL
        }
    }

};


//MENU OPTIONS
const directory edit_menu_save = {
NULL,
    4,
    {
        {
            "Edit Coin Score Ages",
            menu_coin_age_edit,
            NULL
        },
        {
            "Edit Sound Type",
            menu_choose_sound,
            NULL
        },
        {
            "Edit Langage \033[0;31m(NON - U.S. VERSIONS)\033[0m",
            menu_choose_lang,
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

