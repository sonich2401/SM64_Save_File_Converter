#include "EEPROM.h"
#include "EEPROM_Defines.h"

uint8 flags_h_str_to_in(string name){
    for(uint8 i =0; i < STR_FLAGS_SIZE; i++){
        if(strstr(name, str_flags[i].name) == name){
            return i;
        }
    }
    printf("ERROR: \"%s\" Not a reconized flag name!\n", name);
    return -1;
}

//Gets the value of a flag from a given name
bool get_flag_name(string name){
    return get_flag_index(flags_h_str_to_in(name));
}

//Gets the value of a flag from a given index
bool get_flag_index(uint8 index){
    return (*((unsigned char*)eeprom + str_flags[index].byte_offset) & (1 << str_flags[index].bit_offset)) >> str_flags[index].bit_offset;
}

//Sets the value of a flag from a given name
void set_flag_name(string name, bool val){
    set_flag_index(flags_h_str_to_in(name), val);
}

//Sets the value of a flag from a given index
void set_flag_index(uint8 index, bool val){
    *((unsigned char*)eeprom + str_flags[index].byte_offset) &= (val << str_flags[index].bit_offset);
}