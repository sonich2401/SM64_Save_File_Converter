#include "EEPROM.h"

//Gets the sound setting for the menu
uint8 get_sound_setting(uint8 menu){
    return eeprom->menu_saves[menu].soundMode;
}

//Get the selected language setting
uint8 get_language(uint8 menu){
    return eeprom->menu_saves[menu].Language;
}

//Sets the sound setting for the menu
void set_sound_setting(uint8 menu, uint8 val){
    eeprom->menu_saves[menu].soundMode = val;
}

//Set the selected language setting
void set_language(uint8 menu, uint8 val){
    eeprom->menu_saves[menu].Language = val;
}