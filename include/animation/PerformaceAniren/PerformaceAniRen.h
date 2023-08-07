#pragma once

#include "../dummy_texture.h"
#include "../ren/ren.h"

namespace pge {
	//This class is the exact same as aniren but uses more memory. This is because aniren
	//has all sprites loaded but the display is contained in 1 decal.
	//Instead, PerformanceAniRen will swap out a decal pointer so it will display that
	//instead of a single decal instance
	struct PerformaceAniRen : public texture {
		struct FrameList {
			float FrameDuritation;
			std::vector<pge::ren*> Frames;
		};
		std::map<std::string, FrameList>States;
		std::string currentState;
		float timer = 0;
		unsigned int currentFrame = 0;
		void  AddState(std::string StateName, std::vector<std::string> pathNames, float frameDir);
		void SetState(std::string stateName);
		olc::Decal* GetNextFrame(float fElapsedTime);
		~PerformaceAniRen();

	};
}