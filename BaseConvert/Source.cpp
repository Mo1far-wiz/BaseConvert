#include <iostream>
#include "BaseConvert.h"

int main() {
	BaseConvert converter;

	std::string str = converter.convert("122.33", 10, 16);
	std::cout << str << std::endl;
}