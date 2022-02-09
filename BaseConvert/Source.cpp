#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::string str = converter.convert("101", 2, 10);
	std::cout << str << std::endl;
}