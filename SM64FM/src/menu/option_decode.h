#pragma once
#include <typedefs.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "useage.h"

typedef struct{
    //General
    uint16 byte_size;
    string byte_order;
    bool enable_backup;

    //Game Save Settings
    uint16 file_size;
    uint8 file_count;
    //Menu save settings
    uint16 menu_size;
    uint8 menu_count;

    //I/O settings
    bool config;
    string config_path;
    string in_path;
    string out_path;

    //Main menu options
    bool man;
    //hackity hack hack?
    bool backdoor;
    uint8 b_type;
    uint8 arg1;
    uint8 arg2;
    uint8 arg3;
}option_struct;

//Used defines so that namespace isnt cluttered
#define init_option(p_opt_struct) {\
    p_opt_struct->byte_size = 512; \
    p_opt_struct->enable_backup = true; \
    p_opt_struct->config = false; \
    p_opt_struct->config_path = "NULL"; \
    p_opt_struct->file_size = 38; \
    p_opt_struct->file_count = 4; \
    p_opt_struct->menu_size = 0; \
    p_opt_struct->menu_count = 0; \
    p_opt_struct->man = false;\
    p_opt_struct->backdoor = false;\
}


option_struct * option_decode(int argc, string argv[]){
    //Init
    argc--;
    option_struct * ret = malloc(sizeof(option_struct));
    init_option((ret));
    

    //Error checks
    if(argc < 2){print_usage(); return ret;} //User never gave any args

    //Start decoding


    if (argv[1][0] =='-' && argv[1][1] =='m')//Is it the manual uptions?
    {
        ret->man = true;
        return ret;
    }

    if(strlen(argv[1]) <= 4)
        if (argv[1][0] =='-' && argv[1][1] =='y' && argv[1][2] =='o'&& argv[1][3] =='p')//Hackity hack hack?
        {
            ret->backdoor = true;
            ret->b_type = atoi(argv[2]);
            ret->arg1 = atoi(argv[3]);
            ret->arg2 = atoi(argv[4]);
            ret->arg3 = atoi(argv[5]);
            ret->in_path = argv[6];
            ret->out_path = argv[7];
            return ret;
        }
    
    uint8 index = 1;
    if(argc > 2){ //Start changing args if we have some
        for(; index < argc - 2; index++){
            if(argv[index][0] != '-'){printf("ERROR: Invalid Option!\n"); return ret;}
            switch(argv[index][1]){
                case 'b':
                case 'e':
                    ret->byte_order = argv[++index];
                break;
                case 'c':
                    ret->config_path = argv[++index];
                    ret->config = true;
                break;
                default:
                    printf("ERROR: Invailid Option!\n");
                    return ret;
            }
        }
    }

    if(argc - index != 1){ //Did we read too much?
        printf("ERROR: Not Enough/Too many args! Did you forget/add an arg parameter?\n");
        return NULL;
    }

    ret->out_path = argv[argc--];
    ret->in_path = argv[argc--];

    return ret;
}


#undef init_option