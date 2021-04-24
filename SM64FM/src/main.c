#include <stdlib.h>
#include <stdio.h>
#include <typedefs.h>

#include "menu/option_decode.h"
#include "util/load_file/load_bin.h"
#include "EEPROM/EEPROM.h"
#include "menu/menu_choice.h"

#include "util/os/linux/escape_codes.h"

void exit_program(option_struct * options);



int main(int argc, string argv[]){
    option_struct * options = option_decode(argc, argv);

    eeprom = malloc(sizeof(EEPROM));
    current_save = malloc(1); //uint8
    *current_save = 0;

    if(options->in_path == NULL) return 0;
    
    unsigned char * infile = load_bin(options->in_path);
    *eeprom = init_EEPROM(infile);
    free(infile);
    

    if(options->backdoor){ //hackity hack hack?
        switch(options->b_type){
            case 0:
                return get_star_value(options->arg1, options->arg2);
                break;
            case 1:
                set_star_value(options->arg1, options->arg2, options->arg3);
            break;
            case 2:
                return get_coins_index(options->arg1);
            break;
            case 3:
                set_coins_index(options->arg1, options->arg2);
            break;
        }
        exit_program(options);
        return 0;
    }


    menu_ask(&root, NULL);
    
    
    exit_program(options);

    return 0;
}

void exit_program(option_struct * options){
    for(uint8 backup = 0; backup < 2; backup++){
        for(uint8 sav = 0; sav < 4; sav++){
            set_checksum(&eeprom->game_saves[sav][backup], 0);
        }
        set_checksum(&eeprom->menu_saves[backup], 1);
    }
    
    write_bin(options->out_path,(unsigned char*)eeprom, 512);
}