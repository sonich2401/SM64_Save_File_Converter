#ifndef TYPEDEFS_CP_H
#define TYPEDEFS_CP_H

#include "src/util/os/linux/escape_codes.h"

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



#define bool char
#define boolean bool
#define false 0
#define true 1
#define True true
#define False false
#define TRUE true
#define FALSE false

typedef char * string;

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