#include "typedefs.h"

#ifndef EEPROM_H
#define EEPROM_H

//Struct includes
    #include "EEP_Types/save.h"
    #include "EEP_Types/menu.h"
//

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



//EEPROM Singleton

EEPROM init_EEPROM(unsigned char * buffer);

class EEPROM_Storage{
    public:
        static EEPROM_Storage& get(){
            static EEPROM_Storage inst;
            return inst;
        }
    public:

        EEPROM * orginal;
        EEPROM * edited;

        uint8 cur_slot;


   private:
    ~EEPROM_Storage(){}
};





#endif