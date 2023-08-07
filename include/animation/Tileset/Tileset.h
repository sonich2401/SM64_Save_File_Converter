#pragma once

#include "../dummy_texture.h"
#include "../ren/ren.h"

//This is a important class. This class is able to load a Tileset and
//draw only a single tile in that sheet. You can draw by index or by coordinate.
//For example, if i had a 3x4 tileset like so
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
//Another way of getting the same result is doing it by 2D coordinates.
//Let's try to accsess the same tile. This is done by choosing point (1, 1)
//Just note that indexing takes a bit of extra processing so if you are looking for
//speed use coordinates
namespace pge {
	struct Tileset : texture {
		olc::PixelGameEngine* pge = nullptr;
		pge::ren* sheet = nullptr;
		olc::vi2d dimentions = { 0,0 };

		Tileset(olc::PixelGameEngine* olc, std::string file_path, olc::vi2d sprite_dimentions);
		Tileset(anipk_tileset * r);
		~Tileset();

		void DrawTile(float x, float y, unsigned int index, olc::vf2d scale = { 1,1 });
		void DrawTile(float x, float y, olc::vi2d tile_cords, olc::vf2d scale = { 1,1 });
	};
}