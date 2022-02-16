#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::cout << converter.convert("0.12122", 3, 9) << std::endl;
	std::string str = converter.convert("49cI2g8IC", 25, 34);

}