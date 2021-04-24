#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;

void menu_ask(directory * dir, string name){
    string dir_printout;
    if(name == NULL){
        name = "root >\0";
    }
    dir_printout = malloc(300);
    strcpy(dir_printout, name);
    dir_printout[strlen(name)] = '\0';
    
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