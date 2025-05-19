#pragma once

#include <olcPixelGameEngine.h>
#include "../animation/dummy_texture.h"
#include "../animation/Sprite.h"

struct resource {
	inline resource(const anipk* __restrict__  pac, pge::texture* __restrict__ dat){
		this->id = pac->rid;
		this->type = pac->type;
		this->dat = dat;
		this->ref_count = 1;
	}
	
	RESOURCE_ENUM id;
	TEX_TYPE type; //What type of resouce is this?
	pge::texture* dat = nullptr; //Pointer to the raw data in memory
	unsigned int ref_count;

	void deconstruct(){
		switch(type){
			case STATIC:
				delete ((pge::ren*)dat);
			break;

			case TILESET:
				delete ((pge::Tileset*)dat);
			break;

			default:
			break;
		}
	}
};

class rman;
extern rman* inref;


class rman {
public:
	//rman() {}
	static rman& get() {
		return *inref;
	}
private:
	std::vector<resource> resources;

public:
	olc::PixelGameEngine* pge = nullptr;
public:

public:
	void init(olc::PixelGameEngine* olc);

	//add_texture() - Will load a texture and return the index for that resource
	//if the texture already exists it will return the index of the texture instead.
	//Has 
	unsigned int add(RESOURCE_ENUM id, const bool& skip_dup_check = false);

	//this does the same thing as load_texture but will return a pointer to the data rather than a index
	pge::texture* load(RESOURCE_ENUM id);

	void unload_texture(RESOURCE_ENUM id);
	void unload_texture(pge::texture* tex);

	//void unload_texture(unsigned int index);

	RESOURCE_ENUM get_res_from_ptr(const pge::texture* __restrict__ o_ptr);

public:
	rman(rman const&) = delete;
	void operator=(rman const&) = delete;
public:
	explicit rman();
	~rman();
};


#define ADD_REN(id) ((pge::aniren*)(rman::get().load(id)))
#define ADD_STATIC_REN(id) ((pge::ren*)(rman::get().load(id)))
#define ADD_STATIC_SPRSHEET(id) ((pge::SprSheet*)(rman::get().load(id)))
