#pragma once

#include "../dummy_texture.h"

//This class is a basic texture type. It contains the sprite information
//and the GPU object. You can allocate any texture using a 'anipk' which
//is a struct that contains all of the necessary information to construct
//an object. Ofc you can construct it manually as well by passing in a path
//or a Sprite object
namespace pge {
	struct ren : public texture {
		olc::Decal* dcl;
		olc::Sprite* spr;
		ren(std::string path);
		ren(const unsigned char* bytes, size_t size);
		ren(olc::Sprite * ptr);
		ren(anipk * ptr);
		ren(unsigned int w, unsigned int h);
		~ren();
	};
}