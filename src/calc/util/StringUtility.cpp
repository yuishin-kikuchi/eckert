#include "StringUtility.h"
#include <cctype>

////==--------------------------------------------------------------------====//
// STRING UTILITY / SPLIT STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
std::vector<std::string> StringUtility::split(const std::string &str) {
	std::vector<std::string> tokens;
	bool reading_word = false;
	bool reading_str = false;
	for (std::string::size_type pos = 0, start = 0, end = str.size();
		pos < end;
		++pos) {
		const auto &ch = str.at(pos);
		switch (ch) {
			case '\t':
				// fall through
			case '\n':
				// fall through
			case '\v':
				// fall through
			case '\f':
				// fall through
			case '\r':
				// fall through
			case ' ':
				if (reading_word) {
					tokens.push_back(std::string(str, start, pos - start));
					reading_word = false;
				}
				break;
			case '\"':
				// double-quoted string
				if (reading_str) {
					tokens.push_back(std::string(str, start, pos - start + 1));
					reading_str = false;
				}
				else if (!reading_word && !reading_str) {
					start = pos;
					reading_str = true;
				}
				break;
			default:
				// not splitter nor double-quotation
				if (!reading_str && !reading_word) {
					start = pos;
					reading_word = true;
				}
				break;
			}
			if ((reading_str || reading_word) && (end == pos + 1)) {
				tokens.push_back(std::string(str, start, pos - start + 1));
				reading_str = false;
				reading_word = false;
			}
	}
	return tokens;
}

////==--------------------------------------------------------------------====//
// STRING UTILITY / STRING TO UPPER
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////
void StringUtility::stringToUpper(std::string &str) {
	for (auto &&x : str) {
		x = std::toupper(x);
	}
}

////==--------------------------------------------------------------------====//
// STRING UTILITY / STRING TO LOWER
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////
void StringUtility::stringToLower(std::string &str) {
	for (auto &&x : str) {
		x = std::tolower(x);
	}
}

////==--------------------------------------------------------------------====//
// STRING UTILITY / GENERATE UPPER STRING
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////
std::string StringUtility::genUpperString(const std::string &str) {
	std::string temp = str;
	for (auto &&x : temp) {
		x = std::toupper(x);
	}
	return temp;
}

////==--------------------------------------------------------------------====//
// STRING UTILITY / GENERATE LOWER STRING
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////
std::string StringUtility::genLowerString(const std::string &str) {
	std::string temp = str;
	for (auto &&x : temp) {
		x = std::tolower(x);
	}
	return temp;
}
