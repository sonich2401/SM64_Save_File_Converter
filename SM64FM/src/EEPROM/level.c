#include "EEPROM.h"
#include "EEPROM_Defines.h"
#include "../util/bitop/bitop.h"

uint8 level_h_str_to_in(string name){
    for(uint8 i =0; i < STR_FLAGS_SIZE; i++){
        if(strstr(name, str_courses[i].name) == name){
            return i;
        }
    }
    printf("ERROR: \"%s\" Not a reconized course name!\n", name);
    return -1;
}

//Get a star value from a given star index
bool get_star_value(uint8 index, uint8 star){
    return get_bit8(eeprom->game_saves[*current_save][0].CourseDat[index], star);
}

//Get star based on course name
bool get_star_value_name(string name, uint8 star){
    return get_star_value(level_h_str_to_in(name), star);
}

//Set a star value from a given star index
void set_star_value(uint8 index, uint8 star, bool val){
    set_bit8(&eeprom->game_saves[*current_save][0].CourseDat[index], star, val);
}

//Set star based on course name
void set_star_value_name(string name, uint8 star, bool val){
    set_star_value(level_h_str_to_in(name), star, val);
}