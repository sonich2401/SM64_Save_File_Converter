#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
void SendNewMessage(std::string str) {
	system("cls");
	std::cout << str;
}
std::string Bar() {
	return "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
std::string ListItem(std::string Item, int itemNum) {
	return "\n\t" + std::to_string(itemNum) + ". " + Item;
}
int iGetMessage(int range) {
	std::cout << "\n";
	std::string In;
	std::getline(std::cin, In);
	if (std::stoi(In) < range+1) {
		return std::stoi(In);
	}
	return NULL;
}