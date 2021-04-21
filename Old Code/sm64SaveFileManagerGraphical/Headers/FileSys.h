#include <string>
#include <fstream>
#include <vector>
 std::vector<unsigned char> LoadHex(std::string fn){
	std::fstream SavFile(fn,std::ios::in );
	std::string sTmp; //Temproary string
	std::getline(SavFile, sTmp);
	SavFile.close();
	std::vector<unsigned char>ret; 
	for (unsigned int i = 0; i < 512; i++) {
		ret.push_back((unsigned char)sTmp[i]);
	}
	return ret;
	}
static std::string LoadFile(std::string fn){
std::fstream File(fn,std::ios::in);
	std::string Contents;
	File>>Contents;
	File.close();
	return Contents;
	}