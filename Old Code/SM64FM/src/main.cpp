#include <stdlib.h>
#include <stdio.h>
#include <typedefs.h>

#include "menu/option_decode.h"
#include "util/load_file/load_bin.h"
#include "EEPROM/EEPROM.h"
#include "menu/menu_choice.h"

#include "util/os/linux/escape_codes.h"

void exit_program(option_struct * options);



int main(int argc, cstring argv[]){
    option_struct * options = option_decode(argc, argv);

    EEPROM_Storage::get().orginal = (EEPROM*)malloc(sizeof(EEPROM));

    if(options->in_path == NULL) return 0;
    
    unsigned char * infile = load_bin(options->in_path);
    *EEPROM_Storage::get().orginal = init_EEPROM(infile);
    EEPROM_Storage::get().edited = (EEPROM*)memcpy(EEPROM_Storage::get().edited, EEPROM_Storage::get().orginal, 512);
    free(infile);


    menu_ask((directory*)&root, NULL);
    
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