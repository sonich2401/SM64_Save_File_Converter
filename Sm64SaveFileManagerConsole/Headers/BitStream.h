#include <vector>
struct sm64Val{
	std::vector<unsigned char> dat;
	virtual void OnCreate() {};
	virtual void swap() {};
};
namespace sm64_t {
	struct DOUBLE : public sm64Val {
		DOUBLE(unsigned char InitList[4]) {
			this->OnCreate();
			for (unsigned int i = 0; i < 4; i++) {
				dat.push_back(InitList[i]);
			}
		}
		void OnCreate() override {
			dat.reserve(4);
		}
		void swap() override {
			dat[0] += dat[3];
			dat[3] = dat[0];
			dat[0] -= dat[3];
			dat[1] += dat[2];
			dat[2] = dat[1];
			dat[1] -= dat[2];
		}
	};

	struct SHORT : public sm64Val {
		SHORT(unsigned char InitList[2]) {
			this->OnCreate();
				for (unsigned int i = 0; i < 2; i++) {
					dat.push_back(InitList[i]);
				}
		}
		void OnCreate() override {
			dat.reserve(2);
		}
		void swap() override {
			dat[0] += dat[1];
			dat[1] = dat[0];
			dat[0] -= dat[1];
		}
	};
	typedef struct Bit8Type : public sm64Val {
		Bit8Type(unsigned char InitList) {
			this->OnCreate();
			for (unsigned int i = 0; i < 1; i++) {
				dat.push_back(InitList);
			}
		}
		void OnCreate() override {
			dat.reserve(1);
		}
		void  swap() override {
			std::cout << "\nERROR: Char's and Int's cannot be Byte Swapped!\n";
		}
	}CHAR, INT8;
}