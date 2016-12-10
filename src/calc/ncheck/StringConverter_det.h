#ifndef _STRING_CONVERTER_DET_H_
#define _STRING_CONVERTER_DET_H_

#include "StringConverter.h"
#include <sstream>

template <typename T>
T StringConverter::convert(const std::string &str)
try {
	T val = 0;
	std::istringstream istream(str);
	istream.exceptions(std::ios::failbit | std::ios::badbit);
	if (!str.empty()) {
		istream >> val;
	}
	return val;
}
catch (...) {
	throw StringConverter::Failure();
}

template <typename T>
T StringConverter::convert(const char *str)
try {
	T val = 0;
	std::istringstream istream(str);
	istream.exceptions(std::ios::failbit | std::ios::badbit);
	if (nullptr != str) {
		istream >> val;
	}
	return val;
}
catch (...) {
	throw StringConverter::Failure();
}

template <typename T>
T StringConverter::convertBinaryString(const std::string &str) {
	const std::size_t max_digits = sizeof(T) * 8;
	const std::size_t len = str.length();
	T multi = 1;
	T val = 0;
	if (len < 3) {
		throw StringConverter::Failure();
	}
	else if (str.at(0) != '0') {
		throw StringConverter::Failure();
	}
	else if ((str.at(1) != 'B') && (str.at(1) != 'b')) {
		throw StringConverter::Failure();
	}
	if (len - 2 >= max_digits) {
		throw StringConverter::Failure();
	}
	for (std::size_t pos = len - 1; (len - pos < max_digits + 1) && (pos > 1); --pos) {
		unsigned char ch = (unsigned char)str.at(pos);
		switch (ch) {
		case '0':
			break;
		case '1':
			val += multi;
			break;
		default:
			throw StringConverter::Failure();
		}
		multi <<= 1;
	}
	return val;
}

template <typename T>
T StringConverter::convertOctalString(const std::string &str) {
	const std::size_t max_digits = sizeof(T) * 8 / 3 + (((sizeof(T) * 8) % 3) ? 1 : 0);
	const std::size_t len = str.length();
	T multi = 1;
	T val = 0;
	if (len < 3) {
		return 0;
	}
	else if (str.at(0) != '0') {
		throw StringConverter::Failure();
	}
	else if ((str.at(1) != 'O') && (str.at(1) != 'o')) {
		throw StringConverter::Failure();
	}
	if (len - 2 >= max_digits) {
		throw StringConverter::Failure();
	}
	for (std::size_t pos = len - 1; (len - pos < max_digits + 1) && (pos > 1); --pos) {
		unsigned char ch = (unsigned char)str.at(pos);
		unsigned digit = 0;
		if (('0' <= ch) && (ch <= '8')) {
			digit = ch - '0';
		}
		else {
			throw StringConverter::Failure();
		}
		val += multi * digit;
		multi <<= 3;
	}
	return val;
}

template <typename T>
T StringConverter::convertZeroOctalString(const std::string &str) {
	const std::size_t max_digits = sizeof(T) * 8 / 3 + (((sizeof(T) * 8) % 3) ? 1 : 0);
	const std::size_t len = str.length();
	T multi = 1;
	T val = 0;
	if (len < 2) {
		throw StringConverter::Failure();
	}
	else if (str.at(0) != '0') {
		throw StringConverter::Failure();
	}
	if (len - 1 >= max_digits) {
		throw StringConverter::Failure();
	}
	for (std::size_t pos = len - 1; (len - pos < max_digits + 1) && (pos > 0); --pos) {
		unsigned char ch = (unsigned char)str.at(pos);
		unsigned digit = 0;
		if (('0' <= ch) && (ch <= '8')) {
			digit = ch - '0';
		}
		else {
			throw StringConverter::Failure();
		}
		val += multi * digit;
		multi <<= 3;
	}
	return val;
}

template <typename T>
T StringConverter::convertHexadecimalString(const std::string &str) {
	const std::size_t max_digits = sizeof(T) * 2;
	const std::size_t len = str.length();
	T multi = 1;
	T val = 0;
	if (len < 3) {
		throw StringConverter::Failure();
	}
	else if (str.at(0) != '0') {
		throw StringConverter::Failure();
	}
	else if ((str.at(1) != 'X') && (str.at(1) != 'x')) {
		throw StringConverter::Failure();
	}
	if (len - 2 >= max_digits) {
		throw StringConverter::Failure();
	}
	for (std::size_t pos = len - 1; (len - pos < max_digits + 1) && (pos > 1); --pos) {
		unsigned char ch = (unsigned char)str.at(pos);
		unsigned digit = 0;
		if (std::isdigit((int)ch)) {
			digit = ch - '0';
		}
		else if (('A' <= ch) && (ch <= 'F')) {
			digit = ch - 'A' + 10;
		}
		else if (('a' <= ch) && (ch <= 'f')) {
			digit = ch - 'a' + 10;
		}
		else {
			throw StringConverter::Failure();
		}
		val += multi * digit;
		multi <<= 4;
	}
	return val;
}

template <typename T>
T StringConverter::convertDecimalString(const std::string &str)
try {
	std::istringstream istream(str);
	istream.exceptions(std::ios::failbit | std::ios::badbit);
	T val = 0;
	if (!str.empty()) {
		istream >> val;
	}
	return val;
}
catch (...) {
	throw StringConverter::Failure();
}

template <typename T>
T StringConverter::convertUnsignedDecimalString(const std::string &str)
try {
	const std::size_t len = str.length();
	T val = 0;
	std::string dstr = str;
	if (len < 2) {
		return 0;
	}
	switch (str.at(0)) {
		case 'U':
			// fall through
		case 'u':
			dstr.erase(0, 1);
			break;
		default:
			return 0;
	}
	std::istringstream istream(dstr);
	istream.exceptions(std::ios::failbit | std::ios::badbit);
	istream >> val;
	return val;
}
catch (...) {
	throw StringConverter::Failure();
}

#endif // _STRING_CONVERTER_DET_H_
