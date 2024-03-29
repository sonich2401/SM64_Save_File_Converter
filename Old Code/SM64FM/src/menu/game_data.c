#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"
#include "../../C-/cppstdlib/rfind/rfind.h"

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
            uint8 * change_byte = &eeprom->game_saves[current_save][backup_mode].capLevel;
            if(i == 1)
                change_byte = &eeprom->game_saves[current_save][backup_mode].capArea;
            printf(format, i + 1, options[i], *change_byte);
            scanf("%hhi", change_byte);
            continue;
        }
        if(i < 2 + 4){
            if(i == 5){
                printf("NOT IMPLEMENTED YET\n");
                continue;
            }
            printf(format, i + 1, options[i], eeprom->game_saves[current_save][backup_mode].capPos[i - 2]);
            
            int16 choice;
            scanf("%hi", &choice);
            eeprom->game_saves[current_save][backup_mode].capPos[i - 2] = choice;
            printf("\r");
            continue;
        }

    }
}



void menu_edit_level_coin(){

    int8 choice = menu_choose_star();
    if(choice == -1){return;} //Exit was selected
    
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
            if(get_bit8(eeprom->game_saves[current_save][backup_mode].CourseDat[course], i)){
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
            bool old_val = get_bit8(eeprom->game_saves[current_save][backup_mode].CourseDat[course], choice-1);
            set_bit8(&eeprom->game_saves[current_save][backup_mode].CourseDat[course], choice-1,!old_val);//toggle bit
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

void menu_print_courses(){
    printf("Which course to Edit?\n");
    for(uint8 i = 0; i < 15; i++){
        int chars_printed = 0;
        chars_printed = printf("%i. %s ", i + 1, str_courses[i].name);
        for(uint8 i1 = 0; i1 < 27 - chars_printed; i1++){ //Make sure everything is printed on the same collom
            printf(" ");
        }
        for(uint8 i1 = 0; i1 < 7; i1++){
            if(get_bit8(eeprom->game_saves[current_save][backup_mode].CourseDat[i], i1)){
                colstr(printf("* "),T_YELLOW);
            }else{
                printf("* ");
            }
        }
        if(!get_bit8(eeprom->game_saves[current_save][backup_mode].CourseDat[i], 7)){
            colstr(printf("[#]"), T_RED);
            colstr(printf(" %i\n", get_coins_index(i)),T_YELLOW);
            continue;
        }
        printf("[ ]");
        colstr(printf(" %i\n", get_coins_index(i)),T_YELLOW);
    }
}


int8 menu_choose_star(){
    while(1){
        menu_print_courses();
    
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





typedef struct {
  const string good_name;
  const string op_name;
}flag_def;



const flag_def secrets[10] = {
  {
  #if (OS == Linux)
    "Princess Secret Slide \033[0;33m[!]\033[0m Box",
  #else
    "Princess Secret Slide [!] Box",
  #endif
    "PSS [!]"
  },
  {
    "Princess Secret Slide 20 sec Speedrun",
    "PSS 20"
  },
  { 
    "Bowser in the Dark World Red Coins (Bowser 1)",
    "Bow 1"
  },
  {
    "Bowser in the Fire Sea Red Coins (Bowser 2)",
    "Bow 2"
  },
  {
    "Bowser in the Sky Red Coins (Bowser 3)",
    "Bow 3"
  },
  {
    "Mario Wings over the Rainbow",
    "Rain"
  },
  {
    "Princess Secret Aquarium",
    "Aqua"
  },
  {
    "Wing Cap Red Coins",
    "Wing"
  },
  {
    "Metal Cap Red Coins",
    "Metal"
  },
  {
    "Vanish Cap Red Coins",
    "Invis"
  }
};




extern const string format;

void menu_edit_secrets(){
  while(true){
    system(OS_CLEAR);
    for(uint8 i = 0; i < STR_SECRET_SIZE; i++){
      if(get_secret_name(secrets[i].op_name)){
        colstr(printf(format, i+1, secrets[i].good_name), T_GREEN);
        continue;
      }
      printf(format, i+1, secrets[i].good_name);
    }
    printf("\n");
    colstr(printf("Please Choose a Option (Enter 0 to leave) "), T_CYAN);

    int8 choice;
    scanf("%hhi", &choice);

    if(choice == 0) return;
    if(choice >= 11){
      system(OS_CLEAR);
      colstr(printf("ERROR!!!\n"), T_RED);
      printf("Not a valid option\n");
      printf("Press any key to continue ...\n");
      system(OS_PAUSE);
      continue;
    }

    choice--;
    bool val = get_secret_name(secrets[choice].op_name);
    set_secret_name(secrets[choice].op_name, !val);
  }
}