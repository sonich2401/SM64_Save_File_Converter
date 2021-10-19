#include "formats.h"



//Helper functions
void SwapEndian(char * val, uint8 byte_count){
	for(uint8 i = 0; i < byte_count/2; i++){ //swap the first size/2 elements with the mirrored equivilents at the end of the byte
		char tmp = val[i];
		val[i] = val[4 - i];
		val[4 - i] = tmp;
	}
}



void EndianSwap(EEPROM& saveFile){

	//Save files
	for(uint8 SaveSlot = 0; SaveSlot < 8; SaveSlot++){
		Save * cur_save = &saveFile.named.Slots.slotsArray[SaveSlot];
		SwapEndian(cur_save->GoodName.flags.array, 4);
		SwapEndian(cur_save->GoodName.checksum, 2);
		SwapEndian(cur_save->GoodName.magic, 2);
	}

	//Menus
	for(uint8 SaveSlot = 0; SaveSlot < 8; SaveSlot++){
		Menu * cur_menu = &saveFile.named.MenuSaves.array[SaveSlot];
		SwapEndian(cur_menu->GoodName.checksum, 2);
		SwapEndian(cur_menu->GoodName.magic, 2);
	}

}



//converts any eeprom into a new eeprom that contains a converted eeprom with the desired file format encoding
EEPROM * convert_format(EEPROM * savefile, FORMAT to){
	EEPROM * saveFileCopy = convertUniversal(memcpy(savefile, saveFileCopy, 512));

	switch (to)
	{
	case EMU:
	case N64:
		//already in correct format
		break;
	case PC:
		EndianSwap(saveFileCopy);
	break;
	case VDOC:
		VDOC_SwapBytes(saveFileCopy);
		break;

	default:
		colstr(printf("ERROR (convert_format()): check detect_format because returned value is not reconized by this function\n"),T_RED);
		break;
	}

	return saveFileCopy; //return new save file
}


//this function will convert the EEPROM into a format that modern computers can read
//without much conversion
void convertUniversal(EEPROM * src){
	FORMAT saveFormat= detect_format(savefile->named.Slots.slots2D[0][0].GoodName.magic);
	
	switch (saveFormat)
	{
	case EMU:
	case N64:
		//already in correct format
		break;
	case PC:
		EndianSwap(src);
	break;
	case VDOC:
		VDOC_SwapBytes(src);
		break;

	default:
		colstr(printf("ERROR (convertUniversal()): check detect_format because returned value is not reconized by this function\n"),T_RED);
		break;
	}
}







//Mirror all groups of 4 bytes
void VDOC_SwapBytes(EEPROM& saveFile){
	for(uint16 i = 0; i < 512/4; i+=4){
		SwapEndian(&saveFile.array[i], 4);
	}
}