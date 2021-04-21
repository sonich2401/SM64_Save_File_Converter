#pragma once
#include <typedefs.h>
#include <stdio.h>
#include <stdlib.h>

//get_bit.c

//Get the bit in the given bytes
bool get_bit8(uint8 val, uint8 bit);

//Get the bit in the given bytes
bool get_bit16(uint16 val, uint8 bit);

//Get the bit in the given bytes
bool get_bit32(uint32 val, uint8 bit);

//Get the bit in the given bytes
bool get_bit64(uint64 val, uint8 bit);


//set_bit.c

//Set the bit in the given bytes
void set_bit8(uint8 * src, uint8 bit, uint8 new_val);

//Set the bit in the given bytes
void set_bit16(uint16 * src, uint8 bit, uint16 new_val);

//Set the bit in the given bytes
void set_bit32(uint32 * src, uint8 bit, uint32 new_val);

//Set the bit in the given bytes
void set_bit64(uint64 * src, uint8 bit, uint64 new_val);