#include <typedefs.h>
#include "menu_choice.h"
#include "../EEPROM/EEPROM.h"
#include "../EEPROM/EEPROM_Defines.h"
#include "../../C-/cppstdlib/rfind/rfind.h"

extern EEPROM * eeprom;


typedef struct {
  const string good_name;
  const string op_name;
}flag_def;


const flag_def doors[9] = {
  {
    "Whomp's Fortress Door",
    "WF"
  },
  {
    "Cool Cool Mountain Door",
    "CMM"
  },
  { 
    "Jolly Rodger Bay Door",
    "JRB"
  },
  {
    "Princess Secret Slide Door",
    "PSS"
  },
  {
    "Bowser in the Dark World Door (Star door 1)",
    "Star 1"
  },
  {
    "Bowser in the Fire Sea (Star door 2)",
    "Star 2"
  },
  {
    "50 Star Door (Star door 3)",
    "Star 3"
  },
  {
    "Basement Door",
    "Basement"
  },
  {
    "Upstairs Door"
    "Upstairs"
  }
};


const flag_def progress[8] = {
  {
    "Valid Game",
    "Valid"
  },
  {
    "Castle Moat",
    "Moat"
  },
  { 
    "Bowser Key 1 (Downstairs)",
    "Key 1"
  },
  {
    "Bowser Key 2 (Upstairs)",
    "Key 2"
  },
  {
    "Dire Dire Docks Portal Moved",
    "DDD"
  },
  {
    "Wing Cap Un-locked",
    "Wing"
  },
  {
    "Metal Cap Un-locked",
    "Star 3"
  },
  {
    "Vanish Cap Un-locked",
    "Invis"
  }
};

const flag_def caps[3] = {
  {
    "Wing Cap Un-locked",
    "Wing"
  },
  {
    "Metal Cap Un-locked",
    "Metal"
  },
  { 
    "Vanish Cap Un-locked",
    "Invis"
  }
};


const string format = "%i. %s\n";





void local___flag_menu(const flag_def list[], uint8 size){
  while(true){
    system(OS_CLEAR)
    for(uint8 i = 0; i < size; i++){
      if(get_flag_name(list[i].op_name)){
        colstr(printf(format, i+1, list[i].good_name), T_GREEN);
      }
      printf(format, i+1, list[i].good_name);
    }
    printf("\n");
    colstr(printf("Please Choose a Option (Enter 0 to leave) "), T_CYAN);

    int8 choice;
    scanf("%hhi", &choice);

    if(choice == 0) return;
    if(choice >= size){
      system(OS_CLEAR);
      colstr(printf("ERROR!!!\n"), T_RED);
      printf("Not a valid option");
      system(OS_PAUSE);
      continue;
    }

    choice--;
    bool val = get_flag_name(list[choice].op_name);
    set_flag_name(lsit[choice].op_name, !val);

  }
}



void menu_set_door_flags(){
  local___flag_menu(doors, 9);
}

void menu_set_progress_flags(){
  local___flag_menu(progress, 8);
}

void menu_set_cap_flags(){
  local___flag_menu(caps, 3);
}