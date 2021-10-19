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
#pragma once
#include <_typedefs.h>

#if IS_LITTLE_ENDIAN
	#define N64_MAGIC 0x4144
	#define EMU_MAGIC N64_MAGIC
	#define PC_MAGIC 0x4441
	

	#define PC_CHKSM 0x8500
	#define N64_CHKSM 0x0085
	#define EMU_CHKSM N64_CHKSM

#else
	#define EMU_MAGIC 0x4441
	#define PC_MAGIC 0x4144
	#define N64_MAGIC 0x4441

	#define PC_CHKSM 0x0085
	#define N64_CHKSM 0x8500
	#define EMU_CHKSM N64_CHKSM

#endif

union EEPROM;

namespace SAVE_FORMATS{
	enum FORMAT{
		EMU,
		PC,
		VDOC,
		N64
	};


	FORMAT detect(uint16 magic, uint16 checksum);

	EEPROM* convert(EEPROM * eep, FORMAT desired_format);
};
