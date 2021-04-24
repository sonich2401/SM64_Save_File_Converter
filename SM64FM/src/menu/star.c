#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;

void menu_edit_star(){
    while(1){
        printf("Which course to Edit?\n");
        for(uint8 i = 0; i < 15; i++){
            int chars_printed = 0;
            chars_printed = printf("%i. %s ", i + 1, str_courses[i].name);
            for(uint8 i1 = 0; i1 < 27 - chars_printed; i1++){ //Make sure everything is printed on the same collom
                printf(" ");
            }
            for(uint8 i1 = 0; i1 < 7; i1++){
                if(get_bit8(eeprom->game_saves[*current_save][0].CourseDat[i], i1)){
                    colstr(printf("* "),T_YELLOW);
                }else{
                    printf("* ");
                }
            }
            if(!get_bit8(eeprom->game_saves[*current_save][0].CourseDat[i], 7)){
                colstr(printf("[#]\n"), T_RED);
                continue;
            }
            printf("[ ]\n");
        }
    
        uint8 choice;
        colstr(printf("\nYour Choice (Enter 0 to leave): "),T_CYAN);
        scanf("%hhi", &choice);
        if(choice > 15){ //ERROR CHECKING
            system(OS_CLEAR);
            colstr(printf("ERROR: "), T_RED);
            printf("INVALID COURSE!\nPress Enter to continue...\n");
            system(OS_PAUSE);
            system(OS_CLEAR);
            continue;
        }
        if(choice == 0){ //Exit the menu
            break;
        }
        menu_edit_course(choice-1);
        break;
    }//END OF WHILE
}
