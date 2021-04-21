#define OLC_PGE_APPLICATION
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <bitset>
#include "Headers/olcPixelGameEngine.h"
#include "Headers/BitStream.h"
#include "Headers/FileSys.h"
#include "Headers/Sprite.h"
#include "Headers/TextHelp.h"
#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__)
#include "Headers/Linux.h"
#else 
#include "Headers/WindowsFileSys.h"
#endif

#include "Headers/SM64/Char_to_Type.h"
#include "Headers/CrudeSm64SaveRoutie.h"
#include "Headers/SM64/bitsruff.h"
#define CSPATH "./pic/StarFrames/Star_"
#define UCSPATH "./pic/UnStarFrames/Star_"
#define CINPATH "./pic/Coin/C_"
#define SCREEN_SCALAR 1
//DLEETE THIS
//int size = 500 / (15 / 2);
//olc::Pixel colors[2] = { olc::RED,olc::GREEN };
//std::string boolNames[2] = { "False","True" };
//bool tmpbool;
//


eep CurrentSaveFile;
unsigned char currentFile;
bool SaveDataType;

std::vector<unsigned char> SaveDat;
std::deque<unsigned char> VecToDe;
std::vector<unsigned char> EmptySave = LoadHex("./Empty.eep");

Object* Star;
Object* UnStar;
Object* Coin;
Object* starBool[2];
std::bitset<8> CurrentFileStarDat[15];

bool update = 1;
uint8_t gamestate = 1;

float Scroll = 0;
float ScrollVel = 0;

static const std::string PntPth = "./pic/Paintings/";
static const std::string BaseStarCountText = "Castle Stars = ";
std::string TotalStarCount[4];
std::string CastleStarCount= BaseStarCountText;
uint8_t TotalStars=0;

bool exportSt = 0;
bool exportType;
std::string ExportFN="";

static const std::string FlagNames[20] = { "Valid Game","Wing Cap Switch","Metal Cap Switch","Vanish Cap Switch","Castle Moat Drained","8 Star Door Unlocked (Bowser 1)","30 Star Door Opened (Bowser 2)","50 Star Door Opened","Bowser 1 Key Obtained","Bowser 2 Key Obtained","Basement Door Opened" ,"Upstairs Door Opened" ,"Dire Dire Docks Portal Moved" ,"Whomps Fortress Door Opened" ,"Jolly Rodger Bay Door Opened" ,"Cool Cool Mountain Door Opened" ,"Princess's Secret Slide Door Opened" ,"Cap Stolen By Snowman" ,"Cap Stolen By Bird" ,"Cap Stolen By Monkey"};
static const std::string SecretStarNames[15] = {"Tower of the Wing Cap Red Coin Star","Cavern of the Metal Cap Red Coin Star","Vanish Cap Red Coins Star","Basement Toad Star","Upstairs Toad Star" ,"Tick Tock Clock Toad Star" ,"MIPS 16 Star" ,"MIPS 50 Star" ,"Secret Aquarium" ,"Princess's Secret Slide Star in Box" ,"Princess's Secret Slide Star 20 sec" ,"Bowser 1 Red Coin Star" ,"Bowser 2 Red Coin Star" ,"Bowser 3 Red Coin Star" ,"Mairo Wings Over the Rainbow"};

