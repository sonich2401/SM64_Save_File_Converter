#include <resource/resource_manager.h>

struct resource;

#include <olcPixelGameEngine.h>
#include <animation/Sprite.h>
#include <animation/dummy_texture.h>
#include <map>
#include <resource/resources.h>
#include <iostream>


static rman only_allowed_instance = rman();
rman* inref;


//TODO: make the rman use a global pointer instead of using static get to make it faster

//TODO: Replace the vector in RMAN with an array so that a O(1) lookup table can be used to see if a resource is alloced or not


void rman::init(olc::PixelGameEngine* __restrict__ olc) {
	this->pge = olc;
}

// load_texture() will load a texture and return the index for that resource
// If the texture already exists it will return the index of the texture instead.
unsigned int rman::add(RESOURCE_ENUM id, const bool& skip_dup_check) { //wh is only used for SpriteSheets
	if(!skip_dup_check){
		for (unsigned int i = 0; i < resources.size(); i++){
			if (resources[i].id == id){
				resources[i].ref_count++;
				return i;
			}
		}
	}

	anipk* r = (anipk*)(void*)RESOURCES[id];

	switch (r->type) {
	case STATIC:
		this->resources.emplace_back(r, new pge::ren(r));
		break;
	case ANIMATED:
		this->resources.emplace_back(r, new pge::aniren((anipk_aniren*)r));
		break;
	//Currently depricated
	/*case SPRITE_SHEET:
		(void)this->load(((anipk_SprSheet*)r)->reference_textue);
		this->resources.emplace_back(r, new pge::SprSheet((anipk_SprSheet*)r));
		break;*/
	case TILESET:
		this->resources.emplace_back(r, new pge::Tileset((anipk_tileset*)r));
		break;
	default:
		#ifdef DEBUG
			fprintf(stderr, "Not A valid Resource Type! resource_manager.cpp");
			abort();
		#endif
		break;
	}

	return resources.size() - 1;
}

// This does the same thing as load_texture but will return a pointer to the data rather than a index
pge::texture* rman::load(RESOURCE_ENUM id) { // wh is only used for SpriteSheets
	anipk* r = (anipk*)(void*)RESOURCES[id];

	size_t id_of_resource;
	switch(r->type){
		case SPRITE_SHEET:
			return new pge::SprSheet((anipk_SprSheet*)r);
		break;
		
		case TILESET:
			id_of_resource = this->add(id, false);
			return resources[id_of_resource].dat;
		break;

		case ANIMATED:
			return new pge::aniren((anipk_aniren*)r);
		break;

		case STATIC:
			id_of_resource = this->add(id, false);
			return resources[id_of_resource].dat;
		break;
	}

	return nullptr;
}

void rman::unload_texture(RESOURCE_ENUM id) {
	for(unsigned int i = 0; i < this->resources.size(); i++){
		if(this->resources[i].id == id){
			if(this->resources[i].ref_count > 1){
				this->resources[i].ref_count--;
				return;
			}else{
				this->resources[i].deconstruct();
				this->resources.erase(this->resources.begin() + i);
				return;
			}
		}
	}
	#ifdef DEBUG
		fprintf(stderr, "ERR: Texture %i is not a texture that was loaded via the resource manager!\n", id);
		abort();
	#endif
}

void rman::unload_texture(pge::texture* tex){
	for(unsigned int i = 0; i < this->resources.size(); i++){
		if(this->resources[i].dat == tex){
			if(this->resources[i].ref_count > 1){
				this->resources[i].ref_count--;
				return;
			}else{
				this->resources[i].deconstruct();
				this->resources.erase(this->resources.begin() + i);
				return;
			}
		}
	}
	#ifdef DEBUG
		fprintf(stderr, "ERR: Texture %p is not a texture that was loaded via the resource manager!\n", tex);
		fprintf(stderr, "Attempting translation ...\nAssuming it was a pge::ren* ...\n");
		fprintf(stderr, "size w = %lu, h = %lu\n", ((pge::ren*)tex)->spr->width, ((pge::ren*)tex)->spr->height);
		abort();
	#endif
}

const RESOURCE_ENUM rman::get_res_from_ptr(const pge::texture* __restrict__ o_ptr){
	for(const auto& ele : this->resources){
		if(ele.dat == (pge::texture*)o_ptr){
			return ele.id;
		}
	}
	return RESOURCE_ENUM::INVALID_RESOURCE;
}

rman::rman() {
	inref = &only_allowed_instance;
}

rman::~rman() {
	#ifdef DEBUG
		fprintf(stderr, "INFO: Resources allocated at shutdown %lu\n", this->resources.size());
		for(size_t i = 0; i < this->resources.size(); i++){
			fprintf(stderr, "### ELEMENT %lu ###\n\tID: %lu\n\tReference count %lu\n\n", i, this->resources[i].id, this->resources[i].ref_count);
		}

	#endif
}
