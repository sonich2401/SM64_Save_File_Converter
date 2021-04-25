#pragma once
#include <typedefs.h>
#include <stdlib.h>
#include <stdio.h>
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"
#include "../util/bitop/bitop.h"


struct directory;

typedef struct{
    string name;
    void (*func)(void);
    struct directory * link;
}menu_option;

typedef struct {
    struct directory * last;
    uint8 options_size;
    menu_option options[];
}directory;


extern const directory root;
extern const directory edit_game_save;
extern const directory edit_menu_save;
extern const directory edit_game_flags;
const directory halt; 



void menu_ask(directory * dir, string name);


//GAME DATA
void menu_edit_cap_data();

void menu_edit_course(uint8 course);

void menu_edit_star();

void menu_print_courses(); //VERY USEFUL FUNCTION

int8 menu_choose_star();

void menu_edit_level_coin();

void menu_edit_secrets();

//MENU DATA

void menu_choose_lang();

void menu_choose_sound();

void menu_coin_age_edit();


//GAME FLAGS DATA

void menu_set_flags();

void menu_set_door_flags();

void menu_set_progress_flags();

void menu_set_cap_flags();