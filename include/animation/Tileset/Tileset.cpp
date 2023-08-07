#include "Tileset.h"
#include <resource/resource_manager.h>

//Same as SprSheet but doesnt animate
pge::Tileset::Tileset(olc::PixelGameEngine* olc, std::string file_path, olc::vi2d sprite_dimentions) {
	this->pge = olc;
	sheet = new pge::ren(file_path);
	dimentions = sprite_dimentions;
	fprintf(stderr, "ERR: DONT USE THIS CONSTRUCTOR\n");
	abort();
}

pge::Tileset::Tileset(anipk_tileset * r){
	this->pge = rman::get().pge;
	#if USE_STATIC_FILES
		this->sheet = new pge::ren(r->s_file->data, r->s_file->size);
	#else
		this->sheet = new pge::ren(*(char**)r->s_file);
	#endif
	this->dimentions = r->tile_size;
};

void pge::Tileset::DrawTile(float x, float y, unsigned int index, olc::vf2d scale) {
	int offy = ((int)((index * dimentions.x) / sheet->spr->width)) * dimentions.x;
	int offx = (int)((index * dimentions.x) % sheet->spr->width); // use % to get rid of tiles beyond the widht size
	DrawTile(x, y, { offx / dimentions.x, offy / dimentions.y }, scale);
}

void pge::Tileset::DrawTile(float x, float y, olc::vi2d tile_cords, olc::vf2d scale) {
	pge->DrawPartialDecal({ x,y }, sheet->dcl, tile_cords * dimentions, dimentions);
}

pge::Tileset::~Tileset() {
	delete sheet;
}
