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
#ifndef TYPEDEFS_CP_H
#define TYPEDEFS_CP_H

#define IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define IS_LITTLE_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)


#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>


template<typename T>
static void byte_swap(T * ptr){
	if(sizeof(T) == 1)
		return;

	//printf("BEFORE = %x,", *ptr);

	T og_val = *ptr;
	unsigned char * chr_array = (unsigned char*)&og_val;

	for(size_t i = 0; i < (sizeof(T) / 2); i++){
		int mirrored_index = sizeof(T) - i - 1;

		unsigned char tmp_val = chr_array[i];
		chr_array[i] = chr_array[mirrored_index];
		chr_array[mirrored_index] = tmp_val;
	}

	memcpy(ptr, chr_array, sizeof(T));
	//printf(" After = %x\n", *ptr);
}

#include "escape_codes.h"

using std::string;
using std::vector;

typedef unsigned char uint8 ;
typedef char int8;

typedef unsigned short int uint16;
typedef short int int16;

typedef unsigned int uint32;
typedef int int32;

typedef unsigned long uint64;
typedef long int64;

typedef unsigned long long uint128;
typedef long long int128;

typedef float float32;


/*
#define bool char
#define boolean bool
#define false 0
#define true 1
#define True true
#define False false
#define TRUE true
#define FALSE false
*/

typedef char * cstring;

#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__)
//#ifndef OS_CLEAR

#define OS_CLEAR "clear"
#define OS_PAUSE "sed -n q </dev/tty"

//#endif
#else
#ifndef OS_CLEAR

#define OS_CLEAR "cls"
#define OS_PAUSE "pause"

#endif
#endif


#ifndef OS
#define OS WIN
#endif

#endif