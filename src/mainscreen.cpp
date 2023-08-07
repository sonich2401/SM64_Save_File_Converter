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
#include <olcPixelGameEngine.h>
#include <_typedefs.h>
#include "screendef.h"
#include <Sprite.h>

#include "EEPROM/EEPROM.h"
#include "screensize.h"
#include "pgeClass.h"

#include <resource/resource_manager.h>
#include <vector>




        main_screen::main_screen(Example * olc, uint8 current_slot) : screen(olc, current_slot){
            //Update EEP buffer
            EEP_DAT::get().update();


            scroll = -100;

            //Init paintings
            paintings[0] =  ADD_STATIC_REN(BOB);
            paintings[1] =  ADD_STATIC_REN(WF);
            paintings[2] =  ADD_STATIC_REN(JRB);
            paintings[3] =  ADD_STATIC_REN(CCM);
            paintings[4] =  ADD_STATIC_REN(BBH);
            paintings[5] =  ADD_STATIC_REN(LLL);
            paintings[6] =  ADD_STATIC_REN(SSL);
            paintings[7] =  ADD_STATIC_REN(HMC);
            paintings[8] =  ADD_STATIC_REN(DDD);
            paintings[9] =  ADD_STATIC_REN(WDW);
            paintings[10] = ADD_STATIC_REN(TTM);
            paintings[11] = ADD_STATIC_REN(TTC);
            paintings[12] = ADD_STATIC_REN(THI);
            paintings[13] = ADD_STATIC_REN(CCM);
            paintings[14] = ADD_STATIC_REN(RR);

            //init star animation frames
            colstars[0] = ADD_STATIC_SPRSHEET(RESOURCE_ENUM::UNSTAR_SHEET);
            colstars[1] = ADD_STATIC_SPRSHEET(RESOURCE_ENUM::STAR_SHEET);

            //Init coin animations
            coin = ADD_STATIC_SPRSHEET(RESOURCE_ENUM::C_FULL);

            //init arrow icons
            arrow[0] = ADD_STATIC_REN(A_0);
            arrow[1] = ADD_STATIC_REN(A_1);

            //bomb covers
            cannon[1] = ADD_STATIC_REN(BOMB);
            cannon[0] = ADD_STATIC_REN(BOMB_);

            //init menu buttons
            top = ADD_STATIC_REN(TOP);
            modify = ADD_STATIC_REN(MOD);
            toggle = ADD_STATIC_REN(TOGGLE);
            boolean[0] = ADD_STATIC_REN(_FALSE);
            boolean[1] = ADD_STATIC_REN(_TRUE);


            //Init Sub-Menu Icons
            toad_mips = ADD_STATIC_REN(RESOURCE_ENUM::TOAD_MIPS);
            bowser = ADD_STATIC_REN(RESOURCE_ENUM::BOWSER);
            peach_painting = ADD_STATIC_REN(RESOURCE_ENUM::PEACH);
            sign = ADD_STATIC_REN(RESOURCE_ENUM::SIGN);
            door = ADD_STATIC_REN(RESOURCE_ENUM::DOOR);

            //init Switch icons
            //pge::ren * box_off = );
            for(uint16 i = 0; i < 3; i++){
                for(uint8 i1 = 0; i1 < 2; i1++){
                    cap_switches[i][i1] = ADD_STATIC_REN(RESOURCE_ENUM(RESOURCE_ENUM::BLUE + (i * 2 + i1)));
                }
                cap_boxes[i][1] = ADD_STATIC_REN(RESOURCE_ENUM(RESOURCE_ENUM::BOX_VANISH + i));
                cap_boxes[i][0] = ADD_STATIC_REN(RESOURCE_ENUM::BOX_NONE);
            }

            //init Save Icons
            valid_save[0] = ADD_STATIC_REN(RESOURCE_ENUM::SAVE_NOT_VALID);
            valid_save[1] = ADD_STATIC_REN(RESOURCE_ENUM::SAVE_VALID);


        }

        void main_screen::run(float& fElapsedTime){
            if(draw_layer0()){ //Only draw other layers if there is no corruption
                draw_layer1();
                draw_layer2(fElapsedTime);
            }
        }

        bool main_screen::draw_layer0(){
            //Draw Titlebar
            pge->SetDrawTarget((uint8)0);
            if(corruption){
                pge->DrawStringDecal({0,0}, "Corruption Detected!\n Do you want to repair it? [n/y]",olc::BLACK, {3.4, 5});
                if(pge->GetKey(olc::Y).bPressed){
                    EEP_DAT::get().fix_corruption();
                    corruption = EEP_DAT::get().isCorrupted();
                }
                if(pge->GetKey(olc::N).bPressed)
                    corruption = false;
                
                return false;
            }
            return true;
        }

