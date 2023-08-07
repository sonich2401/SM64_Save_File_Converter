#pragma once

#include <olcPixelGameEngine.h>
#include <string>
#include <vector>

#include <resource/resources.h>

#ifndef ANIMATION_ID_DEFINED
	#define ANIMATION_ID_DEFINED
	typedef unsigned int Animation_id;
#endif

#ifndef ANI_STRUCT_DEF
	#define ANI_STRUCT_DEF

		enum TEX_TYPE {
			STATIC = 0b000,
			ANIMATED = 0b001,
			SPRITE_SHEET = 0b010,
			TILESET = 0b011
		};


		//This is used to construct animations for aniren
		struct animation_aniren{
			std::string name;
			float dur_of_frame;
			std::vector<std::string> path;
		};

		//This is used to construct animations for SprSheets
		struct animation_SprSheet{
			float dur_of_frame;
			std::vector<unsigned short> index;
		};

	
	//Base class for constructing objects with constant data
	struct anipk {
		anipk(RESOURCE_ENUM id, const static_file* __restrict__ file, TEX_TYPE t){
			this->rid = id;
			this->s_file = (static_file*)file;

			this->type = t;
		}
		anipk(){}
		RESOURCE_ENUM rid;
		union{
			static_file* s_file;
			RESOURCE_ENUM reference_textue; //For objects that 
		};
		TEX_TYPE type;
	};

	//Struct for constructing anirens
	struct anipk_aniren : anipk{
		anipk_aniren(RESOURCE_ENUM id, const static_file* __restrict__ file, TEX_TYPE t, olc::vi2d size, std::vector<animation_aniren> ani) : anipk(id, file, t){
			this->spr_size = size;
			this->anis = ani;
		}
		olc::vi2d spr_size;
		std::vector<animation_aniren> anis;
	};

	//Struct for constructing Sprite Sheets
	struct anipk_SprSheet : anipk{
		anipk_SprSheet(RESOURCE_ENUM id, RESOURCE_ENUM rid, TEX_TYPE t, olc::vi2d size, std::vector<animation_SprSheet> ani) : anipk() {
			this->spr_size = size;
			this->anis = ani;
			this->rid = id;
			this->type = t;
			this->reference_textue = rid;
			this->spr_size = size;
			this->anis = ani;
		}
		olc::vi2d spr_size;
		std::vector<animation_SprSheet> anis;
	};


	//Struct for creating tilesets
	struct anipk_tileset : anipk{
		anipk_tileset(RESOURCE_ENUM id, const static_file* __restrict__ file, TEX_TYPE t, olc::vi2d size) : anipk(id, file, t){
			this->tile_size = size;
		}
		olc::vi2d tile_size;
	};
#endif

namespace pge {
	struct texture {
		// Used for polymorphism (no void* and static casts that way)
		
		virtual ~texture(){}
	};
}
