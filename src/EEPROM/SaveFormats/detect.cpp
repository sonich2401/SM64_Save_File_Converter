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
#include <_typedefs.h>

const char* type_names[4] = {
		"Emulator",
		"PC",
		"V-Doctor",
		"Nintendo 64"
};




namespace SAVE_FORMATS{

	FORMAT detect(uint16 magic, uint16 checksum){

		FORMAT ret;

		switch (magic)
		{
		case N64_MAGIC:
			ret = FORMAT::N64;
			break;
		case PC_MAGIC:
			ret = FORMAT::PC;
			break;

		default:
			ret = FORMAT::VDOC;
			break;
		}

		if(ret == VDOC)
			if(checksum != N64_MAGIC){
				perror("Not a valid save type!");
				exit(-100);
			}
		
		return ret;
	}

}
