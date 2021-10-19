/*RenDev#2616 SM64SFM
    Copyright (C) 2021 RenDev

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
    Permission is also granted to not credit the author in any way as long as you do not take credit
    for this piece of software.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/
#include "ren.h"
//TODO: delete assert.h
#include <assert.h>


pge::ren::ren(std::string path) {
	this->spr = new olc::Sprite(path);
	this->dcl = new olc::Decal(this->spr);
	assert(this->spr->width != 0);
}

pge::ren::ren(olc::Sprite * ptr){
	this->spr = ptr;
	this->dcl = new olc::Decal(ptr);
	assert(this->spr->width != 0);
}


pge::ren::ren(unsigned int w, unsigned int h){
	this->spr = new olc::Sprite(w,h);
	this->dcl = new olc::Decal(this->spr);
	assert(this->spr->width != 0);
}

pge::ren::~ren() {
	delete dcl;
	delete spr;
}