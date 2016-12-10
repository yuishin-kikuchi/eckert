#ifndef _STRING_UTILITY_H_
#define _STRING_UTILITY_H_

#include <string>
#include <vector>

////==--------------------------------------------------------------------====//
// STRING UTILITY
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////

class StringUtility {
	public:
		static std::vector<std::string> split(const std::string &str);
		static void stringToUpper(std::string &str);
		static void stringToLower(std::string &str);
		static std::string genUpperString(const std::string &str);
		static std::string genLowerString(const std::string &str);
};

#endif // _STRING_UTILITY_H_
