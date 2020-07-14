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
#include "Headers/WindowsFileSys.h"
#include "Headers/SM64/Char_to_Type.h"
#include "Headers/CrudeSm64SaveRoutie.h"
#include "Headers/SM64/bitsruff.h"
std::string Input;
std::map<std::string,sm64Val*> SaveData;
bool SaveDataType;
std::vector<unsigned char> SaveDat;
std::deque<unsigned char> VecToDe;
eep* testSaveLoad=nullptr;
int MainMenu() {
	SendNewMessage(
		"Choose an Option:"
		+ Bar()
			+ ListItem("Load Save File", 1)
			+ ListItem("Export Save", 2)
			+ ListItem("Convert Save", 3)
			+ ListItem("Veiw Raw Data",4)
	);
	return iGetMessage(5);
}
bool EdiannessMenu() {
	SendNewMessage(
		"What Type of Save File Are You Trying to Load/Export?" + Bar()
			+ ListItem("Hardware/Emulator Save File", 1)
			+ ListItem("SM64 PC Port Save File",2)
	);
	int msRet = iGetMessage(2);
	if (msRet == 1) {
		return true;
	}
	else {
		return false;
	}
	//return 1;
}
void Organize() {
	SaveData["Mario"] = new sm64_t::CHAR((unsigned char)'a');
}
void LoadSM64File() {
	SaveDat = LoadHex(sb::openfn("Open Save File"));
	SaveDataType = EdiannessMenu();
}
void ExportSM64File() {
	std::string fn = sb::savefn("Choose Save Location and Name");
	SaveDataType = EdiannessMenu();
	if (testSaveLoad != nullptr) {
		testSaveLoad->EepRomExport(fn, SaveDataType);
	}
}
void ConvertEdianness() {
}
int main()
{
	system("title Sm64 Save File Editor");
	while (1) {
		switch (MainMenu()) {
		case 1:
			LoadSM64File();
			break;
		case 2:
			ExportSM64File();
			break;
		case 3:
			ConvertEdianness();
			break;
		case 4:
			system("cls");
			for (unsigned int i = 0; i < 512; i++) {
				std::cout << " " + std::to_string(SaveDat[i]);
			}
			system("pause");
			break;
		case 5:
			for (unsigned int banana = 0; banana < 512; banana++) {
				VecToDe.push_back(SaveDat[banana]);
			}
			testSaveLoad = new eep(VecToDe);
			system("cls");
			displayCourseData(*testSaveLoad,0);
			system("pause");
			break;
		default:
			SendNewMessage("\nERROR: Not Valid Gamestate\n");
			return 0;
		}
	}
	return 0;
}