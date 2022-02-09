#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::string str = converter.convert("14.88", 30, 11);
	std::cout << str << std::endl;
}