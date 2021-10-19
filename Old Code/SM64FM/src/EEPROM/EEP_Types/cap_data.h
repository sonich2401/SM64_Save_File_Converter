#include "../typedefs.h"

#ifndef CAP_DATA_H
#define CAP_DATA_H

typedef struct{
    int16 x,y,z;
}Vec3;

typedef struct {
    uint8 cap_level;
    uint8 cap_area;
    Vec3 cap_pos_UNUSED;
}LostCapData;

#endif