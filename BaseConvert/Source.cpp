#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::string str = converter.convert("49CI2G8IC", 25, 34);
	std::cout << str << std::endl;
}