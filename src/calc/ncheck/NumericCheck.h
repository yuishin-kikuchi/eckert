////==--------------------------------------------------------------------====//
// NUMERIC CHECK
//====--------------------------------------------------------------------==////

#ifndef _NUMERIC_CHECK_H_
#define _NUMERIC_CHECK_H_

#include <string>
#include <cctype>
#include <map>

class NumericCheck {
	public:
		enum class NumberType : int;
		enum class DataType : int;
		enum class MetricPrefix : int;
		static const std::map<MetricPrefix, std::string> prefixSymbol;
	private:
		static std::size_t checkPrefix(const std::string &token, MetricPrefix &mp);
		static std::size_t checkPrefixImag(const std::string &str, MetricPrefix &mp);
	public:
		static void removeImag(std::string &r_strToken);
		// numeric check
		static NumberType whatNumber(const std::string &token);
		static bool isInfinity(const std::string &token);
		static bool isUnsigned(const std::string &token);
		static bool isInteger(const std::string &token);
		static bool isDecimal(const std::string &token);
		static bool isExponential(const std::string &token);
		static bool isImagInteger(const std::string &token);
		static bool isImagDecimal(const std::string &token);
		static bool isImagExponential(const std::string &token);
		// numeric check with metric prefix
		static NumberType whatNumber(const std::string &token, MetricPrefix &mp);
		static bool isInteger(const std::string &token, MetricPrefix &mp);
		static bool isDecimal(const std::string &token, MetricPrefix &mp);
		static bool isExponential(const std::string &token, MetricPrefix &mp);
		static bool isImagInteger(const std::string &token, MetricPrefix &mp);
		static bool isImagDecimal(const std::string &token, MetricPrefix &mp);
		static bool isImagExponential(const std::string &token, MetricPrefix &mp);
		static void erasePrefix(std::string &str, const NumberType &type, const MetricPrefix &prefix);
		// data string check
		static DataType whatData(const std::string &token);
		static bool isTrue(const std::string &token);
		static bool isFalse(const std::string &token);
		static bool isPreUnsigned(const std::string &token);
		static bool isZeroOctal(const std::string &token);
		static bool isBinary(const std::string &token);
		static bool isOctal(const std::string &token);
		static bool isHexadecimal(const std::string &token);
};

enum class NumericCheck::NumberType : int {
	NOT_NUMBER,
	INTEGER,
	DECIMAL,
	EXPONENTIAL,
	IMAG_INTEGER,
	IMAG_DECIMAL,
	IMAG_EXPONENTIAL,
	T_INFINITY,
};

enum class NumericCheck::DataType : int {
	NOT_DATA,
	TRUE,
	FALSE,
	DECIMAL,
	UNSIGNED,
	BINARY,
	OCTAL,
	ZERO_OCTAL,
	HEXADECIMAL,
};

enum class NumericCheck::MetricPrefix : int {
	YOCTO, //  y: 1.0E-24
	ZEPTO, //  z: 1.0E-21
	ATTO,  //  a: 1.0E-18
	FEMTO, //  f: 1.0E-15
	PICO,  //  p: 1.0E-12
	NANO,  //  n: 1.0E-09
	MICRO, //  u: 1.0E-06
	MILLI, //  m: 1.0E-03
	CENTI, //  c: 1.0E-02
	DECI,  //  d: 1.0E-01
	ONE,   //  1
	DECA,  // da: 1.0E+01
	HECTO, //  h: 1.0E+02
	KILO,  //  k: 1.0E+03
	MEGA,  //  M: 1.0E+06
	GIGA,  //  G: 1.0E+09
	TERA,  //  T: 1.0E+12
	PETA,  //  P: 1.0E+15
	EXA,   //  E: 1.0E+18
	ZETTA, //  Z: 1.0E+21
	YOTTA, //  Y: 1.0E+24
	KIBI,  // Ki: 2^(10 * 1)
	MEBI,  // Mi: 2^(10 * 2)
	GIBI,  // Gi: 2^(10 * 3)
	TEBI,  // Ti: 2^(10 * 4)
	PEBI,  // Pi: 2^(10 * 5)
	EXBI,  // Ei: 2^(10 * 6)
	ZEBI,  // Zi: 2^(10 * 7)
	YOBI,  // Yi: 2^(10 * 8)
};

#endif // _NUMERIC_CHECK_H_
