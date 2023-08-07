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
#include "screendef.h"
#include "EEPROM/EEPROM.h"

const std::string gamestate_names[11]  = {
    "DDD Portal Moved",
    "Castle Moat Drained",
    "PSS Door Unlocked",
    "WF Door Unlocked",
    "CCM Door Unlocked",
    "JRB Door Unlocked",
    "Bowser1 Star Door Unlocked",
    "Bowser2 Star Door Unlocked",
    "Basement Door Unlocked",
    "Upstairs Door Unlocked",
    "50 Star Door",
};

#define LETTER_SCALE 3
const int ySPACING  = 34;
const int WORD_SPACING = LETTER_SCALE * 8;

const olc::Pixel COLORS[2] = { olc::RED,olc::GREEN };
const std::string BOOL_NAMES[2] = { "False","True" };


main_screen5::main_screen5(Example * olc, uint8 current_slot) : screen(olc, current_slot){
    pge = olc;
}


void main_screen5::run(float& fElapsedTime){
    pge->Clear(olc::GREY);

    const auto DrawTextLine = [&](int x, int y, std::string name, bool state){
        pge->FillRect({ x + 2, y }, { ((int)(name.size() * WORD_SPACING)),WORD_SPACING }, olc::WHITE);
        pge->DrawRect({ x, y - 2 }, { ((int)(name.size() * WORD_SPACING)) + 3, WORD_SPACING + 3 }, olc::BLACK);
        pge->DrawString({ x + 2, y }, name, olc::BLACK, LETTER_SCALE);
        pge->DrawString({ 750 - 80, y }, BOOL_NAMES[state], COLORS[state], LETTER_SCALE);
    };


    #define OPTION_SPACING 50
    if(pge->GetMouse(0).bPressed){
        int selected = (pge->GetMouseY() / OPTION_SPACING);
        if(selected >= 11)
            selected = 10;
        
        uint8 tmp_val;
        switch(selected){
            case 8:
                EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.ProgressFlags.BasementDoorOpened = !EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.ProgressFlags.BasementDoorOpened;
            break;
            case 9:
                EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.ProgressFlags.UpstairsDoorOpened = !EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.ProgressFlags.UpstairsDoorOpened;
            break;
            case 10:
                EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.CapStolenFlags_50StarDoor.DoorOpen_50star = !EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.CapStolenFlags_50StarDoor.DoorOpen_50star; 
            break;

            default:
                uint8 tmp_val = *(uint8*)&EEP_DAT::get().getCurSave(cur_slot)->GoodName.flags.Named.UnlockedDoors;
                tmp_val ^= (1 << selected);
                memcpy(&EEP_DAT::get().getCurSave(cur_slot)->GoodName.flags.Named.UnlockedDoors, &tmp_val, 1);
            break;

        }
    }

    for(uint8_t i = 0; i < 8; i++){
        bool val = ((*(uint8*)&EEP_DAT::get().getCurSave(cur_slot)->GoodName.flags.Named.UnlockedDoors) >> i) & 0b1;
        DrawTextLine(10, 20 + (i * OPTION_SPACING), gamestate_names[i], val);
    }
    
    DrawTextLine(10, 20 + (8 * OPTION_SPACING), gamestate_names[8], EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.ProgressFlags.BasementDoorOpened);
    DrawTextLine(10, 20 + (9 * OPTION_SPACING), gamestate_names[9], EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.ProgressFlags.UpstairsDoorOpened);
    DrawTextLine(10, 20 + (10 * OPTION_SPACING), gamestate_names[10], EEP_GET_SAVE(cur_slot)->GoodName.flags.Named.CapStolenFlags_50StarDoor.DoorOpen_50star);
}


main_screen5::~main_screen5(){
    
}