uint8_t CastleSecretStarsCounter(int8_t x=-1,bool y=0,olc::PixelGameEngine *pge=nullptr) {
	int counter = 0;
	std::bitset<5> Toad_Mips(CurrentSaveFile.SaveFiles[currentFile][0].CastleSecrets);//5 bits
	std::bitset<5> PSS(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[18]);// 2bits
	std::bitset<5> Aqua(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[23]); //1 bit
	std::bitset<5> Bowser1(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[15]);//1 bit
	std::bitset<5> WingCap(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[20]);//1 bit
	std::bitset<5> MetalCap(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[19]);//1 bit
	std::bitset<5> VanishCap(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[21]);//1 bit
	std::bitset<5> Bowser2(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[16]);//1 bit
	std::bitset<5> RR_WingCap_RedCoins(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[22]);//1 bit
	std::bitset<5> Bowser3(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[17]);//1 bit
	std::bitset<5>* bitpoint[15 - 4 - 1] = { &WingCap,&MetalCap,&VanishCap, &Toad_Mips,&Aqua,&PSS,&Bowser1,&Bowser2,&Bowser3,&RR_WingCap_RedCoins };
	if (x != -1) {
		if (x == 0)
			WingCap[0] = !WingCap[0];
		if (x == 1)
			MetalCap[0] = !MetalCap[0];
		if (x == 2)
			VanishCap[0] = !VanishCap[0];
		if (x >= 3 && x < 8) {
			if (x == 3)
				Toad_Mips[0] = !Toad_Mips[0];
			if (x == 4)
				Toad_Mips[2] = !Toad_Mips[2];
			if (x == 5)
				Toad_Mips[3] = !Toad_Mips[3];
			if (x == 6)
				Toad_Mips[1] = !Toad_Mips[1];
			if (x == 7)
				Toad_Mips[4] = !Toad_Mips[4];
		}
		if (x == 8)
			Aqua[0] = !Aqua[0];
		if (x == 9)
			PSS[0] = !PSS[0];
		if (x == 10)
			PSS[1] = !PSS[1];
		if (x == 11)
			Bowser1[0] = !Bowser1[0];
		if (x == 12)
			Bowser2[0] = !Bowser2[0];
		if (x == 13)
			Bowser3[0] = !Bowser3[0];
		if (x == 14)
			RR_WingCap_RedCoins[0] = !RR_WingCap_RedCoins[0];
#define tmpm CurrentSaveFile.SaveFiles[currentFile][0]
		tmpm.CastleSecrets = (uint8_t)Toad_Mips.to_ulong();
		tmpm.CourseDat[18] = (uint8_t)PSS.to_ulong();
		tmpm.CourseDat[20] = (uint8_t)WingCap.to_ulong();
		tmpm.CourseDat[21] = (uint8_t)VanishCap.to_ulong();
		tmpm.CourseDat[19] = (uint8_t)MetalCap.to_ulong();
		tmpm.CourseDat[23] = (uint8_t)Aqua.to_ulong();
		tmpm.CourseDat[22] = (uint8_t)RR_WingCap_RedCoins.to_ulong();
		tmpm.CourseDat[15] = (uint8_t)Bowser1.to_ulong();
		tmpm.CourseDat[16] = (uint8_t)Bowser2.to_ulong();
		tmpm.CourseDat[17] = (uint8_t)Bowser3.to_ulong();
	}
	for (unsigned int i = 0; i < 10; i++)
		counter += bitpoint[i]->count();
	if (y) {
		pge->Clear(olc::GREY);
		bool tmpb[15] = {WingCap[0],MetalCap[0],VanishCap[0], Toad_Mips[0],Toad_Mips[2],Toad_Mips[3],Toad_Mips[1],Toad_Mips[4],Aqua[0],PSS[0],PSS[1],Bowser1[0],Bowser2[0],Bowser3[0]};
		olc::Pixel colors[2] = { olc::RED,olc::GREEN };
		std::string boolNames[2] = { "False","True" };
		for (int i = 0; i < 15; i++) {
			pge->FillRect({ 20,i * 34 }, { (int)SecretStarNames[(int)i].size() * 16,16 }, olc::WHITE);
			pge->DrawRect({ 18,(i * 34) - 2 }, { (int)(SecretStarNames[(int)i].size() * 16) + 3,19 }, olc::BLACK);
			pge->DrawString({ 20,i * 34 }, SecretStarNames[(int)i], olc::BLACK, 2);
			pge->DrawString({ 750 - 80,(i * 34) }, boolNames[tmpb[i]], colors[tmpb[i]], 2);
		}
	}
	return counter;
}

unsigned int SelectedToggle2(uint16_t y) {
	unsigned int ret = 0;
	for (unsigned int i = 0; i < 20; i++)
		if (i * 34 < y && (i + 1) * 34 > y)
			return i;
	return 0;
}

