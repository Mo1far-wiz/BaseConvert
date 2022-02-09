#pragma once
#include <iostream>
#include <string>
#include <math.h>

class BaseConvert
{
private:
	void toupper(std::string* str) {
		auto str_iterator_begin = str->begin();
		auto str_iterator_end = str->end();

		for (str_iterator_begin; str_iterator_begin != str_iterator_end; ++str_iterator_begin) {
			int val = *str_iterator_begin;
			if (val >= 'a' && val <= 'z')
				val -= 32;
			*str_iterator_begin = static_cast<char>(val);
		}
	}
	int comma_possition(std::string* str) {
		auto str_iterator_begin = str->begin();
		auto str_iterator_end = str->end();

		for (int q = 0; str_iterator_begin != str_iterator_end; ++str_iterator_begin, ++q) {
			int val = *str_iterator_begin;
			if (val == ',' || val == '.')
				return q;
		}

		return -1;
	}
	int to_number(char ch) {
		while (ch > 127)
			ch -= 128;
		if (ch >= 48 && ch <= 57)
			return ch - 48;

		return ch - 55;
	}
public :
	BaseConvert() {}
	~BaseConvert() {}

	std::string convert(std::string str, int from, int to) {
		toupper(&str);

		if (from > 36 || to > 36 || from < 0 || to < 0)
			throw std::invalid_argument("bases should be between 36 and 0");

		long double decimal = 0;
		int comma_pos = comma_possition(&str);
		int numbers; // quantity of numbers in string (without comma)

		if (comma_pos != -1)
			numbers = comma_pos - 1;
		else
			numbers = str.length() - 1;

		auto str_iterator_begin = str.begin();
		auto str_iterator_end = str.end();

		for (; str_iterator_begin != str_iterator_end; ++str_iterator_begin) {
			int val = to_number(*str_iterator_begin);
			if (val == comma_pos) {
				numbers = -1;
				continue;
			}

			long double power = pow(from, numbers--);
			decimal += val * power;
		}

		std::string decimal_str = std::to_string(decimal);

		if (comma_pos != -1) {
			std::string fractal_part = decimal_str.substr(decimal_str.find("[,\.]"));
		}
	}
};

