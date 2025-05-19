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

const std::string star_names[5]  = {
    "Toad Star Basement [HMC]",
    "MIPS the rabbit 16 star",
    "Toad Star Upstairs",
    "Toad Star Upstairs [TTC]",
    "MIPS the rabbit 50 star"
};

#define LETTER_SCALE 3
const int ySPACING  = 34;
const int WORD_SPACING = LETTER_SCALE * 8;

const olc::Pixel COLORS[2] = { olc::RED,olc::GREEN };
const std::string BOOL_NAMES[2] = { "False","True" };

uint8 * toad_mips;
uint8 tmp_val;

void edit_toad_bits(char bit_index){
    tmp_val = *toad_mips;
    tmp_val ^= (1 << bit_index);
    memcpy(toad_mips, &tmp_val, 1);
}

main_screen3::main_screen3(Example * olc, uint8 current_slot) : screen(olc, current_slot){
    pge = olc;
    toad_mips = (uint8*)&EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.flags.Named.ToadMipsStars;
    EEP_DAT::get().updateSecrets();
}


void main_screen3::run(float& fElapsedTime){
    pge->Clear(olc::GREY);
    (void)fElapsedTime;

    const auto DrawTextLine = [&](int x, int y, std::string name, bool state){
        pge->FillRect({ x + 2, y }, { ((int)(name.size() * WORD_SPACING)),WORD_SPACING }, olc::WHITE);
        pge->DrawRect({ x, y - 2 }, { ((int)(name.size() * WORD_SPACING)) + 3, WORD_SPACING + 3 }, olc::BLACK);
        pge->DrawString({ x + 2, y }, name, olc::BLACK, 3);
        pge->DrawString({ 750 - 80, y }, BOOL_NAMES[state], COLORS[state], 3);
    };


    #define OPTION_SPACING 100
    if(pge->GetMouse(0).bPressed){
        int selected = (pge->GetMouseY() / OPTION_SPACING);
        if(selected >= 5)
            selected = 4;
        
        edit_toad_bits(selected % 5);
        EEP_DAT::get().updateSecrets();
    }

    for(uint8_t i = 0; i < 5; i++){
        DrawTextLine(10, 20 + (i * OPTION_SPACING), star_names[i], EEP_DAT::get().save_file_buffers[cur_slot].secret_star_states[i + 10]);
    }
}


main_screen3::~main_screen3(){

}