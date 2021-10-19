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
#include <_typedefs.h>

#ifndef LEVEL_H
#define LEVEL_H

union Level{
    struct Level_t1{
        bool star1 : 1;
        bool star2 : 1;
        bool star3 : 1;
        bool star4 : 1;
        bool star5 : 1;
        bool star6 : 1;
        bool coin_star : 1;
        bool cannon : 1;
    }named;

    uint8 byte;
};



union Level_Data {
    struct LevelsNamed{
        Level BombOmbBattlefeild;
        Level WhompsFortress;
        Level JollyRodgerBay;
        Level CoolCoolMountain;
        Level BigBoosHaunt;
        Level HazyMazeCave;
        Level LethalLavaLand;
        Level ShiftingSandLand;
        Level DireDireDocks;
        Level SnowmansLand;
        Level WetDryWorld;
        Level TallTallMountain;
        Level TinyHugeMountian;
        Level TickTockClock;
        Level RainbowRide;
    }levels_named;

    Level levels_indexed[15];
};


#endif