#include "../typedefs.h"

#ifndef GAME_FLAGS_H
#define GAME_FLAGS_H

union Flags
        {
            struct named{
                struct x08{
                    bool ToadStarBasement : 1;
                    bool MIPS_Star16 : 1;
                    bool ToadStarUpstairs : 1;
                    bool ToadStarTickTockClock : 1;
                    bool MIPS_Star50 : 1;
                }ToadMipsStars;

                struct x09{
                    bool CapStolenBySnowman : 1;
                    bool CapStolenByBird : 1;
                    bool CapStolenByMonkey : 1;
                    bool DoorOpen_50star : 1;
                }CapStolenFlags_50StarDoor;

                struct x0A{
                    bool DDD_Portal_Moved : 1;
                    bool Castle_Moat_Water : 1;
                    bool PSS_Door_Unlocked : 1;
                    bool WF_Door_Unlocked : 1;
                    bool CCM_Door_Unlocked : 1;
                    bool JRB_Door_Unlocked : 1;
                    bool Bowser1_StarDoor_Unlocked : 1;
                    bool Bowser2_StarDoor_Unlocked : 1;
                }UnlockedDoors;

                struct h0x0B {
                    bool ValidGame : 1;
                    bool WingCapSwitch : 1;
                    bool MetalCapSwitch : 1;
                    bool VanishCapSwitch : 1;
                    bool Bowser1_Key : 1;
                    bool Bowser2_Key : 1;
                    bool BasementDoorOpened : 1;
                    bool UpstairsDoorOpened : 1;
                }ProgressFlags;
            }Named;

            int8 array[4];
        };

#endif