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

#ifndef GAME_FLAGS_H
#define GAME_FLAGS_H

union Flags
        {
            struct named{
#if 0
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
#else
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

                struct x0A {
                    bool DDD_Portal_Moved : 1;
                    bool Castle_Moat_Water : 1;
                    bool PSS_Door_Unlocked : 1;
                    bool WF_Door_Unlocked : 1;
                    bool CCM_Door_Unlocked : 1;
                    bool JRB_Door_Unlocked : 1;
                    bool Bowser1_StarDoor_Unlocked : 1;
                    bool Bowser2_StarDoor_Unlocked : 1;
                }UnlockedDoors;

                struct x09 {
                    bool CapStolenBySnowman : 1;
                    bool CapStolenByBird : 1;
                    bool CapStolenByMonkey : 1;
                    bool DoorOpen_50star : 1;
                }CapStolenFlags_50StarDoor;

                struct x08 {
                    bool ToadStarBasement : 1;
                    bool MIPS_Star16 : 1;
                    bool ToadStarUpstairs : 1;
                    bool ToadStarTickTockClock : 1;
                    bool MIPS_Star50 : 1;
                }ToadMipsStars;
            }Named;
#endif

            int8 array[4];
        };

#endif