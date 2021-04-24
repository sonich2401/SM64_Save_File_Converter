#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;


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



void menu_edit_level_coin(){

    int8 choice = menu_choose_star();
    system(OS_CLEAR);
    printf("Please enter new coin value (prevoius = ");
    colstr(printf("%i", get_coins_index(choice)),T_YELLOW);
    printf(")\n");

    printf("New value: ");
    printf(T_YELLOW); //set the text yellow ;)

    uint8 choice1;
    scanf("%hhi", &choice1);

    set_coins_index(choice, choice1);

    printf(T_RESET);
}



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



int8 menu_choose_star();

void menu_edit_star(){
    int8 choice = menu_choose_star();
    if(choice == -1){return;}
    menu_edit_course(choice);
}

int8 menu_choose_star(){
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
                colstr(printf("[#]"), T_RED);
                colstr(printf(" %i\n", get_coins_index(i)),T_YELLOW);
                continue;
            }
            printf("[ ]");
            colstr(printf(" %i\n", get_coins_index(i)),T_YELLOW);
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
            return -1;
        }
        return (int8)(choice - 1);
    }//END OF WHILE
}
