#include <typedefs.h>
#include <stdlib.h>
#include <stdio.h>
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

void menu_ask(directory * dir, string name){
    string dir_printout;
    if(name == NULL){
        name = "root >";
    }
    dir_printout = malloc(300);
    strcpy(dir_printout, name);
    
    while(true){
        //UI
        system(OS_CLEAR);
        printf("Directory: %s\n", dir_printout);
        printf("Please Choose a Option:\n");
        for(uint8 i =0; i < dir->options_size; i++){
            printf("\t%i. %s\n", i + 1, dir->options[i].name);
        }

        //INPUT
        uint8 choice;
        scanf("%hhi", &choice);

        //INPUT DECODING
        if(dir->options[choice-1].link == NULL){
            if(dir->options[choice-1].func == NULL)//back
                return;
            system(OS_CLEAR);
            dir->options[choice-1].func();
            continue; //Dont go into a new directory
        }

        //ENTER A NEW DIR
        //Copy the orignal dir name and add the next dir to that name
        string new_str = malloc(300); 
        memcpy(new_str, dir_printout, strlen(dir_printout)); //cpy string
        strcat(new_str, dir->options[choice-1].name); //append the name
        strcat(new_str, " >"); //append the arrow
        menu_ask(dir->options[choice-1].link,new_str); //Branch

        free(new_str);//Cleanup
    }//END OF WHILE
    free(dir_printout);
}

const directory root = {
    NULL,
    4,
    {
        {
            "Edit Game Save",
            NULL,
            (directory*)&edit_game_save
        },
        {
            "Edit Menu Save",
            NULL,
            (directory*)&edit_menu_save
        },
        {
            "Edit Game Flags",
            NULL,
            (directory*)&edit_game_flags
        },
        {
            "Exit",
            NULL,
            NULL
        }
    }
};


void menu_edit_cap_data(){
    const string options[] =
    {
        "Level",
        "Area",
        "X",
        "Y",
        "Z",
        "Stolen by"
    };
    uint8 options_size = 6;
    string format = "%i. Cap %s (prev: %i) = "; 

    //TODO: Add stolen by option NOW: sizeof(options) - 1 SHOULD: sizeof(options)
    for(uint8 i = 0; i < options_size - 1; i++){
    
        //INPUT
        if(i < 2){
            uint8 * change_byte = &eeprom->game_saves[*current_save][0].capLevel;
            if(i == 1)
                change_byte = &eeprom->game_saves[*current_save][0].capArea;
            printf(format, i + 1, options[i], *change_byte);
            scanf("%hhi", change_byte);
            continue;
        }
        if(i < 2 + 4){
            if(i == 5){
                printf("NOT IMPLEMENTED YET\n");
                continue;
            }
            printf(format, i + 1, options[i], eeprom->game_saves[*current_save][0].capPos[i - 2]);
            
            int16 choice;
            scanf("%hi", &choice);
            eeprom->game_saves[*current_save][0].capPos[i - 2] = choice;
            printf("\r");
            continue;
        }

    }
}

void menu_edit_star(){
    printf("Which course to Edit?\n");
    for(uint8 i = 0; i < 15; i++){
        printf("%i. %s ", i + 1, str_courses[i].name);
        for(uint8 i1 = 0; i1 < 7; i1++){
            if(get_bit8(eeprom->game_saves[*current_save][0].CourseDat[i], i1)){
                printf("*");
            }else{
                printf("o");
            }
        }
        if(get_bit8(eeprom->game_saves[*current_save][0].CourseDat[i], 7)){
            printf("[#]\n");
            continue;
        }
        printf("[ ]\n");
    }
    while(1){}
}

const directory edit_game_save = {
    NULL,
    4,
    {
        {
            "Edit Cap Data",
            menu_edit_cap_data,
            NULL
        },
        {
            "Edit Level Data",
            menu_edit_star,
            NULL
        },
        {
            "Edit Coin Scores",
            NULL,
            NULL
        },
        {
            "Back",
            NULL,
            NULL
        }
    }

};
