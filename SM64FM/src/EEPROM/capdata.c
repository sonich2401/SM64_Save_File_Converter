#include "EEPROM.h"

//Sets the cap data. 1 = Snowman, 2 = Brid, 3= Monkey
void set_capdata(uint8 level, uint8 area, int16 x, int16 y, int16 z, uint8 type){
    eeprom->game_saves[*current_save][0].capArea = area;
    eeprom->game_saves[*current_save][0].capLevel = level;
    
    eeprom->game_saves[*current_save][0].capPos[0] = x;
    eeprom->game_saves[*current_save][0].capPos[1] = y;
    eeprom->game_saves[*current_save][0].capPos[2] = z;

    set_flag_name("cap_stolen", type);
}

