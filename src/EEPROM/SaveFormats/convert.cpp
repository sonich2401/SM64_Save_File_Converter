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
#include "formats.h"
#include "../EEPROM.h"


namespace SAVE_FORMATS
{
	EEPROM* convert(EEPROM * eep, FORMAT desired_format){

		uint16_t magic = eep->named.Slots.slots2D[0][0].GoodName.magic.fullBytes;
		uint16_t checksum = eep->named.Slots.slots2D[0][0].GoodName.checksum;
		#if IS_LITTLE_ENDIAN
			//byte_swap<uint16>(&magic);
			//byte_swap<uint16>(&eep->named.Slots.slots2D[0][0].GoodName.checksum);
		#endif


		EEPROM* buffer = (EEPROM*)malloc(512);
		buffer = (EEPROM*)memcpy(buffer, eep, 512);
		FORMAT saveFormat = detect(magic, checksum);

		if(saveFormat == desired_format)
			return buffer;

		
		for(uint8 i1 = 0; i1 < 2; i1++){
			//Save Files
			for(uint8 i = 0; i < 4; i++){
				//TODO: Should I remove this? Seems like it would cause issues
				byte_swap<uint16>(&eep->named.Slots.slots2D[i][i1].GoodName.checksum);

				switch (saveFormat){
					case FORMAT::EMU:
					case FORMAT::PC:
					case FORMAT::N64:
						//Cap data
						byte_swap<int16>(&buffer->named.Slots.slots2D[i][i1].GoodName.cap_data.cap_pos_UNUSED.x);
						byte_swap<int16>(&buffer->named.Slots.slots2D[i][i1].GoodName.cap_data.cap_pos_UNUSED.y);
						byte_swap<int16>(&buffer->named.Slots.slots2D[i][i1].GoodName.cap_data.cap_pos_UNUSED.z);

						byte_swap<uint16>(&buffer->named.Slots.slots2D[i][i1].GoodName.checksum);
						byte_swap<uint16>(&buffer->named.Slots.slots2D[i][i1].GoodName.magic.fullBytes);

						//Flags
						byte_swap<uint32>((uint32*)&buffer->named.Slots.slots2D[i][i1].GoodName.flags.array);
					break;

					case VDOC:
						//TODO Create VDOC support
					break;
				}
			}
			//Menu Saves
			for(uint8 i = 0; i < 2; i++){
				byte_swap<uint16>(&buffer->named.MenuSaves.array[i].GoodName.magic.fullBytes);
				byte_swap<uint16>(&buffer->named.MenuSaves.array[i].GoodName.checkSum);
			}
		}

		return buffer;
	}

} // namespace SAVE_FORMATS