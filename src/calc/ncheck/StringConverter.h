////==--------------------------------------------------------------------====//
// STRING CONVERTER
//====--------------------------------------------------------------------==////

#ifndef _STRING_CONVERTER_H_
#define _STRING_CONVERTER_H_

#include <string>

class StringConverter {
	public:
		class Failure : public std::exception { };
	public:
		template <typename T>
		static T convert(const std::string &str);
		template <typename T>
		static T convert(const char *str);
		template <typename T>
		static T convertBinaryString(const std::string &str);
		template <typename T>
		static T convertOctalString(const std::string &str);
		template <typename T>
		static T convertZeroOctalString(const std::string &str);
		template <typename T>
		static T convertHexadecimalString(const std::string &str);
		template <typename T>
		static T convertDecimalString(const std::string &str);
		template <typename T>
		static T convertUnsignedDecimalString(const std::string &str);
};

#include "StringConverter_det.h"
// include the detail header for template functions

#endif // _STRING_CONVERTER_H_
