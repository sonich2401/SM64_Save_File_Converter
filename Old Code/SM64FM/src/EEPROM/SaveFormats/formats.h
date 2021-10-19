#prgama once
#include <typedefs.h>
#include "../EEPROM.h"

extern const uint16 EMU_MAGIC;
extern const uint16 PC_MAGIC;

enum FORMAT{
	EMU,
	PC,
	VDOC,
	N64
};

//detects the EEPROM's format based on the magic and checksum
FORMAT detect_format(uint16 magic, uint16 checksum);

//converts any eeprom into a new eeprom that contains a converted eeprom with the desired file format encoding
void convert_format(EEPROM * savefile, FORMAT to);

//this function will convert the EEPROM into a format that modern computers can read
//without much conversion
void convertUniversal(EEPROM * src);
