#pragma once
#include <string>
#include <deque>
#include "SM64/Char_to_Type.h"
#define CURRENT_SAVE i1
#define BACKUP_TYPE i2
#define SELECTED_SAVE_FILE this->SaveFiles[CURRENT_SAVE][BACKUP_TYPE]
#define MAX_SAVES 4
void doNothing() {}
int counter=-1;
struct flag;
struct MenuSave {
	uint32_t CoinScoreAge[4];
	uint8_t soundMode;
	uint8_t Language;
	uint8_t fillerPadding[10];
	uint16_t magic;
	uint16_t checkSum;
};
struct starCourses {
	bool CannonOpen;
	bool CoinStarObtained;
	bool star[6];
};
struct Save {
	uint8_t capLevel;
	uint8_t capArea;
	int16_t capPos[3];
	uint8_t CastleSecrets;
	struct h0x08 {
		bool ToadStarBasement;
		bool MIPS_Star16;
		bool ToadStarUpstairs;
		bool ToadStarTickTockClock;
		bool MIPS_Star50;
		void init(uint8_t input) {
			std::bitset<5> tmpbs(input);
			ToadStarBasement	=tmpbs[0] ;
			MIPS_Star16	=tmpbs[1]  ;
			ToadStarUpstairs	=tmpbs[2] ;
			ToadStarTickTockClock=tmpbs[3] ;
			MIPS_Star50 = tmpbs[4];
		}
		unsigned char to_int() {
			std::bitset<5> tmpbs;
			tmpbs[0] = ToadStarBasement;
			tmpbs[1] = MIPS_Star16;
			tmpbs[2] = ToadStarUpstairs;
			tmpbs[3] = ToadStarTickTockClock;
			tmpbs[4] = MIPS_Star50;
			return (uint8_t)tmpbs.to_ulong();
		}
	}CastleSecretsBits;
	uint8_t Flags[3];
	struct h0x09
	{
		bool CapStolenBySnowman;
		bool CapStolenByBird;
		bool CapStolenByMonkey;
		bool DoorOpen_50star;
		void init(uint8_t input) {
			std::bitset<5> tmpbs(input);
			CapStolenBySnowman = tmpbs[0];
			CapStolenByBird = tmpbs[1];
			CapStolenByMonkey = tmpbs[2];
			DoorOpen_50star = tmpbs[4];
		}
		uint8_t to_int() {
			std::bitset<5> tmpbs;
			tmpbs[0] = CapStolenBySnowman;
			tmpbs[1] = CapStolenByBird;
			tmpbs[2] = CapStolenByMonkey;
			tmpbs[4] = DoorOpen_50star;
			return (uint8_t)tmpbs.to_ulong();
		}
	}Flag0;
	struct h0x0A {
		bool DDD_Portal_Moved;
		bool Castle_Moat_Water;
		bool PSS_Door_Unlocked;
		bool WF_Door_Unlocked;
		bool CCM_Door_Unlocked;
		bool JRB_Door_Unlocked;
		bool Bowser1_StarDoor_Unlocked;
		bool Bowser2_StarDoor_Unlocked;
		void init(uint8_t input) {
			std::bitset<8> tmpbs(input);
			DDD_Portal_Moved = tmpbs[0];
			Castle_Moat_Water = tmpbs[1];
			PSS_Door_Unlocked = tmpbs[2];
			WF_Door_Unlocked = tmpbs[3];
			CCM_Door_Unlocked = tmpbs[4];
			JRB_Door_Unlocked = tmpbs[5];
			Bowser1_StarDoor_Unlocked = tmpbs[6];
			Bowser2_StarDoor_Unlocked = tmpbs[7];
		}
		unsigned char to_int() {
			std::bitset<8> tmpbs;
			tmpbs[0] = DDD_Portal_Moved;
			tmpbs[1] = Castle_Moat_Water;
			tmpbs[2] = PSS_Door_Unlocked;
			tmpbs[3] = WF_Door_Unlocked;
			tmpbs[4] = CCM_Door_Unlocked;
			tmpbs[5] = JRB_Door_Unlocked;
			tmpbs[6] = Bowser1_StarDoor_Unlocked;
			tmpbs[7] = Bowser2_StarDoor_Unlocked;
			return (uint8_t)tmpbs.to_ulong();
		}
	}Flag1;
	struct h0x0B {
		bool ValidGame;
		bool WingCapSwitch;
		bool MetalCapSwitch;
		bool VanishCapSwitch;
		bool Bowser1_Key;
		bool Bowser2_Key;
		bool BasementDoorOpened;
		bool UpstairsDoorOpened;
		void init(uint8_t input) {
			std::bitset<8> tmpbs(input);
			ValidGame = tmpbs[0];
			WingCapSwitch = tmpbs[1];
			MetalCapSwitch = tmpbs[2];
			VanishCapSwitch = tmpbs[3];
			Bowser1_Key = tmpbs[4];
			Bowser2_Key = tmpbs[5];
			BasementDoorOpened = tmpbs[6];
			UpstairsDoorOpened = tmpbs[7];
		}
		unsigned char to_int() {
			std::bitset<8> tmpbs;
			tmpbs[0] = ValidGame;
			tmpbs[1] = WingCapSwitch;
			tmpbs[2] = MetalCapSwitch;
			tmpbs[3] = VanishCapSwitch;
			tmpbs[4] = Bowser1_Key;
			tmpbs[5] = Bowser2_Key;
			tmpbs[6] = BasementDoorOpened;
			tmpbs[7] = UpstairsDoorOpened;
			return (uint8_t)tmpbs.to_ulong();
		}
	}Flag2;
	uint8_t CourseDat[25];
	uint8_t coinCourses[15];
	uint16_t magic;
	uint16_t checkSum;
};
struct eep {
	////uint8_t UselessGarbagePadding[8];
	Save SaveFiles[4][2];

