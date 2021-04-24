#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;

void menu_edit_cap_data(){
    const string options[] =
    {
        "Level",
        "Area",
        "X",
        "Y",
        "Z",
        "Stolen by"
    };
    uint8 options_size = 6;
    string format = "%i. Cap %s (prev: %i) = "; 

    //TODO: Add stolen by option NOW: sizeof(options) - 1 SHOULD: sizeof(options)
    for(uint8 i = 0; i < options_size - 1; i++){
    
        //INPUT
        if(i < 2){
            uint8 * change_byte = &eeprom->game_saves[*current_save][0].capLevel;
            if(i == 1)
                change_byte = &eeprom->game_saves[*current_save][0].capArea;
            printf(format, i + 1, options[i], *change_byte);
            scanf("%hhi", change_byte);
            continue;
        }
        if(i < 2 + 4){
            if(i == 5){
                printf("NOT IMPLEMENTED YET\n");
                continue;
            }
            printf(format, i + 1, options[i], eeprom->game_saves[*current_save][0].capPos[i - 2]);
            
            int16 choice;
            scanf("%hi", &choice);
            eeprom->game_saves[*current_save][0].capPos[i - 2] = choice;
            printf("\r");
            continue;
        }

    }
}