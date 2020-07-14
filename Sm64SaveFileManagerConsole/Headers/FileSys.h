#include <string>
#include <fstream>
 std::vector<unsigned char> LoadHex(std::string fn){
	std::fstream SavFile(fn,std::ios::in );
	std::string sTmp; //Temproary string
	std::getline(SavFile, sTmp);
//	memcpy(Contents, &sTmp, 512); //Debugging purposes
	SavFile.close();
	std::vector<unsigned char>ret; 
	ret.reserve(512);
	system("cls");
	for (unsigned int i = 0; i < 512; i++) {
		std::cout <<std::hex<<(unsigned char)sTmp[i] ; //dispplays what is being sent to the vector
		ret.push_back((unsigned char)sTmp[i]);
		std::dec;
	}
	system("pause");
	return ret;
	}
static std::string LoadFile(std::string fn){
std::fstream File(fn,std::ios::in);
	std::string Contents;
	File>>Contents;
	File.close();
	return Contents;
	}