void FlagToggle(olc::PixelGameEngine *pge) {
	pge->Clear(olc::GREY);
#define tmpm CurrentSaveFile.SaveFiles[currentFile][0]
	bool tmpb[20] = { tmpm.Flag2.ValidGame ,tmpm.Flag2.WingCapSwitch,tmpm.Flag2.MetalCapSwitch, tmpm.Flag2.VanishCapSwitch,tmpm.Flag1.Castle_Moat_Water,tmpm.Flag1.Bowser1_StarDoor_Unlocked,tmpm.Flag1.Bowser2_StarDoor_Unlocked,tmpm.Flag0.DoorOpen_50star,tmpm.Flag2.Bowser1_Key,tmpm.Flag2.Bowser2_Key,tmpm.Flag2.BasementDoorOpened,tmpm.Flag2.UpstairsDoorOpened,tmpm.Flag1.DDD_Portal_Moved,tmpm.Flag1.WF_Door_Unlocked,tmpm.Flag1.JRB_Door_Unlocked,tmpm.Flag1.CCM_Door_Unlocked,tmpm.Flag1.PSS_Door_Unlocked,tmpm.Flag0.CapStolenBySnowman,tmpm.Flag0.CapStolenByBird,tmpm.Flag0.CapStolenByMonkey };
	bool * tmpb_p[20]= { &tmpm.Flag2.ValidGame ,&tmpm.Flag2.WingCapSwitch,&tmpm.Flag2.MetalCapSwitch, &tmpm.Flag2.VanishCapSwitch,&tmpm.Flag1.Castle_Moat_Water,&tmpm.Flag1.Bowser1_StarDoor_Unlocked,&tmpm.Flag1.Bowser2_StarDoor_Unlocked,&tmpm.Flag0.DoorOpen_50star,&tmpm.Flag2.Bowser1_Key,&tmpm.Flag2.Bowser2_Key,&tmpm.Flag2.BasementDoorOpened,&tmpm.Flag2.UpstairsDoorOpened,&tmpm.Flag1.DDD_Portal_Moved,&tmpm.Flag1.WF_Door_Unlocked,&tmpm.Flag1.JRB_Door_Unlocked,&tmpm.Flag1.CCM_Door_Unlocked,&tmpm.Flag1.PSS_Door_Unlocked,&tmpm.Flag0.CapStolenBySnowman,&tmpm.Flag0.CapStolenByBird,&tmpm.Flag0.CapStolenByMonkey };
	olc::Pixel colors[2] = { olc::RED,olc::GREEN };
	std::string boolNames[2] = { "False","True" };
	for (int i = 0; i < 20; i++) {
		pge->FillRect({ 20,i * 34 -(int)Scroll	}, { (int)FlagNames[(int)i].size() * 16,16 }, olc::WHITE);
		pge->DrawRect({ 18,(i * 34) - 2-(int)Scroll }, { (int)(FlagNames[(int)i].size() * 16) + 3,19 }, olc::BLACK);
		pge->DrawString({ 20,i * 34 -(int)Scroll}, FlagNames[(int)i], olc::BLACK, 2);
		pge->DrawString({ 750 - 80,(i * 34)- (int)Scroll },boolNames[tmpb[i]], colors[tmpb[i]], 2);
	}
	if (pge->GetMouse(0).bPressed) {
		unsigned char abc = SelectedToggle2(pge->GetMouseY()+Scroll);
		*tmpb_p[abc] = !(*tmpb_p[abc]);
	}
}
uint8_t CountStars() {
	uint8_t counter=0;
	std::bitset<7> Courses[15];
	for (unsigned int i = 0; i < 15; i++) {
		Courses[i] = CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[i];
		counter += Courses[i].count();
	}
	return counter + CastleSecretStarsCounter();
}

void updateCastleStarCounter() {
	CastleStarCount = BaseStarCountText + std::to_string(CastleSecretStarsCounter());
}

void UpdateTotalStars() { 
	TotalStarCount[currentFile] = " X "+std::to_string(CountStars());
}

