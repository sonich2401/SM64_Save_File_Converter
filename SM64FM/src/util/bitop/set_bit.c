#include "bitop.h"

void print_binary(unsigned int number)
{
    if (number >> 1) {
        print_binary(number >> 1);
    }
    putc((number & 1) ? '1' : '0', stdout);
}
//Set the bit in the given bytes
void set_bit8(uint8 * src, uint8 bit, uint8 new_val){
    *src = (*src & ~(1 << bit)) | (new_val << bit);
}

//Set the bit in the given bytes
void set_bit16(uint16 * src, uint8 _bit, uint16 new_val){
    uint16 bit = _bit;
    *src = (*src & ~(1 << bit)) | (new_val << bit);
}

//Set the bit in the given bytes
void set_bit32(uint32 * src, uint8 _bit, uint32 new_val){
    uint32 bit = _bit;
    *src = (*src & ~(1 << bit)) | (new_val << bit);
}

//Set the bit in the given bytes
void set_bit64(uint64 * src, uint8 _bit, uint64 new_val){
    uint64 bit = _bit;
    *src = (*src & ~(1 << bit)) | (new_val << bit);
}