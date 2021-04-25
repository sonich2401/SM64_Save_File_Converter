#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <typedefs.h>

#include "empty_file/Empty.h"

struct flag;
typedef struct {
	uint32 CoinScoreAge[4]; //uint8 [16]
	uint8 soundMode;
	uint8 Language;
	uint8 fillerPadding[10];
	uint16 magic;
	uint16 checkSum;
}MenuSave;

typedef struct  {
	bool CannonOpen;
	bool CoinStarObtained;
	bool star[6];
}starCourses;

typedef struct {
	uint8 capLevel;
	uint8 capArea;
	int16 capPos[3];

    uint32 GameFlags; //C Secrets, Flags[3]

	uint8 CourseDat[25];
  uint8 CastleSecretStar[10];
	uint8 coinCourses[15];
	uint16 magic;
	uint16 checkSum;
}Save;


typedef struct{
    Save game_saves[4][2];
    MenuSave menu_saves[2];
}EEPROM;

#ifndef GLOBAL_EEPROM
#define GLOBAL_EEPROM
extern EEPROM * eeprom; //Check EEPROM.c for external symbol
extern uint8 * current_save;//Check EEPROM.c for external symbol
#endif


//Detects the endianess of the EEPROM
uint8 detect_endian();

//Load a EEPROM from a loaded file buffer. Set buffer to NULL to load a default save
EEPROM init_EEPROM(unsigned char * buffer);




//Checksum.c

//Calculate the checksum of a savefile or menu save, 0 = save, 1 = menu
uint16 calc_checksum(void * dat, bool type);

void set_checksum(void * dat, bool type);



//flags.c

//Gets the value of a flag from a given name
bool get_flag_name(string name);

//Gets the value of a flag from a given index
bool get_flag_index(uint8 index);

//Sets the value of a flag from a given name
void set_flag_name(string name, bool val);

//Sets the value of a flag from a given index
void set_flag_index(uint8 index, bool val);




//level.c

//Get a star value from a given star index
bool get_star_value(uint8 index, uint8 star);

//Get star based on course name
bool get_star_value_name(string name, uint8 star);

//Set a star value from a given star index
void set_star_value(uint8 index, uint8 star, bool val);

//Set star based on course name
void set_star_value_name(string name, uint8 star, bool val);



//capdata.c

//Sets the cap data. 1 = Snowman, 2 = Brid, 3= Monkey
void set_capdata(uint8 level, uint8 area, int16 x, int16 y, int16 z, uint8 type);



//coins.c

//Get the coin score for a level from a given index
uint8 get_coins_index(uint8 index);

//Get the coin score for a level from a given name
uint8 get_coins_name(string name);

//Set the coin score for a level from a given index
void set_coins_index(uint8 index, uint8 val);

//Set the coin score for a level from a given name
void set_coins_name(string name, uint8 val);

//Coin ages

//Get the coin score age for a level from a given index
uint8 get_coins_age_index(uint8 index);

//Get the coin score age for a level from a given name
uint8 get_coins_age_name(string name);

//Set the coin score age for a level from a given index
void set_coins_age_index(uint8 index, uint8 val);

//Set the coin score age for a level from a given name
void set_coins_age_name(string name, uint8 val);






//menu.c

//Gets the sound setting for the menu
uint8 get_sound_setting(uint8 menu);

//Sets the sound setting for the menu
void set_sound_setting(uint8 menu, uint8 val);

//Get the selected language setting
uint8 get_language(uint8 menu);

//Set the selected language setting
void set_language(uint8 menu, uint8 val);


//secret.c 

//Get the value of the castle secret star from the given index
bool get_secret(uint8 index, uint8 bit);

//Get the value of the castle secret star from the given name
bool get_secret_name(string name);

//Set the castle secret star from the given index
void set_secret(uint8 index, uint8 val);

//Set the castle secret star from the given name
void set_secret_name(string name, uint8 val);