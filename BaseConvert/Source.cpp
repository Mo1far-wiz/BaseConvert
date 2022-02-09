#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::string str = converter.convert("ed", 16, 9);
	std::cout << str << std::endl;
}