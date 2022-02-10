#pragma once
#include <iostream>
#include <string>
#include <math.h>

class BaseConvert
{
private:
	//function takes reference of string and change lovercase to upper
	void toupper(std::string& str);
	//finds number of commas position, if no returns -1
	int comma_possition(std::string& str);
	//if we have letters (like X U I), to make them numbers in char
	int to_number(char ch);
	//oposite of to_number
	char to_char(int n);
	//convert integer part by formula and rewrite it in string
	std::string integer_part_convert(const std::string& int_str, int to);
	//convert fractional part by formula and rewrite it in string
	void fractional_part_convert(std::string& fract_str, int to);

public :
	BaseConvert() {}
	~BaseConvert() {}

	std::string convert(std::string str, int from, int to);
};