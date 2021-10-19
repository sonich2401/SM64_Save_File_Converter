#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"

extern EEPROM * eeprom;



void menu_choose_lang(){
 const string options[3] = {
        "English",
        "French",
        "German"
    };
    const string colors[3] = {
        T_GREEN,
        T_MAGENTA,
        T_YELLOW
    };

    while(true){
        printf("Please Choose a Option:\n");
        for(uint8 i = 0; i < 3; i++){
            printf("%i. ",i+1);
            printf("%s",colors[i]);
            printf("%s\n", options[i]);
            printf(T_RESET);
        }
        colstr(printf("Enter a new Language Setting (prev = %s): ", options[get_language(0)]),T_CYAN);
        uint8 choice;
        scanf("%hhi", &choice);

        if(choice <= 0 || choice >= 4){
            system(OS_CLEAR);
            colstr(printf("ERROR:\n"),T_RED);
            printf("Not a valid Language Mode!\n");
            printf("Press any key to continue ...\n");
            system(OS_PAUSE);
            system(OS_CLEAR);
            continue;
        }
        set_language(0, choice-1);
        return;
    }
}

void menu_choose_sound(){
    const string options[3] = {
        "Stereo",
        "Mono",
        "Headset"
    };
    const string colors[3] = {
        T_GREEN,
        T_MAGENTA,
        T_YELLOW
    };

    while(true){
        printf("Please Choose a Option:\n");
        for(uint8 i = 0; i < 3; i++){
            printf("%i. ",i+1);
            printf("%s",colors[i]);
            printf("%s\n", options[i]);
            printf(T_RESET);
        }
        colstr(printf("Enter a new Sound Setting (prev = %s): ", options[get_sound_setting(0)]),T_CYAN);
        uint8 choice;
        scanf("%hhi", &choice);

        if(choice <= 0 || choice >= 4){
            system(OS_CLEAR);
            colstr(printf("ERROR:\n"),T_RED);
            printf("Not a valid Sound Mode!\n");
            printf("Press any key to continue ...\n");
            system(OS_PAUSE);
            system(OS_CLEAR);
            continue;
        }
        set_sound_setting(0, choice-1);
        return;
    }

}

void menu_coin_age_edit(){
    printf("Please select a level to edit the coin age for\n");
    printf("Please remeber that this is ");
    colstr(printf("EXPERIMENTAL \n"),T_RED);

    printf("Press any key to continue ...\n");
    system(OS_PAUSE);

    int8 course = menu_choose_star();
    if(course == -1){return;}

    system(OS_CLEAR);
    printf("Coin age for %s, is %i\n", str_courses[course].name, get_coins_age_index(course));

    //Get input
    colstr(printf("\nPlease enter a new value: "),T_CYAN);
    uint8 choice;
    scanf("%hhi", &choice);

    set_coins_age_index(course, choice);
    return;
}