#include "SprSheet.h"
#include "../../resource/resource_manager.h"

pge::SprSheet::SprSheet(const std::string& sheet_fp, const olc::vi2d& wh) {
	abort();
	init(sheet_fp, wh);
}

pge::SprSheet::SprSheet(olc::Sprite* __restrict__ sheet, const olc::vi2d& wh) {
	printf("ERR SPRSHEET: %p\n", sheet);
	abort();
	init(new pge::ren(sheet), wh);
}

pge::SprSheet::SprSheet() { abort(); }

pge::SprSheet::SprSheet(const anipk_SprSheet* __restrict__ package)
{
	this->currentState = 0; //To prevent compiler warnings
	this->currentFrame = 0;
	this->pge = rman::get().pge;
	this->init((pge::ren*)rman::get().load(package->reference_textue), package->spr_size);

	this->States.resize(package->anis.size()); //Allocate space
	for (Animation_id i = 0; i < package->anis.size(); i++) {
		AddState(i, package->anis[i].index, package->anis[i].dur_of_frame);
	}
}

pge::SprSheet::SprSheet(RESOURCE_ENUM sheet_id, const olc::vi2d& wh) {
	abort();
	init((pge::ren*)rman::get().load(sheet_id), wh);
}

void pge::SprSheet::init(pge::ren* __restrict__ spr, const olc::vi2d& wh){
	pge = rman::get().pge;
	sprSheet = spr;
	spr_sheet_wh = wh;
}

void pge::SprSheet::init(const std::string& sheet_fp, const olc::vi2d& wh) {
	printf("ERR SPRSHEET: %s\n", sheet_fp.c_str());
	abort();
	init(new pge::ren(sheet_fp), wh);
}

void pge::SprSheet::HotSwap(olc::Sprite* __restrict__ new_spr) {
	sprSheet->spr = new_spr;
	sprSheet->dcl->Update();
}

void pge::SprSheet::AddState(unsigned int StateID, const std::vector<unsigned short int>& frame_ids, const float& frameDir) {
	States[StateID] = frameList{ frameDir, frame_ids };
	SetState(StateID);
}

void pge::SprSheet::SetState(unsigned int StateID) {
	if(StateID > 50){
		abort();
	}
	if(currentState == StateID){
		return;
	}
	currentState = StateID;
	this->timer = this->States[this->currentState].frameDuritation;
	currentFrame %= this->States[this->currentState].Frame_ids.size();
}



void pge::SprSheet::GetNextFrame(const float& fElapsedTime) {
	this->timer -= fElapsedTime;
	if (this->timer <= 0.0f) {
		this->currentFrame++;
		this->timer += this->States[this->currentState].frameDuritation;
		if(this->timer <= 0.0f){
			this->timer = this->States[this->currentState].frameDuritation;
		}

		this->currentFrame %= this->States[this->currentState].Frame_ids.size();
	}
}

//TODO: Why does this exist?
std::array<olc::vf2d, 2> pge::SprSheet::GetFrameCords(){
  int cur_frame = States[currentState].Frame_ids[currentFrame];
  int offy = ((int)((cur_frame * spr_sheet_wh.x) / sprSheet->spr->width)) * spr_sheet_wh.y;
  int offx = (int)((cur_frame * spr_sheet_wh.x) % sprSheet->spr->width); // use % to get rid of tiles beyond the widht size

  return {{{(float)offx, (float)offy}, spr_sheet_wh}};
}

void pge::SprSheet::Draw(const olc::vf2d& pos, const olc::vf2d& scale , const olc::Pixel& tint){
	int cur_frame = States[currentState].Frame_ids[currentFrame];
  
	int offy = ((int)((cur_frame * spr_sheet_wh.x) / sprSheet->spr->width)) * spr_sheet_wh.y;
	int offx = (int)((cur_frame * spr_sheet_wh.x) % sprSheet->spr->width); // use % to get rid of tiles beyond the widht size

	pge->DrawPartialDecal(pos, sprSheet->dcl, {(float)offx, (float)offy}, spr_sheet_wh, scale, tint);
}

pge::SprSheet::~SprSheet(){
	rman::get().unload_texture(this->sprSheet);
	this->States.clear();
}