const string FILE_NAMES[4] = {"A:","B:", "C:", "D:"};
const uint16 SPACING = 200;

void main_screen::draw_layer1(){
    bool chosen = false;
    //Draw Titlebar
    pge->SetDrawTarget((uint8)1);
    pge->DrawDecal({0,0}, this->top->dcl);

    //Draw save Icons

            
    for(uint8 i = 0; i < 4; i++){
        bool is_valid_save = EEP_DAT::get().save_file_buffers[i].valid;
        uint8 star_count = (uint8)EEP_DAT::get().save_file_buffers[i].stars;

        //Grey out not selected lots
        olc::Pixel tint = olc::Pixel(100, 100, 100, 200);
        if(cur_slot == i)
            tint = olc::Pixel(255,255,255,255); //normal .png colors
                    
        pge->DrawDecal({float(i * SPACING + 150), 5}, valid_save[is_valid_save]->dcl, {1, 1}, tint); //{0.060, 0.060}
        pge->DrawStringDecal({float(i * SPACING + 150 + 85), 5 + 20}, FILE_NAMES[i] + " " + std::to_string(star_count), olc::BLACK, {2,2});
                
        //Check if icon was pressed
        if(pge->GetMouse(0).bPressed && !chosen){
            if(pge->GetMouseY() > 75)
                continue;
            if(pge->GetMouseX() > (i * SPACING + 150) && pge->GetMouseX() < ((i + 1) * SPACING + 150)){
                cur_slot = i;
                EEP_DAT::get().update();
            }
            if(pge->GetMouseX() < 120){
                chosen = true;
                if(pge->GetMouseY() < 75/2){
                    EEP_DAT::get().load();        
                    //corruption = EEP_DAT::get().isCorrupted();
                    EEP_DAT::get().update();
                    continue;
                }
                pge->ChangeGamestate(5);
            }
        }
    }
}

