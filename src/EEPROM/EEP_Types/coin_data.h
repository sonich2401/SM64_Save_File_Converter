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

#ifndef COIN_DATA_H
#define COIN_DATA_H


union CoinScoreData
        {
            struct levels_named{
                uint8 BombOmbBattlefeild;
                uint8 WhompsFortress;
                uint8 JollyRodgerBay;
                uint8 CoolCoolMountain;
                uint8 BigBoosHaunt;
                uint8 HazyMazeCave;
                uint8 LethalLavaLand;
                uint8 ShiftingSandLand;
                uint8 DireDireDocks;
                uint8 SnowmansLand;
                uint8 WetDryWorld;
                uint8 TallTallMountain;
                uint8 TinyHugeMountian;
                uint8 TickTockClock;
                uint8 RainbowRide;
            }named;

            uint8 levels_indexed[15];
        };

union CoinAgeData
        {
            struct coin_age_levels_named{
                uint8 BombOmbBattlefeild;
                uint8 WhompsFortress;
                uint8 JollyRodgerBay;
                uint8 CoolCoolMountain;
                uint8 BigBoosHaunt;
                uint8 HazyMazeCave;
                uint8 LethalLavaLand;
                uint8 ShiftingSandLand;
                uint8 DireDireDocks;
                uint8 SnowmansLand;
                uint8 WetDryWorld;
                uint8 TallTallMountain;
                uint8 TinyHugeMountian;
                uint8 TickTockClock;
                uint8 RainbowRide;
            }level_age_named;

            uint8 levels_indexed[15];
        };


#endif