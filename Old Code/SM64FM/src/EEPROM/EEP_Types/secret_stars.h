#include "../typedefs.h"

#ifndef SECRET_STARS_H
#define SECRET_STARS_H

union CastleSecretStars
        {
            struct StarsNamed{
                bool Bowser1RedCoins;
                bool Bowser2RedCoins;
                bool Bowser3RedCoins;

                struct PSS{
                    bool Box : 1;
                    bool Speedrun20sec : 1;
                }PricessSecretSlide;

                struct cap_stars{
                    bool metalCap;
                    bool wingCap;
                    bool vanishCap;
                }CapRedCoins;

                bool WingsOverRainbow_RedCoins;
                bool Aquarium;

                bool UNUSED_CakeScreenStar;
            }named;

            uint8 array[10];
        };

#endif