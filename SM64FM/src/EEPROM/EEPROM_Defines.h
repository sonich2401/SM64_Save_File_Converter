//Check EEPROM.c for the values of the header
#pragma once
#include <typedefs.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    const string name;
    const string acts[7];
}course_str_struct;

#ifndef STR_COURSE_SIZE
#define STR_COURSE_SIZE 15
#endif

#ifndef STR_SECRET_SIZE
#define STR_SECRET_SIZE 100
#endif

extern const course_str_struct str_courses[STR_COURSE_SIZE];

typedef struct {
    const string name;
    const uint16 byte_offset;
    const uint8 bit_offset;
}flag_str_struct;

#ifndef STR_FLAGS_SIZE
#define STR_FLAGS_SIZE 27
#endif

extern const flag_str_struct str_flags[STR_FLAGS_SIZE];