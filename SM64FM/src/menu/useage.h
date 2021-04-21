#pragma once
#include <typedefs.h>
#include <stdio.h>


#ifndef VER //Make VS code happy
#define VER 19921124.0
#endif
#ifndef DATE //Make VS code happy
#define DATE "NULL"
#endif
#ifndef PROG_NAME //Make VS code happy
#define PROG_NAME "NULL"
#endif


void print_usage(){
    printf("%s - v%.3f, Build Date: %s\n",PROG_NAME, VER, DATE);
    
    printf(
    "    Useage:\n"
    "        %s -<args [parameter]> (EEP/BIN) OUTFILE\n"
    "        %s -<args [parameter]> -c CONFIG_FILE (EEP/BIN) OUTFILE\n"
    "\n"
    "    Options:\n"
    "       -e -b: export as Endian/Byteswap\n"
    "            1 or \'big\'    = N64 orignal type (DEFAULT)\n"
    "            2 or \'little\' = 32 bit N64 type\n"
    "            3 or \'emu\'    = Emulator / V64 tpye\n"
    "       -m: read the EEPROM documentaion\n"
    "            Loads a interactive book-like documentation\n"
    "            on SM64 save files\n"
    "       -c: read a map config for rom hacks\n"
    "            Allows you to define your own byte map\n"
    "            to assign bytes to\n"
    ,PROG_NAME, PROG_NAME);
}