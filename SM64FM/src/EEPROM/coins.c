#include "EEPROM.h"

//Get the coin score for a level from a given index
uint8 get_coins_index(uint8 index){
    return eeprom->game_saves[*current_save][0].coinCourses[index];
}

//Get the coin score for a level from a given name
uint8 get_coins_name(string name);

//Set the coin score for a level from a given index
void set_coins_index(uint8 index, uint8 val){
    eeprom->game_saves[*current_save][0].coinCourses[index] = val;
}

//Set the coin score for a level from a given name
void set_coins_name(string name, uint8 val);

//Coin ages

//Get the coin score age for a level from a given index
uint8 get_coins_age_index(uint8 index){
    return eeprom->menu_saves[0].CoinScoreAge[index];
}

//Get the coin score age for a level from a given name
uint8 get_coins_age_name(string name);

//Set the coin score age for a level from a given index
void set_coins_age_index(uint8 index, uint8 val){
    eeprom->menu_saves[0].CoinScoreAge[index] = val;
}

//Set the coin score age for a level from a given name
void set_coins_age_name(string name, uint8 val);
