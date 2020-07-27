#pragma once
#include <iostream>
#include <bitset>
#include "../CrudeSm64SaveRoutie.h"
template<size_t T>
std::string bits(int number, bool mode = 0) {
    std::bitset<T> bit(number);
    if (mode) { //REVERSEBITS
        for (std::size_t i = 0; i < T / 2; ++i) {
            bool t = bit[i];
            bit[i] = bit[T - i - 1];
            bit[T - i - 1] = t;
        }
    }
    return bit.to_string();
}
template<size_t T>
bool getBit(int number, int bitPosition, bool mode = 0) {
    std::bitset<T> bit(number);
    if (mode)
        return bit[T - bitPosition - 1];
    return bit[bitPosition];
}
void displayCourseData(eep saveData,int saveFile) {
    std::cout << "\nCourse Number |       Stars       | Coin Score";
    std::string name[15] = {"Bomb-Omb Battlefield","Whomps Fortress","Jolly Rodger Bay","Cool Cool Mountain","Big Boo's Haunt","Hazy Maze Cave","Lethal Lava Land","Shifting Sand Land","Dire Dire Docks","Snowman's Land","Wet Dry World","Tall Tall Mountain","Tiny Huge Island","Tick Toc Clock","Rainbow Ride"};
    for (unsigned int i1 = 0; i1 < 15; i1++) {
        std::cout << "\n  " << i1 << "." << name[i1] << "\t\t\t\t" <<std::dec<< (int)saveData.SaveFiles[saveFile][0].coinCourses[i1];
        uint8_t starval = (int)saveData.SaveFiles[saveFile][0].CourseDat[i1];
        for (unsigned int i2 = 0; i2 < 7; i2++) {
            std::string sSt = "Not Collected";
            if (getBit<8>(starval, 8-i2-1, 1)) {
                sSt = "Star Collectd";
            }
            std::cout << "\n\t\t" << i2 + 1 << ". " << sSt;
        }
    }
}
