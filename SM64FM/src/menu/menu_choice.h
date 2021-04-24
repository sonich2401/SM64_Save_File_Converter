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


const directory root;
const directory edit_game_save;
const directory edit_menu_save;
const directory edit_game_flags;
const directory halt; 

void menu_ask(directory * dir, string name);

const directory root;


void menu_edit_cap_data();


void menu_edit_course(uint8 course);


void menu_edit_star();



const directory edit_game_save;