void main_screen::draw_layer2(float fElapsedTime){
    pge->SetDrawTarget(2);

    //Update animations
    colstars[0]->GetNextFrame(fElapsedTime);
    colstars[1]->GetNextFrame(fElapsedTime);

    coin->GetNextFrame(fElapsedTime);
            
    bool sprint_pressed = pge->GetKey(olc::CTRL).bHeld;
    const float SPEED_INCREASE = 1200;

    //Scroll the screen
    if(pge->GetMouseWheel() != 0){
        scroll += (scroll_spd + (sprint_pressed * SPEED_INCREASE)) * fElapsedTime * (pge->GetMouseWheel() < 0);
        scroll -= (scroll_spd + (sprint_pressed * SPEED_INCREASE)) * fElapsedTime * (pge->GetMouseWheel() > 0);
        if(scroll < -100){
            scroll = -100;
        }
        if(scroll > 2200){
            scroll = 2200;
        }
    }
  
    //find where to stop drawing paintings
    int8 min_y = (scroll/130) + 1;
    int8 max_y = ((scroll + SCREEN_H)/130) + 1;

    //clamp the values
    if(min_y < 0)
        min_y =0;
    if(max_y < 0)
        max_y = 0;
    if(max_y > 15)
        max_y = 15;
    if(min_y > 15)
        min_y = 15;

    //Draw all paitings in view
    const uint16 spacing = 130;
    const uint16 star_spacing = 80;
    const uint16 star_offset_x = 175;
    const uint16 star_offset_y = 25;
    #define GET_X_LINE_SPOT(x) ((float)(star_offset_x + (x * 80)))

    //printf("%i - %i = %i\n", (uint8)max_y, (uint8)min_y, ((uint8)max_y) - ((uint8)min_y));
    //Draws per line. Culling is active
    for(uint8 i = (uint8)min_y; i < (uint8)max_y; i++){
        pge->DrawDecal({20, (i * spacing) - scroll}, paintings[i]->dcl, {0.437, 0.437} );

        //Draw Stars
        uint8 starvals = EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.level_data.levels_indexed[i].byte;
        uint8 coin_count = (uint8)EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.coin_score_data.levels_indexed[i];
                
        for(uint8 i1 = 0; i1 < 9; i1++){
            bool star_val = (bool)(starvals & (1 << i1));
            olc::vf2d star_pos = {GET_X_LINE_SPOT(i1), (float32)((i * spacing) - scroll + star_offset_y)};
            if(i1 < 7){
                this->colstars[star_val]->Draw(star_pos, {0.2, 0.2});
                continue;
            }
            //last bit is the cannon bit
            if(i1 < 8){
                pge->DrawDecal(star_pos, this->cannon[!star_val]->dcl, {2, 2});
                continue;
            }
            //Draw Coin Count
            coin->Draw(star_pos, {1, 1});
            pge->DrawStringDecal({star_pos.x + star_spacing, star_pos.y - 10}, std::to_string(coin_count), olc::BLACK, {2,2});
            
            //Draw Arrows
                //Down
            pge->DrawDecal({star_pos.x + star_spacing, star_pos.y + 32}, arrow[1]->dcl, {0.5, 0.5});
                //Up
            pge->DrawDecal({star_pos.x + star_spacing + 32, star_pos.y + 32}, arrow[0]->dcl, {0.5, 0.5});
        }      
    }

    //Draw Switches

    Flags::named::h0x0B * cap_flags_byte = &EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.flags.Named.ProgressFlags;
    bool cap_states[3] = {cap_flags_byte->VanishCapSwitch, cap_flags_byte->MetalCapSwitch, cap_flags_byte->WingCapSwitch};

    float cap_y = (15 * spacing) - scroll + star_offset_y; //15 is the next index after RR stars in the menu
    if(cap_y - scroll < 0){ //Dont draw unless you can see it
            
        pge->DrawStringDecal({10, cap_y + 25}, "Unlocked Caps", olc::BLACK, {1.5, 1.80});

        for(uint8 i = 0; i < 3; i++){
            float cap_x = GET_X_LINE_SPOT(i);
            pge->DrawDecal({cap_x, cap_y}, cap_switches[i][cap_states[i]]->dcl, {2, 2});
            pge->DrawDecal({cap_x + 16, cap_y - 48}, cap_boxes[i][cap_states[i]]->dcl);
        }

        //Draw Icon links to other menus
        float icon_y = (16 * spacing) - scroll + star_offset_y;
        pge->DrawDecal({20, icon_y}, peach_painting->dcl, {1.5, 1.5});
        pge->DrawStringDecal({star_offset_x, icon_y + 32}, "Castle Secret Stars", olc::BLACK, {2,2});

        icon_y += spacing; //move to next row
        pge->DrawDecal({20, icon_y}, toad_mips->dcl, {1, 1});
        pge->DrawStringDecal({star_offset_x, icon_y + 32}, "Mips & Toad Stars", olc::BLACK, {2,2});

        icon_y += spacing; //move to next row
        pge->DrawDecal({20, icon_y + 32}, sign->dcl, {3, 3});
        pge->DrawStringDecal({star_offset_x, icon_y + 64}, "Game State Flags", olc::BLACK, {2,2});

        icon_y += spacing; //move to next row
        pge->DrawDecal({40, icon_y + 32}, door->dcl, {1, 1});
        pge->DrawStringDecal({star_offset_x, icon_y + 64}, "Opened Doors", olc::BLACK, {2,2});

        icon_y += spacing; //move to next row
        pge->DrawDecal({32, icon_y + 32}, cannon[1]->dcl, {2.5, 2.5});
        pge->DrawStringDecal({star_offset_x, icon_y + 64}, "Restore Backup", olc::BLACK, {2,2});
            
    }
            
    //Check for events

    //Check for clicking
    if(pge->GetMouse(0).bPressed){
        if(pge->GetMouseY() <= 75)
            return;

        olc::vf2d mPos = pge->GetMousePos();

        if(mPos.x > star_offset_x){ //check if cliicking stars
            uint8 index_x = (mPos.x - star_offset_x) / star_spacing;
            uint8 index = ((float)(mPos.y + this->scroll)/ spacing);
            char* prim; //case 20
            char* sec; //Case 20
            switch (index) {
                case 15: //Cap switches were clicked
                    if(!(index_x < 3)) break;
                    switch (index_x) { //couldnt make this a array lookup because you cant take a address of a bitfeild
                        case 0: //vanish cap
                            cap_flags_byte->VanishCapSwitch ^= 1; //toggle bit
                        break;
                        case 1: //metal cap
                            cap_flags_byte->MetalCapSwitch ^= 1; //toggle bit
                        break;
                        case 2: //wing cap
                            cap_flags_byte->WingCapSwitch ^= 1; //toggle bit
                        break;
                    }
                break;

                case 19:
                case 18:
                case 17:
                case 16: //castle stars were clicked
                    if(!(index_x < 3)) break;
                            
                    pge->ChangeGamestate(index - 15);
                break;

                //Restore backup option was selected
                case 20:
                    prim = (char*)EEP_GET_SAVE(cur_slot);
                    sec = (char*)&EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][1];
                    memcpy(prim, (void*)sec, sizeof(Save));
                break;
                            
                default: //Stars were clicked
                    if(index > 15 || index < 0)
                        break;
                    uint8 * byte = &EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.level_data.levels_indexed[index].byte;
                    if(index_x < 8){
                        *byte ^= 1 << index_x; //toggle star via XOR
                    }else{
                        index_x -= 9;
                                
                        const uint8 COIN_SHIFT_SPEED = 10;
                        if(index_x < 2){
                                if (pge->GetMouseX() > GET_X_LINE_SPOT(10) - (star_spacing / 2))
                                    EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.coin_score_data.levels_indexed[index] += 1 + (sprint_pressed * COIN_SHIFT_SPEED);
                                else
                                    EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.coin_score_data.levels_indexed[index] -= 1 + (sprint_pressed * COIN_SHIFT_SPEED);
                        }
                    }

                    break;
            }
        }

        //Update the EEP because a action happend
        EEP_DAT::get().update();
    }
}



