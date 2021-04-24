#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;

void menu_edit_course(uint8 course){
    string * act_names = str_courses[course].acts;
    const string format = "%i. %s\n";
    while(1){
        system(OS_CLEAR);
        for(uint8 i = 0; i < 7; i++){
            string act_name = act_names[i];
            if(get_bit8(eeprom->game_saves[*current_save][0].CourseDat[course], i)){
                colstr(printf(format, i+1, act_name), T_YELLOW);
                continue;
            }
            printf(format, i+1, act_name);
        }


        uint8 choice;
        colstr(printf("\nYour Choice (Enter 0 to leave): "),T_CYAN);
        scanf("%hhi", &choice);
        printf("\n");
        if(choice > 7){ //ERROR CHECKING
            system(OS_CLEAR);
            colstr(printf("ERROR: "), T_RED);
            printf("INVALID STAR!\nPress Enter to continue...\n");
            system(OS_PAUSE);
            system(OS_CLEAR);
            continue;
        }
        if(choice != 0){
            bool old_val = get_bit8(eeprom->game_saves[*current_save][0].CourseDat[course], choice-1);
            set_bit8(&eeprom->game_saves[*current_save][0].CourseDat[course], choice-1,!old_val);//toggle bit
            continue;
        }
        return;
    }
}