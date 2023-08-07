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
#include <resource/resource_manager.h>
#include "screensize.h"
#include "EEPROM/SaveFormats/formats.h"

save_screen::save_screen(Example * olc, uint8 current_slot) : screen(olc, current_slot){
    pge = olc;

    n64 = ADD_STATIC_REN(RESOURCE_ENUM::EMU);
    pc =  ADD_STATIC_REN(RESOURCE_ENUM::PC);

    pge->Clear(olc::GREY);
}


void save_screen::run(float& fElapsedTime){
    pge->SetDrawTarget((uint8)0);
    pge->Clear(olc::Pixel(0,0,0,0));
    pge->SetDrawTarget((uint8)1);


    //Draw top textbox
    #define BOX_Y_LEVEL 80
    #define BOX_TEXT_SCALE 4
    #define BOX_TEXT "Choose a Save Format"
    pge->FillRectDecal({0,0}, {SCREEN_W, BOX_Y_LEVEL});
    pge->DrawLineDecal({0, BOX_Y_LEVEL}, {SCREEN_W, BOX_Y_LEVEL}, olc::BLACK);
    olc::vf2d text_size = pge->GetTextSize(BOX_TEXT);
    text_size *= BOX_TEXT_SCALE;
    pge->DrawStringDecal({(SCREEN_W - text_size.x) / 2, (BOX_Y_LEVEL - text_size.y)/2}, BOX_TEXT, olc::BLACK, {BOX_TEXT_SCALE, BOX_TEXT_SCALE});



    const float n64_SCALE = (SCREEN_W / 2) / n64->spr->width;
    const float pc_SCALE = n64_SCALE * 0.9;

    const float N64_Y_LEVEL = (SCREEN_H - (n64->spr->height * n64_SCALE)) / 2;
    const float PC_Y_LEVEL = (SCREEN_H - (pc->spr->height * pc_SCALE)) / 2;

    pge->DrawDecal({0, N64_Y_LEVEL}, n64->dcl, {n64_SCALE, n64_SCALE});
    pge->DrawDecal({(SCREEN_W / 2), PC_Y_LEVEL}, pc->dcl, {pc_SCALE, pc_SCALE});

    if(pge->GetMouse(0).bPressed){
        if(pge->GetMouseX() < 300){
            //N64 save type
            EEP_DAT::get().save(SAVE_FORMATS::N64);
        }else{
            //PC PORT
            EEP_DAT::get().save(SAVE_FORMATS::PC);
        }
        
        pge->ChangeGamestate(0);
    }
}

save_screen::~save_screen(){
}