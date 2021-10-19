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
#include "ren.h"
#include <olcPixelGameEngine.h>

namespace pge {
	struct SprSheet{
		pge::ren * sprSheet;
		olc::vi2d spr_sheet_wh; //How big is the sprite?
		olc::PixelGameEngine* pge;

		SprSheet(olc::PixelGameEngine* olc, std::string sheet_fp, olc::vi2d wh);
		SprSheet(olc::PixelGameEngine* olc, olc::Sprite* sheet, olc::vi2d wh);
		SprSheet();
		//SprSheet(const anipk_SprSheet* package);
		~SprSheet();

		struct frameList {
			float frameDuritation;
			std::vector<unsigned short int> Frame_ids;
		};
		std::map<std::string, frameList> States;
		std::string currentState;
		float timer = 0;
		unsigned int currentFrame = 0;

		void init(olc::Sprite* p);

		void init(olc::PixelGameEngine* olc, std::string sheet_fp, olc::vi2d wh);

		void HotSwap(olc::Sprite* new_spr);

		void UpdateDecal(unsigned int cur_frame);

		void  AddState(std::string StateName, std::vector<unsigned short int> frame_ids, float frameDir);

		void SetState(std::string stateName);

		void GetNextFrame(float fElapsedTime);

    std::array<olc::vf2d, 2> GetFrameCords();

    void Draw(const olc::vf2d& pos, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE);
	};
}