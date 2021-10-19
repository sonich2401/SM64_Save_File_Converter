//Check EEPROM.c for the values of the header
#pragma once
#include <typedefs.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    const cstring name;
    const cstring acts[7];
}course_str_struct;

typedef struct {
    const cstring name;
    const uint16 byte_offset;
    const uint8 bit_offset;
}flag_str_struct;


//Check EEPROM.c for extern defines
#ifndef STR_COURSE_SIZE
#define STR_COURSE_SIZE 15
#endif

#ifndef STR_SECRET_SIZE
#define STR_SECRET_SIZE 10
#endif

#ifndef STR_FLAGS_SIZE
#define STR_FLAGS_SIZE 26
#endif

extern const course_str_struct str_courses[STR_COURSE_SIZE];

extern const flag_str_struct str_flags[STR_FLAGS_SIZE];

extern const flag_str_struct str_secret[STR_SECRET_SIZE];