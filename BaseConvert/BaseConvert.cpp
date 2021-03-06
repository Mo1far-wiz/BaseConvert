#include "BaseConvert.h"

void BaseConvert::toupper(std::string& str)
{
	auto str_iterator_begin = str.begin();
	auto str_iterator_end = str.end();

	for (str_iterator_begin; str_iterator_begin != str_iterator_end; ++str_iterator_begin)
		if (*str_iterator_begin >= 'a' && *str_iterator_begin <= 'z')
			*str_iterator_begin -= 32;
}

int BaseConvert::comma_possition(std::string& str)
{
	auto str_iterator_begin = str.begin();
	auto str_iterator_end = str.end();

	for (int q = 0; str_iterator_begin != str_iterator_end; ++str_iterator_begin, ++q)
		if (*str_iterator_begin == ',' || *str_iterator_begin == '.')
			return q;

	return -1;
}

int BaseConvert::to_number(char ch)
{
	while (ch > 127)
		ch -= 128;

	if (ch >= 48 && ch <= 57)
		return ch - 48;

	return ch - 55;
}

char BaseConvert::to_char(int n)
{
	return static_cast<char>(n + 55);
}

std::string BaseConvert::integer_part_convert(const std::string& int_str, int to)
{
	long long decimal = std::stoll(int_str);
	if (decimal == 0)
		return "0";
	std::string converted_int_str = "";

	for (int q = 0; decimal > 0; ++q) {
		int elem = decimal % to;

		if (elem > 9)
			converted_int_str += to_char(elem);
		else
			converted_int_str += elem != 0 ? std::to_string(elem) : std::to_string(0);

		decimal /= to;
	}

	std::reverse(converted_int_str.begin(), converted_int_str.end());

	return converted_int_str;
}

void BaseConvert::fractional_part_convert(std::string& fract_str, int to)
{
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

std::string BaseConvert::convert(std::string str, int from, int to)
{
	toupper(str);

	if (from > 36 || to > 36 || from < 0 || to < 0)
		throw std::invalid_argument("bases should be between 36 and 0");

	long long decimal_int = 0;
	long double decimal_fract = 0;

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

		if (numbers >= -1)
			decimal_int += val * power;
		else
			decimal_fract += val * power;
	}

	std::string fractal_part;
	if (comma_pos != -1) {
		fractal_part = std::to_string(decimal_fract);
		fractional_part_convert(fractal_part, to);
	}

	std::string decimal_int_str = std::to_string(decimal_int);
	std::string converted_str = integer_part_convert(decimal_int_str, to);

	if (comma_pos != -1) {
		converted_str += "." + fractal_part;
	}

	return converted_str;
}
