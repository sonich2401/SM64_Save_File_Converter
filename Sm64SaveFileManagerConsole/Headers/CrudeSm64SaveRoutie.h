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
struct MenuSave {
	uint32_t CoinScoreAge[4];
	uint16_t soundMode;
	uint8_t fillerPadding[8];
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
	uint8_t Flags[3];
	
	////struct flags {
	////	bool nullGarbagePadding[11];
	////	bool TTC_StarDoor;
	////	bool capOnSnowMan;
	////	bool capOnBird;
	////	bool capOnGround;
	////	bool BITFS_StarDoor;
	////	bool JRB_DoorUnlock;
	////	bool CCM_DoorUnlock;
	////	bool WF_DoorUnlock;
	////	bool PSS_DoorUnlock;
	////	bool moatDrained;
	////	bool DDD_WarpMove;
	////	bool UpstairsUnlocked;
	////	bool BasementUnlocked;
	////	bool VanishCapUnlocked;
	////	bool MetalCapUnlocked;
	////	bool WingCapUnlocked;
	////	bool FileExists;
	////};
	
	////starCourses CourseDat[25];
	
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
		counter += 1;
		return char_to_int8(getCar(Input));
	}
	uint16_t l16(std::deque<unsigned char>* Input) {
		counter += 2;
		return char_to_int16(getCar(Input), getCar(Input));
	}
	uint32_t l32(std::deque<unsigned char>* Input) {
		counter += 4;
		return char_to_long(getCar(Input), getCar(Input), getCar(Input), getCar(Input));
	}
	eep(std::deque<unsigned char> Input) {  
		if (1) { this->MenuSaves; }
		for (unsigned int CURRENT_SAVE = 0; CURRENT_SAVE < MAX_SAVES; CURRENT_SAVE++) { //Save Files
			for (unsigned int BACKUP_TYPE = 0; BACKUP_TYPE < 2; BACKUP_TYPE++) {
				SELECTED_SAVE_FILE.capLevel = this->l8(&Input);
				SELECTED_SAVE_FILE.capArea = this->l8(&Input);
				SELECTED_SAVE_FILE.capPos[1] = this->l16(&Input);
				SELECTED_SAVE_FILE.capPos[2] = this->l16(&Input);
				SELECTED_SAVE_FILE.capPos[3] = this->l16(&Input);
				SELECTED_SAVE_FILE.CastleSecrets = this->l8(&Input);
				SELECTED_SAVE_FILE.Flags[0] = this->l8(&Input);
				SELECTED_SAVE_FILE.Flags[1] = this->l8(&Input);
				SELECTED_SAVE_FILE.Flags[2] = this->l8(&Input);
				for (unsigned int i3 = 0; i3 < 25; i3++) { //COURCE DATA
					SELECTED_SAVE_FILE.CourseDat[i3] = this->l8(&Input);
				}
				for (unsigned int i3 = 0; i3 < 15; i3++) { //COURCE COIN SCORES
					SELECTED_SAVE_FILE.coinCourses[i3] = this->l8(&Input);
				}
				if (1) {}
				SELECTED_SAVE_FILE.magic = this->l16(&Input);
				SELECTED_SAVE_FILE.checkSum = this->l16(&Input);
			}
		}
		int cnthere = counter;
		for (unsigned int i1 = 0; i1 < 2; i1++) { //Menu
			for (unsigned int i2 = 0; i2 < 4; i2++) {
				this->MenuSaves[i1].CoinScoreAge[i2] = l32(&Input);
			}
			this->MenuSaves[i1].soundMode = l16(&Input);
			this->MenuSaves[i1].magic = this->l16(&Input);
			this->MenuSaves[i1].checkSum = this->l16(&Input);
		}
		std::cout << "\n" << cnthere - counter;
		system("pause");
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

	void EepRomExport(std::string fn,bool edian) {
		std::cout << "\nHello: " << edian;
		system("pause");
		IntExporter exporter(fn, edian);
		if (1) { std::fstream File(fn, std::ios::out); File << ""; File.close(); }

		for (unsigned int CURRENT_SAVE = 0; CURRENT_SAVE < MAX_SAVES; CURRENT_SAVE++) { //Save Files
			for (unsigned int BACKUP_TYPE = 0; BACKUP_TYPE < 2; BACKUP_TYPE++) {
				exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.capLevel) ;
				exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.capArea) ;
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.capPos[1]) ;
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.capPos[2]) ;
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.capPos[3]) ;
				exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.CastleSecrets) ;
				exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[0]) ;
				exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[1]);
				exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.Flags[2]) ;
				for (unsigned int i3 = 0; i3 < 25; i3++) { //COURCE DATA
					exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.CourseDat[i3]);
				}
				for (unsigned int i3 = 0; i3 < 15; i3++) { //COURCE COIN SCORES
					exporter.ExportInt<uint8_t>(SELECTED_SAVE_FILE.coinCourses[i3]);
				}
				if (1) {}
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.magic);
				exporter.ExportInt<uint16_t>(SELECTED_SAVE_FILE.checkSum);
			}
		}
		for (unsigned int i1 = 0; i1 < 2; i1++) { //Menu
			for (unsigned int i2 = 0; i2 < 4; i2++) {
				exporter.ExportInt<uint32_t>(this->MenuSaves[i1].CoinScoreAge[i2]);
			}
			exporter.ExportInt<uint16_t>(this->MenuSaves[i1].soundMode) ;
			exporter.ExportInt<uint16_t>(this->MenuSaves[i1].magic);
			exporter.ExportInt<uint16_t>(this->MenuSaves[i1].checkSum);
			doNothing();

		}
		system("pause");
	}
};