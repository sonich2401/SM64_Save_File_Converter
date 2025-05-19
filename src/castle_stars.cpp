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
#include <olcPixelGameEngine.h>
#include "pgeClass.h"

const std::string SECRETSTAR_NAMES[15] = {
    "Bowser 1 Red Coins",
    "Bowser 2 Red Coins",
    "Bowser 3 Red Coins",
    "Princess Secret Slide [!]",
    "Princess Secret Slide 20sec",
    "Metal Cap Red Coins",
    "Wing Cap Red Coins",
    "Vanish Cap Red Coins",
    "Wings Over the Rainbow Red Coins",
    "Aquarium Red Coins",
    "Toad Star Basement [HMC]",
    "MIPS the rabbit 16 star",
    "Toad Star Upstairs",
    "Toad Star Upstairs [TTC]",
    "MIPS the rabbit 50 star"
};

const int ySPACING  = 34;
const int WORD_SPACING = 16;

const olc::Pixel COLORS[2] = { olc::RED,olc::GREEN };
const std::string BOOL_NAMES[2] = { "False","True" };


main_screen2::main_screen2(Example * olc, uint8 current_slot) : screen(olc, current_slot){
    pge = olc;
    EEP_DAT::get().updateSecrets();
}

void main_screen2::run(float& fElapsedTime){
    (void)fElapsedTime;
    pge->Clear(olc::GREY);

    int selected = -1;

    auto DrawTextLine = [&](int x, int y, std::string name, bool state){
        pge->FillRect({ x + 2, y }, { ((int)(name.size() * WORD_SPACING)),WORD_SPACING }, olc::WHITE);
        pge->DrawRect({ x, y - 2 }, { ((int)(name.size() * WORD_SPACING)) + 3, WORD_SPACING + 3 }, olc::BLACK);
        pge->DrawString({ x + 2, y }, name, olc::BLACK, 2);
        pge->DrawString({ 750 - 80, y }, BOOL_NAMES[state], COLORS[state], 2);
    };
            
    for (int i = 0; i < 15; i++) {
        bool bool_val = EEP_DAT::get().save_file_buffers[cur_slot].secret_star_states[i];

        DrawTextLine(18, i * ySPACING, SECRETSTAR_NAMES[(int)i], bool_val);

        //Check for clicking
        if(pge->GetMouse(0).bPressed){
            if(selected == -1){
                selected = (int)(pge->GetMouseY() / ySPACING);
                if(selected >= 15){ //Invalid option
                    selected = -1;
                    continue;
                }

                //For case 10 - 14
                    uint8 * toad_mips = (uint8*)&EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.flags.Named.ToadMipsStars;
                //
                uint8 tmp_val = 0xFF; //Used because you cant make varibles in switches

                switch (selected)
                {
                case 3:
                case 4:
                    //See case 10 - 14 for my resoning for this sinful code
                    tmp_val = *(uint8*)&EEP_GET_SAVE(cur_slot)->GoodName.castle_secret_stars.named.PricessSecretSlide;
                    tmp_val ^= (1 << (selected - 3));
                    memcpy(&EEP_GET_SAVE(cur_slot)->GoodName.castle_secret_stars.named.PricessSecretSlide, &tmp_val, 1);
                    break;
                case 10: //Toad stars
                case 11:
                case 12:
                case 13:
                case 14:
                    //Jank solution because *toad_mips = xyz; was not working
                    tmp_val = *toad_mips;
                    tmp_val ^= (1 << (selected - 10));
                    memcpy(toad_mips, &tmp_val, 1);
                break;
                
                default: //Normal
                    //the '(selected >= 5)' is a band-aid fix to a bug idk how to fix
                    EEP_GET_SAVE(cur_slot)->GoodName.castle_secret_stars.array[selected - (selected >= 5)] ^= 1;
                    break;
                }
                EEP_DAT::get().updateSecrets();
            }
        }
            
    }
}


main_screen2::~main_screen2(){

}