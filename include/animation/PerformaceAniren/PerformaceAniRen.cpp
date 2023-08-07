#include "./PerformaceAniRen.h"

void pge::PerformaceAniRen::AddState(std::string StateName, std::vector<std::string> pathNames, float frameDir) {
	std::vector<pge::ren*> tmpS;
	for (unsigned int i = 0; i < pathNames.size(); i++) {
		tmpS.push_back(new pge::ren(pathNames[i]));
	}
	FrameList tmp = { frameDir,tmpS };
	States[StateName] = tmp;
	currentState = StateName;
}

void pge::PerformaceAniRen::SetState(std::string stateName) {
	currentState = stateName;
	currentFrame = 0;
	timer = 0;
}

olc::Decal* pge::PerformaceAniRen::GetNextFrame(float fElapsedTime) {
	timer += fElapsedTime;
	if (timer > States[currentState].FrameDuritation) {
		currentFrame++;
		timer = 0;
		if (currentFrame == States[currentState].Frames.size()) {
			currentFrame = 0;
		}
	}
	return States[currentState].Frames[currentFrame]->dcl;
}

pge::PerformaceAniRen::~PerformaceAniRen() {
	std::map<std::string, FrameList>::iterator it = States.begin();
	while (it != States.end())
	{
		for (auto& ptr : it->second.Frames)
			delete ptr;
		it++;
	}
}