main_screen::~main_screen(){
    delete this->coin;
    delete this->colstars[0];
    delete this->colstars[1];

    rman::get().unload_texture(this->arrow[0]);
    rman::get().unload_texture(this->arrow[1]);
    rman::get().unload_texture(this->boolean[0]);
    rman::get().unload_texture(this->boolean[1]);
    rman::get().unload_texture(this->bowser);
    rman::get().unload_texture(this->cannon[0]);
    rman::get().unload_texture(this->cannon[1]);

    for(int i = 0; i < 3; i++){
        rman::get().unload_texture(this->cap_boxes[i][0]);
        rman::get().unload_texture(this->cap_boxes[i][1]);

        rman::get().unload_texture(this->cap_switches[i][0]);
        rman::get().unload_texture(this->cap_switches[i][1]);
    }

    rman::get().unload_texture(this->door);
    rman::get().unload_texture(this->modify);
    
    for(int i = 0; i < 15; i++){
        rman::get().unload_texture(this->paintings[i]);
    }

    rman::get().unload_texture(this->peach_painting);
    rman::get().unload_texture(this->sign);
    rman::get().unload_texture(this->toad_mips);
    rman::get().unload_texture(this->toggle);
    rman::get().unload_texture(this->top);
    rman::get().unload_texture(this->valid_save[0]);
    rman::get().unload_texture(this->valid_save[1]);
}