	MenuSave MenuSaves[2]; //MenuSave[0]== primary; MenuSave[1] ==Backup;
	unsigned char getCar(std::deque<unsigned char>* Input) {
		unsigned char cTmp = Input->front();
		Input->pop_front();
		return cTmp;
	}
	uint8_t l8(std::deque<unsigned char> *Input) {
		return char_to_int8(getCar(Input));
	}
	uint16_t l16(std::deque<unsigned char>* Input) {
		return char_to_int16(getCar(Input), getCar(Input));
	}
	uint32_t l32(std::deque<unsigned char>* Input) {
		return char_to_long(getCar(Input), getCar(Input), getCar(Input), getCar(Input));
	}
	template <typename T>
	uint8_t uint16_to_uint8_t(T Number, uint8_t pos, bool edianess) {
		unsigned char buff[sizeof(Number)];
		for (int i = 0; i < sizeof(Number); i++)
		{
			buff[i] = (Number & 0xff);
			Number >>= 8;
		}
		uint8_t Index[sizeof(Number)];
		if (edianess) {
			for (unsigned int i1 = 0; i1 < sizeof(Number); i1++)
				Index[i1] = i1;
		}
		else {
			for (unsigned int i1 = 0; i1 < sizeof(Number); i1++)
				Index[i1] = sizeof(Number) - i1 - 1;
		}
		for (unsigned int i1 = 0; i1 < sizeof(Number); i1++)
			return buff[Index[pos]];
	}
	uint16_t calcChecksum(unsigned char SaveFileNum,bool edian) {
		//Add Implementation
		uint16_t tmpi=0;
		uint8_t i1 = SaveFileNum;
		uint8_t i2 = 0;
				tmpi += SELECTED_SAVE_FILE.CastleSecrets;
				tmpi += SELECTED_SAVE_FILE.Flags[0];
				tmpi += SELECTED_SAVE_FILE.Flags[1];
				tmpi += SELECTED_SAVE_FILE.Flags[2] ;
				for (unsigned int i3 = 0; i3 < 25; i3++) { //COURCE DATA
					tmpi += SELECTED_SAVE_FILE.CourseDat[i3];
				}
				for (unsigned int i3 = 0; i3 < 15; i3++) { //COURCE COIN SCORES
					tmpi += SELECTED_SAVE_FILE.coinCourses[i3];
				}
				tmpi += uint16_to_uint8_t<uint16_t>(SELECTED_SAVE_FILE.magic,0,edian);
				tmpi += uint16_to_uint8_t<uint16_t>(SELECTED_SAVE_FILE.magic, 1, edian);
				unsigned char  tmpchk[2];
				tmpchk[0] = uint16_to_uint8_t<uint16_t>(tmpi, 0, edian);
				tmpchk[1] = uint16_to_uint8_t<uint16_t>(tmpi, 1, edian);
				if (edian) {
					tmpi = char_to_int16(tmpchk[0], tmpchk[1]);
				}
				else {
	
					tmpi = char_to_int16(tmpchk[1], tmpchk[0]);
				}
				return tmpi;
	}
	void initEep(std::deque<unsigned char> Input,std::vector<unsigned char>tmpVc) {
		bool ed = this->detectEdianess(tmpVc);
		std::cout <<"EPP: "<< ed<<"\n";
		if (1) { this->MenuSaves; }
		for (unsigned int CURRENT_SAVE = 0; CURRENT_SAVE < MAX_SAVES; CURRENT_SAVE++) { //Save Files
			for (unsigned int BACKUP_TYPE = 0; BACKUP_TYPE < 2; BACKUP_TYPE++) {
				
				SELECTED_SAVE_FILE.capLevel = this->l8(&Input);
				SELECTED_SAVE_FILE.capArea = this->l8(&Input);
				SELECTED_SAVE_FILE.capPos[1] = this->l16(&Input);
				SELECTED_SAVE_FILE.capPos[2] = this->l16(&Input);
				SELECTED_SAVE_FILE.capPos[3] = this->l16(&Input);
				if (ed == 0) {
					SELECTED_SAVE_FILE.Flags[2] = this->l8(&Input);
					SELECTED_SAVE_FILE.Flag2.init(SELECTED_SAVE_FILE.Flags[2]);
					SELECTED_SAVE_FILE.Flags[1] = this->l8(&Input);
					SELECTED_SAVE_FILE.Flag1.init(SELECTED_SAVE_FILE.Flags[1]);
					SELECTED_SAVE_FILE.Flags[0] = this->l8(&Input);
					SELECTED_SAVE_FILE.Flag0.init(SELECTED_SAVE_FILE.Flags[0]);
					SELECTED_SAVE_FILE.CastleSecrets = this->l8(&Input);
					SELECTED_SAVE_FILE.CastleSecretsBits.init(SELECTED_SAVE_FILE.CastleSecrets);
				}
				else {
					SELECTED_SAVE_FILE.CastleSecrets = this->l8(&Input);
					SELECTED_SAVE_FILE.CastleSecretsBits.init(SELECTED_SAVE_FILE.CastleSecrets);
					SELECTED_SAVE_FILE.Flags[0] = this->l8(&Input);
					SELECTED_SAVE_FILE.Flag0.init(SELECTED_SAVE_FILE.Flags[0]);
					SELECTED_SAVE_FILE.Flags[1] = this->l8(&Input);
					SELECTED_SAVE_FILE.Flag1.init(SELECTED_SAVE_FILE.Flags[1]);
					SELECTED_SAVE_FILE.Flags[2] = this->l8(&Input);
					SELECTED_SAVE_FILE.Flag2.init(SELECTED_SAVE_FILE.Flags[2]);
				}
				for (unsigned int i3 = 0; i3 < 25; i3++) { //COURCE DATA
					SELECTED_SAVE_FILE.CourseDat[i3] = this->l8(&Input);
				}
				for (unsigned int i3 = 0; i3 < 15; i3++) { //COURCE COIN SCORES
					SELECTED_SAVE_FILE.coinCourses[i3] = this->l8(&Input);
				}
				SELECTED_SAVE_FILE.magic = this->l16(&Input);
				SELECTED_SAVE_FILE.checkSum = this->l16(&Input);
			}
		}
		for (unsigned int i1 = 0; i1 < 2; i1++) { //Menu
			for (unsigned int i2 = 0; i2 < 4; i2++) {
				this->MenuSaves[i1].CoinScoreAge[i2] = l32(&Input); //16 Bytes
			}
			this->MenuSaves[i1].soundMode = l8(&Input); //1 Bytes
			this->MenuSaves[i1].Language = l8(&Input); //1 byte
			for (unsigned int i2 = 0; i2 < 10; i2++) {
				this->MenuSaves[i1].fillerPadding[i2] = l8(&Input); //10 bytes
			}
			this->MenuSaves[i1].magic = this->l16(&Input); //2 Bytes
			this->MenuSaves[i1].checkSum = this->l16(&Input); //2 Bytes
			//Total 32
		}
	}
	bool detectEdianess(std::vector<unsigned char> Input) {
		std::cout << "CHAR: " << Input[52] << " BOOL: "<< (Input[52] == 'D') << "\n";
		if (Input[52] == 'D') {
			return true;
		}
		else {
			return false;
		}
	}
	eep() {
		doNothing();
	}
	eep(std::deque<unsigned char> Input,std::vector<unsigned char>TmpVc) {
		initEep(Input,TmpVc);
	}
	struct IntExporter {
		std::string fn;
		bool edianess;
		IntExporter(std::string Fn,bool ed) {
			fn = Fn;
			edianess = ed;
		}
		template <typename T>
		void ExportInt(T Number) {
			std::fstream File(fn, std::ios::out | std::ios::app);
			unsigned char buff[sizeof(Number)];
			for (int i = 0; i < sizeof(Number); i++)
			{
				buff[i] = (Number & 0xff);
				Number >>= 8;
			}
			uint8_t Index[sizeof(Number)];
			if (edianess) {
				for (unsigned int i1 = 0; i1 < sizeof(Number); i1++)
					Index[i1] = i1;
			}
			else {
				for (unsigned int i1 = 0; i1 < sizeof(Number); i1++)
					Index[i1] = sizeof(Number) - i1 - 1;
			}
			for (unsigned int i1 = 0; i1 < sizeof(Number); i1++)
				File << buff[Index[i1]];
			File.close();
		}

	};