unsigned int SelectedToggle(uint16_t y) {
	return (y > 0) + (y > 34) + (y > 68) + (y > 102) + (y > 136) + (y > 170) + (y > 204) + (y > 238) + (y > 272) + (y > 306) + (y > 340) + (y > 374) + (y > 408) + (y > 442) + (y > 476)-1;
}
struct pair {
	
	olc::Sprite*spr;
	olc::Decal* dcl;
	
	void init(std::string fn) {
		spr = new olc::Sprite(fn);
		dcl = new olc::Decal(spr);
	}
	
	void DrawMe(olc::PixelGameEngine* pge, float x, float y) {
		pge->DrawDecal({ x,y+10 }, dcl, {0.5,0.5});
	}
	
	void DrawMeAsSprite(olc::PixelGameEngine* pge, int x, int y) {
		pge->DrawSprite(x, y, spr);
	}
};
 
pair paintings[15];
 pair arrows[2];
 pair BOMB[2];
 pair TOP;
 pair EMU;
 pair PC_PORT;
 pair TOGGLE;
 pair MOD;
 
 olc::Sprite TOAD("./pic/TOAD.png");
 olc::Sprite MIPS("./pic/MIPS.png");
 olc::Sprite BOW("./pic/Paintings/BOWSER.png");
 olc::Sprite* BOOL_SPR[2] = { new olc::Sprite("./pic/Bool/FALSE.png"),new olc::Sprite("./pic/Bool/TRUE.png") };
 olc::Sprite _TRUE("./pic/Bool/TRUE.png");
 olc::Sprite _FALSE("./pic/Bool/TRUE.png");
 olc::Sprite* SWITCH[3][2] = { {new olc::Sprite("./pic/SWITCH/RED.png"),new olc::Sprite("./pic/SWITCH/RED_.png")} ,{new olc::Sprite("./pic/SWITCH/BLUE.png"),new olc::Sprite("./pic/SWITCH/BLUE_.png")} ,{new olc::Sprite("./pic/SWITCH/GREEN.png"),new olc::Sprite("./pic/SWITCH/GREEN_.png")} };
 std::string FileLetters[4] = { "File A","File B","File C","File D" };

 int GetStar(int x) {
	return (x > 147) + (x > 222) + (x > 297) + (x > 372) + (x > 447) + (x > 522) + (x > 597) + (x > 672) - 1;
}

static const std::string PntPths[15] = {
   "BOB.png",
   "WF.png",
   "JRB.png",
   "CCM.png",
   "BBH.png",
   "HMC.png",
   "LLL.png",
   "SSL.png",
   "DDD.png",
   "CCM.png",
   "WDW.png",
   "TTM.png",
   "THI.png",
   "TTC.png",
   "RR.png"
};

enum Level {
	BOB, WF, JRB, CCM, BBH, HMC, LLL, SSL, DDD, SL, WDW, TTM, THI, TTC, RR
};

static const std::string getName(int lvlNum) {
	switch (lvlNum)
	{
	case 0: return "Bomb-omb Battlefield";
	case 1: return "Whomps Fortress";
	case 2: return "Jolly Rodger Bay";
	case 3: return "Cool Cool Mountian";
	case 4: return "Big Boo's Haunt";
	case 5: return "Hazy Maze Cave";
	case 6: return "Lethal Lava Land";
	case 7: return "Shifting Sand Land";
	case 8: return "Dire Dire Docks";
	case 9: return "Snowman's Land";
	case 10: return "Wet Dry World";
	case 11: return "Tall Tall Mountain";
	case 12: return "Tiny Huge Island";
	case 13: return "Tick Tock Clock";
	case 14: return "Rainbow Ride";
	}
	return "ERROR";
}

void UpdateStarCoutner() {
	for ( int i = 0; i < 15; i++) {
		for ( int i1 = 0; i1 < 8; i1++) {
			CurrentFileStarDat[i][i1]=getBit<8>((int)CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[i], i1, false);
		}
	}
}

void updateImgs(float fE) {
	Star->Sprite.GetNextFrame(fE);
	Coin->Sprite.GetNextFrame(fE);
}

