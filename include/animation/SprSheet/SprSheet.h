#pragma once
#include "../dummy_texture.h"
#include "../ren/ren.h"
#include <olcPixelGameEngine.h>

#ifndef ANIMATION_ID_DEFINED
	#define ANIMATION_ID_DEFINED
	typedef unsigned int Animation_id;
#endif

//This is a important class. This class is able to load a sprite sheet and
//draw only a single sprite in that sheet. You can draw by index or (eventually) coordinate.
//For example, if i had a 3x4 sprite sheet like so
/*
	% % %
	% % %
	% % %
	% % %
*/
//If we choose index 4 it will choose the sprite indicated with a '&' symbol
/*
	% % %
	% & %
	% % %
	% % %
*/
//TODO: Another way of getting the same result is doing it by 2D coordinates.
//Let's try to accsess the same sprite. This is done by choosing point (1, 1)
//Just note that this takes a bit of extra processing so if you are looking for
//speed use indexing



namespace pge {
	struct SprSheet : public texture {
		pge::ren * sprSheet;
		olc::vi2d spr_sheet_wh; //How big is the sprite?
		olc::PixelGameEngine* pge;

		SprSheet(const std::string& sheet_fp, const olc::vi2d& wh);
		SprSheet(RESOURCE_ENUM sheet_id, const olc::vi2d& wh);
		SprSheet(olc::Sprite* __restrict__ sheet, const olc::vi2d& wh);
		SprSheet();
		SprSheet(const anipk_SprSheet* package);
		~SprSheet();

		
		struct frameList {
			float frameDuritation;
			std::vector<unsigned short int> Frame_ids;
		};

		std::vector<frameList> States;
		Animation_id currentState;
		unsigned long int currentFrame = 0;
		float timer = 0.0f;

		void init(pge::ren* __restrict__, const olc::vi2d& wh);

		void init(const std::string& sheet_fp, const olc::vi2d& wh);

		void HotSwap(olc::Sprite* new_spr);

		void UpdateDecal(unsigned int cur_frame);

		void  AddState(Animation_id StateID, const std::vector<unsigned short int>& frame_ids, const float& frameDir);

		void SetState(Animation_id StateID);
		
		void GetNextFrame(const float& fElapsedTime);
		
    
    std::array<olc::vf2d, 2> GetFrameCords();

    void Draw(const olc::vf2d& pos, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE);
	};
};