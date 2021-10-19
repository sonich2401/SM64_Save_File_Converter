/*RenDev#2616 SM64SFM
    Copyright (C) 2021 RenDev

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
    Permission is also granted to not credit the author in any way as long as you do not take credit
    for this piece of software.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/
#include <_typedefs.h>
#include <filesys/openfile.h>
#include <filesys/load_bin.h>
#include <filesys/load_text.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>


#ifndef EEPROM_H
#define EEPROM_H

//Struct includes
    #include "EEP_Types/save.h"
    #include "EEP_Types/menu.h"
//
#include "SaveFormats/formats.h"

//Empty Offical SM64 EEPROM
#include "empty_file/Empty.h"

//Helpful shortcut Macros
#ifndef EEPROM_H_MACROS
#define EEPROM_H_MACROS
    #define EEP_GET_SAVE(save_slot) EEP_DAT::get().getCurSave(save_slot)
#endif


union EEPROM
{
    struct VarEEP{
        union SaveSlots
        {
            struct Split{
                union Save primary;
                union Save backup;  
            }CombinedSlots[4]; //Combine backup and primary into one struct

            struct Named{
                union Save A_Prime;
                union Save A_Back;

                union Save B_Prime;
                union Save B_Back;

                union Save C_Prime;
                union Save C_Back;

                union Save D_Prime;
                union Save D_Back;  
            }SeperateSlots; //Seperate the backup from primary

            union Save slots2D[4][2];
            union Save slotsArray[8];
        }Slots;

        union MenuSlots
        {
            struct MenuSplit{
                union Menu primary;
                union Menu backup;  
            }split; //Combine backup and primary into one struct

            union Menu array[2];
        }MenuSaves;
    }named;
    
    uint8 array[512];
    
};



class EEP_DAT{
    public:
        EEPROM * dat;
        EEPROM * edited;

    public:
        EEP_DAT();

    public:
        struct {
            bool valid = false;
            int stars = 0;
            int secret_stars = 0;
            int toad_stars = 0;

            std::vector<bool> secret_star_states;
            std::vector<bool> door_states;
        }save_file_buffers[4];

        SAVE_FORMATS::FORMAT format;

    public:
        static EEP_DAT& get(){
            static EEP_DAT in;
            return in;
        }

        Save * getCurSave(int save_slot, bool backup = false);

        void init();

        void load();

        void save(SAVE_FORMATS::FORMAT disired_format, EEPROM* ptr = nullptr);

        void updateSecrets();

        void update();

        uint16_t calc_checksum(char * save);

        bool isCorrupted();

        void fix_corruption();


    private:

        ~EEP_DAT();
};


#endif