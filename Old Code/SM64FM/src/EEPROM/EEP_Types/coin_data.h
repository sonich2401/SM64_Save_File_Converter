#include "../typedefs.h"

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