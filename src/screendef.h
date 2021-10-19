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
#pragma once
#include <olcPixelGameEngine.h>
#include <_typedefs.h>
#include "pgeClass.h"

class Example;

class screen{
    public:

        uint8 cur_slot;


        screen(Example * olc, uint8 current_slot){
            pge = olc;
            cur_slot = current_slot;
        }

        void init(Example * olc){
            pge = olc;
        }
    public:
        virtual void run(float& fElapsedTime){
            //do crap
        }
    public:
        Example * pge;

        virtual ~screen() {
        }
};


class main_screen : public screen{
    public:
        float scroll = 0;
        const float scroll_spd = 240 * 10;
        bool corruption = false;

        pge::ren * paintings[15]; //pge::ren paintings[15]

        //Star animations
        pge::SprSheet * colstars[2];

        //Coin animation
        pge::SprSheet * coin;

        //Menu Buttons
        pge::ren * arrow[2]; //pge::ren arrow[2]

        pge::ren * top;
        pge::ren * toggle;
        pge::ren * modify;
        pge::ren * cannon[2]; //pge::ren cannon[2]
        pge::ren * boolean[2];
        pge::ren * toad_mips;
        pge::ren * bowser;
        pge::ren * peach_painting;
        pge::ren * sign;
        pge::ren * door;

        pge::ren * cap_switches[3][2];
        pge::ren * cap_boxes[3][2];
        pge::ren * valid_save[2];

        


    public:
        main_screen(Example * olc, uint8 current_slot);

        void run(float& fElapsedTime);

        bool draw_layer0();
        void draw_layer1();
        void draw_layer2(float fElapsedTime);
};

class main_screen2 : public screen {
    public:
        main_screen2(Example* p, uint8 slot);
        void run(float& fElapsedTime);
};

class main_screen3 : public screen {
    public:
        main_screen3(Example* p, uint8 slot);
        void run(float& fElapsedTime);


};

class main_screen4 : public screen {
    public:
        main_screen4(Example* p, uint8 slot);
        void run(float& fElapsedTime);


};

class main_screen5 : public screen {
    public:
        main_screen5(Example* p, uint8 slot);
        void run(float& fElapsedTime);


};

class save_screen : public screen {
    public:
        save_screen(Example* p, uint8 slot);
        void run(float& fElapsedTime);
    private:
        pge::ren * n64;
        pge::ren * pc;
    public:
        ~save_screen();
};