	void EepRomExport(std::string fn,bool edian,bool specialFlag) {
		IntExporter exporter(fn, edian);
		if (1) { std::fstream File(fn, std::ios::out); File << ""; File.close(); }
		for (unsigned int CURRENT_SAVE = 0; CURRENT_SAVE < MAX_SAVES; CURRENT_SAVE++) { //Save Files
			for (unsigned int BACKUP_TYPE = 0; BACKUP_TYPE < 2; BACKUP_TYPE++) {
				exporter.ExportInt<uint8_t>((uint8_t)0) ;
				exporter.ExportInt<uint8_t>((uint8_t)0) ;
				exporter.ExportInt<uint16_t>((uint16_t)0) ;
				exporter.ExportInt<uint16_t>((uint16_t)0) ;
				exporter.ExportInt<uint16_t>((uint16_t)0) ;
				SELECTED_SAVE_FILE.Flags[0] = SELECTED_SAVE_FILE.Flag0.to_int();
				SELECTED_SAVE_FILE.Flags[1] = SELECTED_SAVE_FILE.Flag1.to_int();
				SELECTED_SAVE_FILE.Flags[2] = SELECTED_SAVE_FILE.Flag2.to_int();
				if (!specialFlag) {
					uint8_t tmp[4] = { SELECTED_SAVE_FILE.CastleSecrets,SELECTED_SAVE_FILE.Flags[0],SELECTED_SAVE_FILE.Flags[1] ,SELECTED_SAVE_FILE.Flags[2] };
					SELECTED_SAVE_FILE.CastleSecrets = tmp[3];
					SELECTED_SAVE_FILE.Flags[0] = tmp[2];
					SELECTED_SAVE_FILE.Flags[1] = tmp[1];
					SELECTED_SAVE_FILE.Flags[2] = tmp[0];
				}
				if (!edian) {
				
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[2]);
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[1]);
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[0]);
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.CastleSecrets);
					
				}
				else {
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.CastleSecrets);
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[0]);
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[1]);
						exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[2]);
				}
				for (unsigned int i3 = 0; i3 < 25; i3++) { //COURCE DATA
					exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.CourseDat[i3]);
				}
				for (unsigned int i3 = 0; i3 < 15; i3++) { //COURCE COIN SCORES
					exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.coinCourses[i3]);
				}
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.magic);
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.checkSum);
			}
		}
		for (unsigned int i1 = 0; i1 < 2; i1++) { //Menu
			for (unsigned int i2 = 0; i2 < 4; i2++) {
				exporter.ExportInt<uint32_t>(this->MenuSaves[i1].CoinScoreAge[i2]);
			}
			exporter.ExportInt<uint8_t>(this->MenuSaves[i1].soundMode) ; 
			exporter.ExportInt<uint8_t>(this->MenuSaves[i1].Language);
			for (unsigned int i2 = 0; i2 < 10; i2++) {
				exporter.ExportInt<uint8_t>(this->MenuSaves[i1].fillerPadding[i2]);
			}
			exporter.ExportInt<uint16_t>(this->MenuSaves[i1].magic);
			exporter.ExportInt<uint16_t>(this->MenuSaves[i1].checkSum);
		}
		//std::cout << "File Exported!\n";
		//system("pause");
	}
};