int FileSelect(int x) {
	UpdateStarCoutner();
	updateCastleStarCounter();
	UpdateTotalStars();
	return (x > 177) + (x > 385) + (x > 593) + (x > 801) - 1;
}

void initSave() {
#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__)
	SaveDat = LoadHex("./InFile.sav");
#else
	SaveDat = LoadHex(sb::openfn("Open SM64 Save File"));
#endif
	VecToDe.clear();
	for (unsigned int i = 0; i < 512; i++) {
		VecToDe.push_back(SaveDat[i]);
	}
	CurrentSaveFile.initEep(VecToDe,SaveDat);
	for (unsigned int i = 0; i < 4; i++) {
		currentFile = i;
		updateCastleStarCounter();
		UpdateTotalStars();
	}
}

void initSave(std::string fn) {
	SaveDat = LoadHex(fn);
	VecToDe.clear();
	for (unsigned int i = 0; i < 512; i++) {
		VecToDe.push_back(SaveDat[i]);
	}
	CurrentSaveFile.initEep(VecToDe, SaveDat);
	for (unsigned int i = 0; i < 4; i++) {
		currentFile = i;
		updateCastleStarCounter();
		UpdateTotalStars();
	}
}

bool ExportMenu(uint16_t x,bool edianness) {
	if (x < 500)
		if (edianness)
			return 1; //dont swap
		else
			return 0; //swap
	else
		if (!edianness)
			return 1; //dont swap
		else
			return 0; //swap
	return 1;
	return !((x > 500) && !edianness); //? Doesnt Work?
}









class sm64SaveFileManager : public olc::PixelGameEngine {
	public:
		sm64SaveFileManager()
		{
			sAppName = "Sm64 Save File Manager";
		}

public:

	bool OnUserCreate() override {
		this->Clear(olc::GREY);
		for (unsigned int i = 0; i < 15; i++) {
			paintings[i].init(PntPth + PntPths[i]);
		}
		arrows[0].init("./pic/A_0.png");
		arrows[1].init("./pic/A_1.png");
		olc::Sprite tmps("./pic/BACKGROUND.png");
		//? this->DrawSprite(0, 0, &tmps);
		BOMB[0].init("./pic/Bomb.png");
		BOMB[1].init("./pic/Bomb_cov.png");
		TOP.init("./pic/TOP.png");
		EMU.init("./pic/emu.png");
		PC_PORT.init("./pic/PC.png");
		TOGGLE.init("./pic/TOGGLE.png");
		MOD.init("./pic/MOD.png");
		Star = new Object(this);
		UnStar = new Object(this);
		Coin = new Object(this);
		starBool[0] = UnStar;
		starBool[1] = Star;
		std::string paths[3] = { CSPATH,UCSPATH,CINPATH };
		img tmpimg1;
		img tmpimg2;
		for (unsigned int i = 0; i < 32; i++) {
			tmpimg1.imgs.push_back(new olc::Sprite(paths[0] + std::to_string(i) + ".png"));
		}
		for (unsigned int i = 1; i < 8; i++) {
			tmpimg2.imgs.push_back(new olc::Sprite(paths[2] + std::to_string(i) + ".png"));
		}
		Star->Sprite.AddState("Star", 0.04, tmpimg1);
		UnStar->Sprite.AddState("Star", 0.1, { paths[1] + "0.png" });
		Coin->Sprite.AddState("Coin", 0.1, tmpimg2);
		Star->Sprite.SetState("Star");
		UnStar->Sprite.SetState("Star");
		Coin->Sprite.SetState("Coin");
		
		
		SaveDat = EmptySave;
		for (unsigned int i = 0; i < 512; i++) {
			VecToDe.push_back(SaveDat[i]);
		}
		CurrentSaveFile.initEep(VecToDe, SaveDat);
		return 1;
	}


