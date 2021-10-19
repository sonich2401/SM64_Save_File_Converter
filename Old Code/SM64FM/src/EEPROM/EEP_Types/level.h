#include "../typedefs.h"

#ifndef LEVEL_H
#define LEVEL_H

typedef struct{
    bool star1 : 1;
    bool star2 : 1;
    bool star3 : 1;
    bool star4 : 1;
    bool star5 : 1;
    bool star6 : 1;
    bool coin_star : 1;
    bool cannon : 1;
}Level;


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