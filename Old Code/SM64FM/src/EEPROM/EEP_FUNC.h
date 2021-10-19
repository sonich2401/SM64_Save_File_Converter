#pragma once
#include "typedefs.h"
#include "EEPROM.h"



#define SAVE_SLOT(slot) EEPROM_Storage::get().edited->named.Slots.slots2D[slot][0]

#define MENU_SLOT(slot) EEPROM_Storage::get().edited->named.MenuSaves.split.primary

