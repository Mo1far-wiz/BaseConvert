#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::string str = converter.convert("49cI2g8IC", 25, 34);
	std::cout << str << std::endl;
}