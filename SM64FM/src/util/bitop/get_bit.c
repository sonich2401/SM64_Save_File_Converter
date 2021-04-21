#include  "bitop.h"

//Get the bit in the given bytes
bool get_bit8(uint8 val, uint8 bit){
    return (val & (1 << bit)) >> bit;
}

//Get the bit in the given bytes
bool get_bit16(uint16 val, uint8 _bit){
    uint16 bit = _bit;
    return (val & (1 << bit)) >> bit;
}

//Get the bit in the given bytes
bool get_bit32(uint32 val, uint8 _bit){
    uint32 bit = _bit;
    return (val & (1 << bit)) >> bit;
}

//Get the bit in the given bytes
bool get_bit64(uint64 val, uint8 _bit){
    uint64 bit = _bit;
    return (val & (1 << bit)) >> bit;
}