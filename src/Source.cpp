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
#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>
#include <_typedefs.h>

#include <Sprite.h>
#include "pgeClass.h"


#include "../pic/imagelist.h"
#include "EEPROM/EEPROM.h"

//Screens
#include "screendef.h"
//#include "mainscreen.h"
//#include "castle_stars.h"

//Resorce manager
#include "rman.h"




class Example;

class main_screen2;






Example::Example()
{
	// Name you application
	sAppName = "SM64 File Manager";
}

bool Example::OnUserCreate() {
	// Called once at the start, so create things here
    EEP_DAT::get().init(); //Init EEPROM
    if(EEP_DAT::get().isCorrupted()){
        perror("The executable has been corrupted. \nPlease compile a new copy. You can get the source code from \nhttps://github.com/sonich2401/SM64_Save_File_Converter\n");
        exit(-20);
    }

    current_slot = 0;
    cur_screen = nullptr;
    this->change_state = true;
    next_state = -1;

    cursor[0] = new pge::ren(paths[PNGS::CUR_OPEN]);
    cursor[1] = new pge::ren(paths[PNGS::CUR_CLOSED]);

        
    this->CreateLayer();
    this->CreateLayer();
    this->EnableLayer(1, true);
    this->EnableLayer(2, true);


    for(uint8 i = 0; i < this->GetLayers().size(); i++){
        this->SetDrawTarget(i);
        Clear(olc::Pixel(0,0,0,0));
    }
    this->SetDrawTarget(2);
    Clear(olc::GREY);
    this->SetDrawTarget((uint8)0);
        
	return true;
}

bool Example::OnUserUpdate(float fElapsedTime) {
    if(this->change_state){
        DrawStringDecal({ 0, 0 }, "Loading", olc::BLACK, { 10, 10 });
        if(cur_screen != nullptr)
            delete cur_screen;
        rman::get().clear();

        for(uint8 i = 0; i < this->GetLayers().size(); i++){
            this->SetDrawTarget(i);
            this->Clear(olc::Pixel(0,0,0,0));

            this->SetDrawTarget(2);
            Clear(olc::GREY);
            this->SetDrawTarget((uint8)0);
        }

        switch (next_state)
        {
        case 0:
            cur_screen = new main_screen(this, current_slot);
            break;
        case 1:
            cur_screen = new main_screen2(this, current_slot);
            break;
        case 2:
            cur_screen = new main_screen3(this, current_slot);
            break;
        case 3:
            cur_screen = new main_screen4(this, current_slot);
            break;
        case 4:
            cur_screen = new main_screen5(this, current_slot);
            break;
        case 5:
            cur_screen = new save_screen(this, current_slot);
            break;

        default:
            next_state = 0;
            return true;
            break;
        }

        this->change_state = false;
    }

    //Draw cursor
    this->SetDrawTarget((uint8)0);
    this->DrawDecal((GetMousePos() - olc::vf2d{10, 10}), cursor[GetMouse(0).bHeld]->dcl, {2,2});
    this->SetDrawTarget(1);

    if(GetKey(olc::Key::ESCAPE).bPressed){
        this->ChangeGamestate((uint8)0);
    }

        
    cur_screen->run(fElapsedTime);
	return true;
}

void Example::ChangeGamestate(uint8 state){
    this->next_state = (int8)state;
    this->change_state = true;
}






int main()
{
    #ifdef DEBUG
        for(string path : paths){
            string cmd = "ls " + path;
            system(cmd.c_str());
        }
    #endif
#ifdef _WIN32
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

	Example demo;
	if (demo.Construct(SCREEN_W, SCREEN_H, 1, 1, 0, true))
		demo.Start();
	return 0;
}