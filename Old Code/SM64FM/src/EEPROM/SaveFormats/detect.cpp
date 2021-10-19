#include "formats.h"

FORMAT detect_format(uint16 magic, uint16 checksum){
	switch (magic)
	{
	case EMU_MAGIC:
		return FORMAT::EMU;
		break;
	case PC_MAGIC:
		return FORMAT::PC;
		break;
	
	default:
		//magic is in the same address as checksum in the vdoc format
		if(checksum == PC_MAGIC || checksum == EMU_MAGIC){
			return FORMAT::VDOC;
		}else{
			colstr(printf("ERROR: detect_format() \"Not a valid magic. Corrupted save file!\"\n"), B_RED);
		}
		break;
	}
}

