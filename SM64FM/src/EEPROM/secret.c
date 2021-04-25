#include "EEPROM.h"
#include "EEPROM_Defines.h"
#include "../util/bitop/bitop.h"

extern EEPROM * eeprom;



uint8 local___name_to_index(string name){
    for(uint8 i =0; i < STR_SECRET_SIZE; i++){
        if(strstr(name, str_secret[i].name) == name){
            return i;
        }
    }
    printf("ERROR: \"%s\" Not a reconized star name!\n", name);
    return -1;
}



//Sets the value for the secret star
void set_secret(uint8 index, uint8 bit, bool new_val){
  if(index == 3){
    set_bit8(&eeprom->game_saves[*current_save][0].CastleSecretStar[index], bit, new_val);
  }
  eeprom->game_saves[*current_save][0].CastleSecretStar[index] = new_val;
}

//Get the value of the castle secret star from the given index
bool get_secret(uint8 index, uint8 bit){
  if(index == 3){
    return get_bit8(eeprom->game_saves[*current_save][0].CastleSecretStar[index], bit);
  }
  return eeprom->game_saves[*current_save][0].CastleSecretStar[index];
}

//Get the value of the castle secret star from the given name
bool get_secret_name(string name){
  uint8 val = local___name_to_index(name);
  if(val == 2){
    return get_secret(val, 1);
  }
  return get_secret(val,0);
}

//Set the castle secret star from the given name
void set_secret_name(string name, uint8 val){
  uint8 index = local___name_to_index(name);
  if(index == 2){
    set_secret(index, 1, val);
  }
  set_secret(index, 0, val);
}