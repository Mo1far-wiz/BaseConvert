#pragma once
#include <iostream>
#include <string>
#include <math.h>

class BaseConvert
{
private:
	//function takes reference of string and change lovercase to upper
	void toupper(std::string& str) {
		auto str_iterator_begin = str.begin();
		auto str_iterator_end = str.end();

		for (str_iterator_begin; str_iterator_begin != str_iterator_end; ++str_iterator_begin) {
			int val = *str_iterator_begin;
			if (val >= 'a' && val <= 'z')
				val -= 32;
			*str_iterator_begin = static_cast<char>(val);
		}
	}
	//finds number of commas position, if no returns -1
	int comma_possition(std::string& str) {
		auto str_iterator_begin = str.begin();
		auto str_iterator_end = str.end();

		for (int q = 0; str_iterator_begin != str_iterator_end; ++str_iterator_begin, ++q) {
			int val = *str_iterator_begin;
			if (val == ',' || val == '.')
				return q;
		}

		return -1;
	}
	//if we have letters (like X U I), to make them numbers in char
	int to_number(char ch) {
		while (ch > 127)
			ch -= 128;
		
		return ch - 55;
	}
	//oposite of to_number
	char to_char(int n) {
		return static_cast<char>(n + 55);
	}
	//convert fractional part by formula and rewrite it in string
	void fractional_part_convert(std::string& fract_str, int to) {
		long double num = std::stold(fract_str);
		fract_str = "";

		while (num > 0 && fract_str.length() < 50)
		{
			num *= to;

			if ((int)num > 9)
				fract_str += to_char((int)num);
			else
				fract_str += std::to_string((int)num);

			num -= (int)num;
		}
	}
public :
	BaseConvert() {}
	~BaseConvert() {}

	std::string convert(std::string str, int from, int to) {
		toupper(str);

		if (from > 36 || to > 36 || from < 0 || to < 0)
			throw std::invalid_argument("bases should be between 36 and 0");

		long double decimal = 0;
		int comma_pos = comma_possition(str);
		int numbers; // quantity of numbers in string (without comma)

		if (comma_pos != -1)
			numbers = comma_pos - 1;
		else
			numbers = str.length() - 1;

		auto str_iterator_begin = str.begin();
		auto str_iterator_end = str.end();

		for (; str_iterator_begin != str_iterator_end; ++str_iterator_begin) {
			int val = to_number(*str_iterator_begin);
			if (*str_iterator_begin == '.' || *str_iterator_begin == ',') {
				numbers = -1;
				continue;
			}

			long double power = pow(from, numbers--);
			decimal += val * power;
		}

		std::string decimal_str = std::to_string(decimal);
		std::string fractal_part;
		if (comma_pos != -1) {
			fractal_part = decimal_str.substr(decimal_str.find("."));
			fractional_part_convert(fractal_part, to);
		}

		std::string converted_str = "";

		for (int q = 0; (int)decimal > 0; ++q) {
			int elem = (int)decimal % to;

			if (elem > 9)
				converted_str += to_char(elem);
			else
				converted_str += elem != 0 ? std::to_string(elem) : std::to_string(0);

			decimal /= to;
		}

		std::reverse(converted_str.begin(), converted_str.end());


		if (comma_pos != -1) {
			converted_str += "." + fractal_part;
		}

		return converted_str;
	}
};

