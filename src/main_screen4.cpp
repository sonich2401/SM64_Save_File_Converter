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

const std::string gamestate_names[6]  = {
    "Valid Game",
    "Wing Cap Switch",
    "Metal Cap Switch",
    "Vanish Cap Switch",
    "Bowser 1 Key",
    "Bowser 2 Key",
};

#define LETTER_SCALE 3
const int ySPACING  = 34;
const int WORD_SPACING = LETTER_SCALE * 8;

const olc::Pixel COLORS[2] = { olc::RED,olc::GREEN };
const std::string BOOL_NAMES[2] = { "False","True" };


main_screen4::main_screen4(Example * olc, uint8 current_slot) : screen(olc, current_slot){
    pge = olc;
}


void main_screen4::run(float& fElapsedTime){
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
        if(selected >= 6)
            selected = 5;
        
        *(uint8*)&EEP_DAT::get().getCurSave(cur_slot)->GoodName.flags.Named.ProgressFlags ^= (1 << selected);
    }

    for(uint8_t i = 0; i < 6; i++){
        bool val = ((*(uint8*)&EEP_DAT::get().getCurSave(cur_slot)->GoodName.flags.Named.ProgressFlags) >> i) & 0b1;
        DrawTextLine(10, 20 + (i * OPTION_SPACING), gamestate_names[i], val);
    }
}
