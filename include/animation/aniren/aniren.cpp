#include "aniren.h"
#include <resource/resource_manager.h>
#include <animation/dummy_texture.h>

pge::aniren::aniren(olc::PixelGameEngine* olc) {
	pge = olc;
}

pge::aniren::aniren() {
}

pge::aniren::aniren(const anipk* package)
{
	anipk_aniren * pk = (anipk_aniren *)(void*)package;

	pge = rman::get().pge;

	init(pk->spr_size.x, pk->spr_size.y);

	for (animation_aniren animaniac : pk->anis)
		AddState(animaniac.name, animaniac.path, animaniac.dur_of_frame);
}

void pge::aniren::init(unsigned int width, unsigned int height)
{
	baseSpr = new olc::Sprite(width, height);
	currentDisplay = new olc::Decal(baseSpr);
}

void pge::aniren::init(olc::Sprite* p)
{
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
	for (unsigned int i = 0; i < pathNames.size(); i++)
		tmpS.push_back(new olc::Sprite(pathNames[i]));
	frameList tmp = { frameDir, tmpS };
	States[StateName] = tmp;
	currentState = StateName;
	if (this->currentDisplay == nullptr)
		init(tmpS.front());
	UpdateDecal(States[currentState].Frames[currentFrame]);
}

void pge::aniren::SetState(std::string stateName) {
	currentState = stateName;
	// currentFrame = 0;
	UpdateDecal(States[currentState].Frames[currentFrame]);
	// timer = 0;
}

void pge::aniren::GetNextFrame(float fElapsedTime) {
	timer += fElapsedTime;

	if (timer > States[currentState].frameDuritation) {
		currentFrame++;
		timer = 0;

		if (currentFrame == States[currentState].Frames.size())
			currentFrame = 0;

		UpdateDecal(States[currentState].Frames[currentFrame]);
	}
}


pge::aniren::~aniren() {
	for(std::map<std::string, frameList>::iterator it = States.begin(); it != States.end(); it++)
		for (auto& ptr : it->second.Frames)
			delete ptr;
	delete currentDisplay;
	delete baseSpr;
}