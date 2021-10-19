#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <typedefs.h>

unsigned char * load_bin(string fp);

void write_bin(string fn, unsigned char * buffer, uint32 buffer_size);