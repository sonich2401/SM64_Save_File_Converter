#pragma once

#include "aniren.h"
#include "../dummy_texture.h"

//This class will take a list of path names and load them into memory
//Once this is done it will animate based on the gamestate that you named and the frame durrations
//DEPRECATED IN FAVOR OF SprSheet
namespace pge {
	struct aniren : public texture{
		olc::Sprite* baseSpr = nullptr;
		olc::Decal* currentDisplay = nullptr;
		olc::PixelGameEngine* pge;

		aniren(olc::PixelGameEngine* olc);
		aniren();
		aniren(const anipk * package);
		~aniren();

		struct frameList {
			float frameDuritation;
			std::vector<olc::Sprite*> Frames;
		};
		std::map<std::string, frameList> States;
		std::string currentState;
		float timer = 0;
		unsigned int currentFrame = 0;

		void init(unsigned int width, unsigned int height);
		void init(olc::Sprite* p);
		void UpdateDecal(olc::Sprite* p);
		void AddState(std::string StateName, std::vector<std::string> pathNames, float frameDir);
		void SetState(std::string stateName);
		void GetNextFrame(float fElapsedTime);		
	};
}
