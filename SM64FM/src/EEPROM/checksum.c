#include "EEPROM.h"

//Calculate the checksum of a savefile or menu save, 0 = save, 1 = menu
uint16 calc_checksum(void * dat, bool type){
    uint16 max = sizeof(Save) * !type + sizeof(MenuSave) * type;
    uint16 ret=0;

    #ifdef _WIN32
    for(uint8 * buffer = dat; ((char*)buffer) - dat < max - sizeof(uint16); buffer++){ //- uint16 because we dont want to read the checksum
        ret += *buffer;
    }
    #else
    for(uint8 * buffer = dat; ((void*)buffer) - dat < max - sizeof(uint16); buffer++){ //- uint16 because we dont want to read the checksum
        ret += *buffer;
    }
    #endif


    return ret;
}

void set_checksum(void * dat, bool type){
    uint16 max = sizeof(Save) * !type + sizeof(MenuSave) * type;
    char * _dat = dat;
    _dat += (max - sizeof(uint16));
    *(uint16*)_dat = calc_checksum(dat, type);
}