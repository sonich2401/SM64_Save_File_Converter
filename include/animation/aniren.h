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
#include "aniren.h"
#include <olcPixelGameEngine.h>

namespace pge {
	struct aniren {
		olc::Sprite* baseSpr = nullptr;
		olc::Decal* currentDisplay = nullptr;
		olc::PixelGameEngine* pge;

		aniren(olc::PixelGameEngine* olc);
		aniren();
		//aniren(const animation_package* package);

		struct frameList {
			float frameDurration;
			std::vector<olc::Sprite*> Frames;
		};
		std::map<std::string, frameList> States;
		std::string currentState;
		float timer = 0;
		unsigned int currentFrame = 0;

		void init(unsigned int width, unsigned int height);

		void init(olc::Sprite* p);

		void UpdateDecal(olc::Sprite* p);

		void  AddState(std::string StateName, std::vector<std::string> pathNames, float frameDir);

		void SetState(std::string stateName);

		void GetNextFrame(float fElapsedTime);



		~aniren();

	};
}