#include "ren.h"


pge::ren::ren(std::string path) {
	this->spr = new olc::Sprite(path);
	this->dcl = new olc::Decal(this->spr);
}

pge::ren::ren(olc::Sprite * ptr){
	this->spr = ptr;
	this->dcl = new olc::Decal(ptr);
}

pge::ren::ren(const unsigned char* bytes, size_t size){
	this->spr = new olc::Sprite(bytes, size);
	#ifdef DEBUG
		if(this->spr->width == 0){
			fprintf(stderr, "ERR: Sprite width is 0! This means that the bytes are corrupted!!!\n");
		}
	#endif
	this->dcl = new olc::Decal(spr);
}

pge::ren::ren(anipk * ptr){
	#if USE_STATIC_FILES
	this->spr = new olc::Sprite(ptr->s_file->data, ptr->s_file->size);
	#else
	this->spr = new olc::Sprite(*ptr->s_file);
	#endif
	this->dcl = new olc::Decal(this->spr);
	this->dcl->Update();
}

pge::ren::ren(unsigned int w, unsigned int h){
	this->spr = new olc::Sprite(w,h);
	this->dcl = new olc::Decal(this->spr);
}

pge::ren::~ren() {
	delete dcl;
	delete spr;
}