	bool OnUserUpdate(float fElapsedTime) override {
		updateImgs(fElapsedTime);
		Scroll -= 200 * fElapsedTime * 20 * (this->GetMouseWheel() > 0);
		Scroll += 200 * fElapsedTime * 20 * (this->GetMouseWheel() < 0);
		if (Scroll < -100) {
			Scroll = -100;
		}
		if (Scroll> ((150 * 15) + 29) - 300 - ((gamestate - 1) * 350*2.5)) {
			Scroll = ((150 * 15) + 29)-300-((gamestate-1)*350*2.5);
		}
		int lastFile = currentFile;
		if (GetKey(olc::ENTER).bPressed) {
			SaveDat = EmptySave;
			for (unsigned int i = 0; i < 512; i++) {
				VecToDe.pop_back();
			}
			//VecToDe.clear();
			for (unsigned int i = 0; i < 512; i++) {
				VecToDe.push_back(SaveDat[i]);
			}
			CurrentSaveFile.initEep(VecToDe, SaveDat);
		}
		if (update) {
			update = 0;
			Scroll = -100;
			this->Clear(olc::GREY);
			switch (gamestate) {
			case 0:
				this->Clear(olc::GREY);
				this->SetPixelMode(olc::Pixel::MASK);
				this->DrawString({300+112,20}, "Export As...",olc::BLACK,2);
				this->DrawLine({ 500,40 }, { 500,500 }, olc::BLACK);
				this->DrawLine({ 0,40 }, { 1000,40 }, olc::BLACK);
				this->DrawSprite({ 100,100 }, EMU.spr);
				this->DrawSprite({ 600,150 }, PC_PORT.spr);
				this->DrawString({ 35,400 }, "Emulator/Hardware Save File", olc::BLACK,2);
				this->DrawString({600,400 }, "PC Port Save File", olc::BLACK, 2);
				break;
			case 1:	
				for (unsigned int i = 0; i < 4; i++) {
					currentFile = i;
					CurrentSaveFile.SaveFiles[currentFile][0].Flag2.ValidGame = 1;
					CurrentSaveFile.SaveFiles[currentFile][0].Flags[2]=CurrentSaveFile.SaveFiles[currentFile][0].Flag2.to_int();
					updateCastleStarCounter();
					UpdateTotalStars();
				}
				currentFile = 0;
				break;
			case 2:
				this->SetPixelMode(olc::Pixel::MASK);
				CastleSecretStarsCounter(-1, true, this);
				//std::string deletethis = "the main";
				this->DrawString({ 1000 - (10 * 16),3 }, "Hit 'ESC'", olc::BLACK, 2);
				this->DrawString({ 1000- (10 * 16),3+16 }, "to go", olc::BLACK, 2);
				this->DrawString({ 1000 - (10 * 16),3+32 }, "back to", olc::BLACK, 2);
				this->DrawString({ 1000 - (10 * 16),3 + 48 }, "the main", olc::BLACK, 2);
				this->DrawString({ 1000 - (10 * 16),3 + 64 }, "menu.", olc::BLACK, 2);


				break;
			case 3:
				FlagToggle(this);
				break;
			default:
				break;
			}
		}
		switch (gamestate)
		{
		case 0:
			if (exportSt) {
				exportSt = 0;
				CurrentSaveFile.EepRomExport(ExportFN, exportType, CurrentSaveFile.detectEdianess(SaveDat));
				gamestate = 1;
				update = 1;
				currentFile = 0;
			}
			if (GetMouse(0).bPressed) {
				exportType = ExportMenu(GetMouseX(), CurrentSaveFile.detectEdianess(SaveDat));
				for (unsigned int i = 0; i < 4; i++) {
					CurrentSaveFile.SaveFiles[i][0].Flag2.init(CurrentSaveFile.SaveFiles[i][0].Flags[2]);
					CurrentSaveFile.SaveFiles[i][0].Flag2.ValidGame = 1;
					CurrentSaveFile.SaveFiles[i][0].Flags[2] = CurrentSaveFile.SaveFiles[i][0].Flag2.to_int();
					CurrentSaveFile.SaveFiles[i][0].checkSum = CurrentSaveFile.calcChecksum(i,  CurrentSaveFile.detectEdianess(SaveDat));
				}
#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__)
				std::string tmpStringl = "";
				std::cout << "Enter The Exported Save File Path\n";
				std::getline(std::cin, tmpStringl);
				ExportFN = tmpStringl;
#else
				ExportFN = sb::savefn("Save SM64 Save File");
#endif
				
				this->Clear(olc::GREY);
				this->DrawString({ 0,0 }, "Exporting...", olc::BLACK, 4);
				exportSt = 1;
			}	
			break;
		case 1:
			if (GetKey(olc::F1).bPressed) {
				std::fstream File("./Credits.crdts", std::ios::in | std::ios::binary);
				std::string line;
				while (std::getline(File,line)) {
					std::cout << line << '\n';
				}
				File.close();
			}
			if (GetMouse(0).bPressed) {
				if (GetMouseX() < 100)
					if (GetMouseY() < 100)
						if (GetMouseY() < 35) {
							initSave();
							UpdateStarCoutner();
							updateCastleStarCounter();
							UpdateTotalStars();
						}
						else {
							gamestate = 0;
							update = 1;
						}
				if (GetMouseX() < 500) {
					if (GetMouseY() > ((150 * 15) + 29) - Scroll && GetMouseY() < ((150 * 15) + 29) - Scroll + 64) {
						gamestate = 2;
						update = 1;
					}
					if (GetMouseY() > ((150 * 15) + 48) + 64 + 16 - Scroll && GetMouseY() < ((150 * 15) + 48) + 64 + 16 - Scroll + 64) {
						gamestate = 3;
						update = 1;
					}
				}
			}
			for (unsigned int i = 0; i < 15; i++) {
				float loc = (150 * i) - Scroll;
				if (loc > -120 && loc < this->GetDrawTargetHeight()) {
					std::bitset<8> StarSettmp(CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[i]);
					this->DrawStringDecal({ 12,loc }, getName(i), olc::BLACK);
					paintings[i].DrawMe(this, 12, loc);
					this->DrawDecal({ 875,loc+32 }, BOMB[StarSettmp[7]].dcl, { 2,2 });
					if (GetMouse(0).bPressed) {
						if (GetMouseY() > 100) {
							if (GetMouseY() > loc + 32 && GetMouseY() < loc + 32 + 75) {
								char starst = GetStar(GetMouseX());
								if (starst >= 0 && starst!=7) {
									StarSettmp[starst] = !StarSettmp[starst];
									CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[i] = (uint8_t)StarSettmp.to_ulong();
								}
								if (GetMouseX() > 875) {
									StarSettmp[7] = !bool(StarSettmp[7]);
									CurrentSaveFile.SaveFiles[currentFile][0].CourseDat[i] = (uint8_t)StarSettmp.to_ulong();
								}
							}
							UpdateStarCoutner();
							updateCastleStarCounter();
							UpdateTotalStars();
							if (GetMouseY() > loc + 48 && GetMouseY() < loc + 64 + 16)
								if (GetMouseX() > 789 && GetMouseX() < 822 + 32)
									if (GetMouseX() > 822 && GetMouseX() < 822 + 32)
										CurrentSaveFile.SaveFiles[currentFile][0].coinCourses[i] -= 1;
									else
										CurrentSaveFile.SaveFiles[currentFile][0].coinCourses[i] += 1;
							if (GetMouseY() > ((150 * 15) + 29) - Scroll&&GetMouseY()< ((150 * 15) + 29) - Scroll+64) { //Modify Secret Stars
								if (GetMouseX() > 385 && GetMouseX() < 385 + 128) {
									gamestate = 2;
									update = 1;
								}
							}
						}
						else {
							if (GetMouseX() > 177) {
								currentFile = FileSelect(GetMouseX());
								UpdateStarCoutner();
								updateCastleStarCounter();
								UpdateTotalStars();
							}
						}
					}
					for (unsigned int i1 = 0; i1 < 7; i1++) {
						int tmpx = 147 + (i1 * 75), tmpy = loc + 32;
						starBool[(unsigned int)CurrentFileStarDat[i][i1]]->Sprite.DrawToScreen(this, tmpx, tmpy,0.2,0.2);
					}
					Coin->Sprite.DrawToScreen(this, 672, loc + 32, 0.2, 0.2);
					this->DrawStringDecal({ 672 + 75,loc + 32 }, std::to_string(CurrentSaveFile.SaveFiles[currentFile][0].coinCourses[i]), olc::BLACK, { 2,2 });
					arrows[0].DrawMe(this, 789, loc + 48);
					arrows[1].DrawMe(this, 822, loc + 48);
				}
			}
			Star->Sprite.DrawToScreen(this, 12, ((150 * 15) + 32)-Scroll, 0.2, 0.2);
			this->DrawStringDecal({87,((150 * 15) + 48) - Scroll }, CastleStarCount, olc::BLACK,{ 2,2 });
			this->DrawDecal({ 385,((150 * 15) + 29) - Scroll }, MOD.dcl, {1,1});
			this->DrawStringDecal({ 87,((150 * 15) + 48)+64+16 - Scroll }, "Game Flags", olc::BLACK, {2,2});
			this->DrawDecal({ 385,((150 * 15) + 29)+64+16 - Scroll }, MOD.dcl, { 1,1 });
			this->DrawDecal({ 0,0 }, TOP.dcl);
			lastFile = currentFile;
			for (unsigned int i = 0; i < 4; i++) {
				currentFile = i;
				Star->Sprite.DrawToScreen(this, (1000-823) + (i*208), 16, 0.2, 0.2);
				this->DrawStringDecal({ (1000-823) + float(i * 208)+60,36 }, TotalStarCount[i], olc::BLACK, { 2,2 });
				this->DrawStringDecal({ (1000-823) + float(i * 208),0 }, FileLetters[i], olc::BLACK, { 2,2 });
			}
			currentFile = lastFile;
			if (GetKey(olc::SPACE).bPressed) { 
				gamestate = 2;
				update = 1;
			}
			break;
		case 2:
			for (int i = 0; i < 15; i++) {
				this->DrawDecal({ 750,float(i * 34) }, TOGGLE.dcl, {0.4,0.4});
			}
			if (GetMouse(0).bPressed) {
				CastleSecretStarsCounter(SelectedToggle(GetMouseY()),true,this);
			}
			if (GetKey(olc::ESCAPE).bPressed) {
				gamestate = 1;
				update = 1;
			}
				break;
		case 3:
			for (int i = 0; i < 20; i++) {
				this->DrawDecal({ 750,float((i * 34)-Scroll) }, TOGGLE.dcl, { 0.4,0.4 });
			}
				FlagToggle(this);
			if (GetKey(olc::ESCAPE).bPressed) {
				gamestate = 1;
				update = 1;
			}
			this->DrawStringDecal({ 1000 - (10 * 16),3 }, "Hit 'ESC'", olc::BLACK, {2,2});
			this->DrawStringDecal({ 1000 - (10 * 16),3 + 16 }, "to go", olc::BLACK, { 2,2 });
			this->DrawStringDecal({ 1000 - (10 * 16),3 + 32 }, "back to", olc::BLACK, { 2,2 });
			this->DrawStringDecal({ 1000 - (10 * 16),3 + 48 }, "the main", olc::BLACK, { 2,2 });
			this->DrawStringDecal({ 1000 - (10 * 16),3 + 64 }, "menu.", olc::BLACK, { 2,2 });


			break;
		default:
			std::cout << "WHAT DID YOU DO! YOUR NOT SUPPOSED TO BE LOOKING AT THIS IN A HEX EDITOR/DISASEMBLER";
			std::cout << "\noh...you were...just using my program and it...choked...sorry for assuming that you were a threat to the FBI\n";
			break;
		}
		return 1;
	}
};
int main() {
	sm64SaveFileManager window;
	uint16_t sze[2];
	std::fstream File("./default.config", std::ios::in | std::ios::binary);
	std::string line;
	uint8_t num = -1;
	while (std::getline(File, line)) {
		num++;
		sze[num] = std::stoi(line);
	}
	File.close();
	if (window.Construct(sze[0], sze[1], SCREEN_SCALAR, SCREEN_SCALAR,false,true)) {
		window.Start();
	}
	return 0;
}