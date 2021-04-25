#include "EEPROM.h"

extern EEPROM * eeprom;


const string secret_names[] = {
  "Bowser 1 Red Coins",
  "Bowser 2 Red Coins",
  "Bowser 3 Red Coins",
  #if (OS == Linux)
    "Princess Secret Slide " T_YELLOW "[!]" T_RESET " Box",
  #else
    "Princess Secret Slide [!] Box",
  #endif

  "Princess Secret Slide 20 sec Speedrun",
  "Wing Cap Red Coins",
  "Metal Cap Red Coins",
  "Vanish Cap Red Coins",
  "Mario Wings Over the Rainbow",
  "Princess Secret Aquarium"
};



uint8 local___name_to_index(string name){

}



//Sets the value for the secret star
void set_secret(uint8 index, uint8 bit, bool new_val){
  if(index == 3){
    set_bit8(eeprom->game_saves[*cur_save][0].CastleSecretStar[index], bit, new_val);
  }
  eeprom->game_saves[*cur_save][0].CastleSecretStar[index] = new_val;
}

//Get the value of the castle secret star from the given index
bool get_secret(uint8 index, uint8 bit){
  if(index == 3){
    return get_bit8(eeprom->game_saves[*cur_save][0].CastleSecretStar[index], bit);
  }
  return eeprom->game_saves[*cur_save][0].CastleSecretStar[index];
}

//Get the value of the castle secret star from the given name
bool get_secret_name(string name);

//Set the castle secret star from the given name
void set_secret_name(string name, uint8 val);