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
#include "aniren.h"
//#include "../../resource/resource_manager.h"
#include <cassert>

pge::aniren::aniren(olc::PixelGameEngine* olc) {
	pge = olc;
}

pge::aniren::aniren() {

}


void pge::aniren::init(unsigned int width, unsigned int height) {
	baseSpr = new olc::Sprite(width, height);
	currentDisplay = new olc::Decal(baseSpr);
}

void pge::aniren::init(olc::Sprite* p) {
	baseSpr = new olc::Sprite(p->width, p->height);
	currentDisplay = new olc::Decal(baseSpr);
}

void pge::aniren::UpdateDecal(olc::Sprite* p)
{
	// Draw the sprite to the current frame sprite
	pge->SetDrawTarget(baseSpr);
	pge->Clear(olc::Pixel(0, 0, 0, 0));
	pge->DrawSprite(0, 0, p);
	pge->SetDrawTarget(nullptr);

	// Update Decal Texture
	currentDisplay->Update();
}

void  pge::aniren::AddState(std::string StateName, std::vector<std::string> pathNames, float frameDir) {
	std::vector<olc::Sprite*> tmpS;
	for (unsigned int i = 0; i < pathNames.size(); i++) {
		tmpS.push_back(new olc::Sprite(pathNames[i]));
	}
	frameList tmp = { frameDir, tmpS };
	States[StateName] = tmp;
	currentState = StateName;
	if (this->currentDisplay == nullptr) {
		init(tmpS.front());
	}
	UpdateDecal(States[currentState].Frames[currentFrame]);
}

void pge::aniren::SetState(std::string stateName) {
	currentState = stateName;
	//currentFrame = 0;
	UpdateDecal(States[currentState].Frames[currentFrame]);
	//timer = 0;
}

void pge::aniren::GetNextFrame(float fElapsedTime) {
	timer += fElapsedTime;
	if (timer > States[currentState].frameDurration) {
		currentFrame++;
		timer = 0;
		if (currentFrame == States[currentState].Frames.size()) {
			currentFrame = 0;
		}
		//clamp(currentFrame, 0, States[currentState].Frames.size());
#ifdef DEBUG
		assert(States[currentState].Frames.size() != 0);
#endif
		UpdateDecal(States[currentState].Frames[currentFrame]);
	}
}


pge::aniren::~aniren() {
	delete currentDisplay;
	delete baseSpr;
	std::map<std::string, frameList>::iterator it = States.begin();
	while (it != States.end())
	{
		for (auto& ptr : it->second.Frames)
			delete ptr;
		it++;
	}
}