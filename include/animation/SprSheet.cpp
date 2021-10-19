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
#include "SprSheet.h"
#include <assert.h>

pge::SprSheet::SprSheet(olc::PixelGameEngine* olc, std::string sheet_fp, olc::vi2d wh) {
	pge = olc;
	spr_sheet_wh = wh;
	//printf("WH = %s\n", wh.str().c_str());
	sprSheet = new pge::ren(sheet_fp);
}

pge::SprSheet::SprSheet(olc::PixelGameEngine* olc, olc::Sprite* sheet, olc::vi2d wh) {
	pge = olc;
	spr_sheet_wh = wh;
	sprSheet = new pge::ren(sheet);
}

pge::SprSheet::SprSheet() { }

void pge::SprSheet::init(olc::Sprite* p) {
  assert(10000 == 10);
	//currentDisplay = new olc::Decal(baseSpr);
}

void pge::SprSheet::init(olc::PixelGameEngine* olc, std::string sheet_fp, olc::vi2d wh) {
	pge = olc;
	spr_sheet_wh = wh;
	sprSheet = new pge::ren(sheet_fp);
}

void pge::SprSheet::HotSwap(olc::Sprite* new_spr) {
	sprSheet->spr = new_spr;
  sprSheet->dcl->Update();
}

void pge::SprSheet::AddState(std::string StateName, std::vector<unsigned short int> frame_ids, float frameDir) {
	frameList tmp = { frameDir, frame_ids };
	States[StateName] = tmp;
	currentState = StateName;
	//UpdateDecal(States[currentState].Frame_ids[currentFrame]);
}

void pge::SprSheet::SetState(std::string stateName) {
	currentState = stateName;
	//currentFrame = 0;
	//UpdateDecal(States[currentState].Frame_ids[currentFrame]);
	//timer = 0;
}



void Tick(pge::SprSheet * ptr, float fElapsedTime){
  ptr->timer += fElapsedTime;
	if (ptr->timer > ptr->States[ptr->currentState].frameDuritation) {
		ptr->currentFrame++;
		ptr->timer = 0;
		if (ptr->currentFrame == ptr->States[ptr->currentState].Frame_ids.size())
			ptr->currentFrame = 0;
		//clamp(currentFrame, 0, States[currentState].Frames.size());
#ifdef DEBUG
		assert(ptr->States[ptr->currentState].Frame_ids.size() != 0);
#endif
  }
}




void pge::SprSheet::GetNextFrame(float fElapsedTime) {
  Tick(this, fElapsedTime);
//UpdateDecal(States[currentState].Frame_ids[currentFrame]);
}

std::array<olc::vf2d, 2> pge::SprSheet::GetFrameCords(){
  int cur_frame = States[currentState].Frame_ids[currentFrame];
  
  int oned_pos = (cur_frame * spr_sheet_wh.x);
  int offy = ((int)(oned_pos / sprSheet->spr->width)) * spr_sheet_wh.y;
  int offx = (int)(oned_pos % sprSheet->spr->width);

  return {{{(float)offx, (float)offy}, spr_sheet_wh}};
}

void pge::SprSheet::Draw(const olc::vf2d& pos, const olc::vf2d& scale , const olc::Pixel& tint){
	//int cur_frame = States[currentState].Frame_ids[currentFrame];
  
	//int offy = ((int)((cur_frame * spr_sheet_wh.x) / sprSheet->spr->width)) * spr_sheet_wh.x;
	//int offx = (int)((cur_frame * spr_sheet_wh.x) % sprSheet->spr->width); // use % to get rid of tiles beyond the widht size

	pge->DrawPartialDecal(pos, sprSheet->dcl, GetFrameCords()[0], spr_sheet_wh, scale, tint);
}

pge::SprSheet::~SprSheet() {
	delete sprSheet;
}