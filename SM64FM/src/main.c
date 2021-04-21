#include <stdlib.h>
#include <stdio.h>
#include <typedefs.h>

#include "menu/option_decode.h"
#include "util/load_file/load_bin.h"
#include "EEPROM/EEPROM.h"
#include "menu/menu_choice.h"



int main(int argc, string argv[]){
    option_struct * options = option_decode(argc, argv);

    eeprom = malloc(sizeof(EEPROM));
    current_save = malloc(1); //uint8
    *current_save = 0;

    unsigned char * infile = load_bin(options->in_path);
    *eeprom = init_EEPROM(infile);
    free(infile);


    menu_ask(&root, NULL);
    
    
    for(uint8 backup = 0; backup < 2; backup++){
        for(uint8 sav = 0; sav < 4; sav++){
            set_checksum(&eeprom->game_saves[sav][backup], 0);
        }
        set_checksum(&eeprom->menu_saves[backup], 1);
    }
    
    write_bin(options->out_path,(unsigned char*)eeprom, 512);

    return 0;
}
