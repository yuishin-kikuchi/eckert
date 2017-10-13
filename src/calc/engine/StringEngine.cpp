#include "StringEngine.h"
#include "CalculationConfig.h"
#include "proc/GeneralProcessor.h"
#include <sstream>
#include <iomanip>
#include <limits>
#include <string>
#include <cmath>

namespace engine {

////==--------------------------------------------------------------------====//
// 10TH POWER
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
static floating_t pow10(int exp) {
	if (exp == 0) {
		return 1.0L;
	}
	else if (exp < 0) {
		floating_t val = 1.0L;
		floating_t to_multiply = 0.1L;
		exp = -exp;
		while (exp) {
			if (exp & 1u) {
				val *= to_multiply;
			}
			to_multiply *= to_multiply;
			exp >>= 1;
		}
		return val;
	}
	else {
		floating_t val = 1.0L;
		floating_t to_multiply = 10.0L;
		while (exp) {
			if (exp & 1u) {
				val *= to_multiply;
			}
			to_multiply *= to_multiply;
			exp >>= 1;
		}
		return val;
	}
}

////==--------------------------------------------------------------------====//
// IS FINITE DECIMAL RATIONAL
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
static bool isFiniteDecimalRational(const rational_t &rat) {
	auto den = rat.getDen();
	while (0 == den % 2) {
		den /= 2;
	}
	if (1 == den) {
		return true;
	}
	while (0 == den % 5) {
		den /= 5;
	}
	if (1 == den) {
		return true;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / CONSTRUCTOR
// [ Update ]
// Nov 30, 2016
//====--------------------------------------------------------------------==////
StringEngine::StringEngine() {
	init();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / INITIALIZER
// [ Update ]
// Jul 10, 2016
//====--------------------------------------------------------------------==////
void StringEngine::init() {
	_fcfg.init();
	_tdisp = TypeDisplayMode::LONG;
	_ddisp = DecimalDisplayMode::FORCE_DECIMAL;
	_frdisp = FractionalDisplayMode::PROVISIONAL;
	_nbase = NumberBaseMode::HEXADECIMAL;
	_euler = false;
	_piRad = false;
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / FLOAT TO STRING (STANDARD)
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::floatToStandardString(const floating_t &val, const int &p) {
	if (p < 1) {
		return "PRECISION ERROR";
	}
	std::ostringstream os;
	os << std::uppercase;
	os.precision(p);
	os << val;
	std::string str = os.str();
	if ((std::string::npos == str.find('.')) && (std::string::npos == str.find('E'))) {
		str.append(".");
	}
	return str;
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / FLOAT TO STRING (FIXED)
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::floatToFixedString(const floating_t &val, const int &p) {
	if (p < 0) {
		return "PRECISION ERROR";
	}
	int cprec = std::numeric_limits<floating_t>::digits10;
	std::ostringstream os;
	floating_t num = val;
	if (val < 0.0) {
		os << '-';
		num = -num;
	}
	else if (0.0 == val) {
		os.precision(p);
		os << std::fixed;
		os << val;
		return os.str();
	}
	int decimalExponent = (int)std::floor(std::log10(num));
	if (decimalExponent > cprec - 1) {
		return floatToScientificString(val, p);
	}
	else if ((decimalExponent > -1) && (cprec < p + decimalExponent + 1)) {
		os.precision(cprec - decimalExponent - 1);
		os << std::fixed;
		os << num;
	}
	else {
		os.precision(p);
		os << std::fixed;
		os << num;
	}
	std::string str = os.str();
	if ((std::string::npos == str.find('.')) && (std::string::npos == str.find('E'))) {
		str.append(".");
	}
	return str;
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / FLOAT TO STRING (SCIENTIFIC)
// [ Update ]
// Dec 14, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::floatToScientificString(const floating_t &val, const int &p) {
	if (p < 1) {
		return "PRECISION ERROR";
	}
	//const int cprec = std::numeric_limits<floating_t>::digits10;
	std::ostringstream os;
	os << std::uppercase;
	floating_t num = val;
	if (num == 0.0) {
		os << std::fixed;
		os.precision(p - 1);
		os << val;
		os << "E+00";
		return os.str();
	}
	if (num < 0.0) {
		num = -num;
		os << '-';
	}
	int decimalExponent = (int)std::floor(std::log10(num));
	floating_t mantissa = num;
	mantissa /= pow10(decimalExponent - p + 1);
	mantissa = std::round(mantissa) / pow10(p - 1);
	if (std::abs(10.0L - mantissa) < pow10(-p - 2)) {
		mantissa /= 10.0L;
		decimalExponent++;
	}
	os << std::fixed;
	os.precision(p - 1);
	os << mantissa;
	if (decimalExponent > -1) {
		os << "E+" << std::setfill('0') << std::setw(2) << decimalExponent;
	}
	else {
		os << "E-" << std::setfill('0') << std::setw(2) << -decimalExponent;
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / FLOAT TO STRING (ENGINEERING)
// [ Update ]
// Dec 14, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::floatToEngineeringString(const floating_t &val, const int &p) {
	if (p < 1) {
		return "PRECISION ERROR";
	}
	std::ostringstream os;
	os << std::uppercase;
	floating_t num = val;
	if (num == 0.0) {
		os << std::fixed;
		os.precision(p - 1);
		os << num;
		os << "E+00";
		return os.str();
	}
	if (num < 0.0) {
		num = -num;
		os << '-';
	}
	int decimalExponent = (int)std::floor(std::log10(num));
	floating_t mantissa = num;
	mantissa /= pow10(decimalExponent - p + 1);
	mantissa = std::round(mantissa) / pow10(p - 1);
	if (std::abs(10.0L - mantissa) < pow10(-p - 2)) {
		mantissa /= 10.0L;
		decimalExponent++;
	}
	int eex = 0;
	int rem = 0;
	if (0 != decimalExponent) {
		rem = decimalExponent % 3;
		if (rem < 0) {
			rem += 3;
		}
	}
	eex = decimalExponent - rem;
	mantissa = mantissa * pow10(rem);
	switch (p) {
		case 1: {
			switch (rem) {
				case 2:
					mantissa = ::round(mantissa / 100.0L) * 100.0L;
					break;
				case 1:
					mantissa = ::round(mantissa / 10.0L) * 10.0L;
					break;
				case 0:
					mantissa = ::round(mantissa);
					break;
				default:
					break;
			}
			os << mantissa;
			break;
		}
		case 2: {
			switch (rem) {
				case 2:
					mantissa = ::round(mantissa / 10.0L) * 10.0L;
					break;
				case 1:
					mantissa = ::round(mantissa);
					break;
				case 0:
					mantissa = ::round(mantissa * 10.0L) / 10.0L;
					os << std::fixed << std::setprecision(1);
					break;
				default:
					break;
			}
			os << mantissa;
			break;
		}
		case 3: {
			switch (rem) {
				case 2:
					mantissa = ::round(mantissa);
					os << std::fixed << std::setprecision(0);
					break;
				case 1:
					mantissa = ::round(mantissa * 10.0L) / 10.0L;
					os << std::fixed << std::setprecision(1);
					break;
				case 0:
					mantissa = ::round(mantissa * 100.0L) / 100.0L;
					os << std::fixed << std::setprecision(2);
					break;
				default:
					break;
			}
			os << mantissa;
			break;
		}
		default: {
			switch (rem) {
				case 2:
					os.precision(p - 3);
					break;
				case 1:
					os.precision(p - 2);
					break;
				case 0:
					os.precision(p - 1);
					break;
				default:
					break;
			}
			os << std::fixed;
			os << mantissa;
			break;
		}
	}
	if (eex > -1) {
		os << "E+" << std::setfill('0') << std::setw(2) << eex;
	}
	else {
		os << "E-" << std::setfill('0') << std::setw(2) << -eex;
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / TYPE TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::typeToString(const CalculationConfig &cfg, const SpElement &elm) const {
	switch (getTypeDisplayMode()) {
		case StringEngine::TypeDisplayMode::NO_DISPLAY:
			return std::string();
		case StringEngine::TypeDisplayMode::LONG:
			return typeToLongString(elm);
		case StringEngine::TypeDisplayMode::SHORT:
			return typeToShortString(elm);
		default:
			return std::string("!ERROR!");
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / TYPE TO LONG STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::typeToLongString(const SpElement &elm) {
	if (nullptr == elm) {
		return std::string("NULLPTR");
	}
	switch (elm->getType()) {
		// com
		case Element::ERROR:
			return std::string("Error");
		case Element::ESTRING:
			return std::string("String");
		// std
		case Element::INTEGER:
			return std::string("Integer");
		case Element::FLOATING:
			return std::string("Floating");
		case Element::RATIONAL:
			return std::string("Rational");
		case Element::EINFINITY:
			return std::string("Infinity");
		case Element::COMPLEX:
			return std::string("Complex");
		// bin
		case Element::BOOLEAN:
			return std::string("Boolean");
		case Element::BINARY8:
			return std::string("Byte");
		case Element::BINARY16:
			return std::string("Word");
		case Element::BINARY32:
			return std::string("Dword");
		case Element::BINARY64:
			return std::string("Qword");
		// set
		case Element::ETUPLE:
			switch (GET_ETUPLE_TYPE(elm)) {
				case ETuple::TupleType::ROW:
					return std::string("Tuple[Row]");
				case ETuple::TupleType::COLUMN:
					return std::string("Tuple(Col)");
				default:
					return std::string("Tuple?");
			}
			break;
		case Element::MATRIX:
			return std::string("Matrix");
		default:
			return std::string("!ERROR!");
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / TYPE TO SHORT STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::typeToShortString(const SpElement &elm) {
	if (nullptr == elm) {
		return std::string("NULL");
	}
	switch (elm->getType()) {
		// com
		case Element::ERROR:
			return std::string("Err");
		case Element::ESTRING:
			return std::string("Str");
		// std
		case Element::INTEGER:
			return std::string("Int");
		case Element::FLOATING:
			return std::string("Flt");
		case Element::RATIONAL:
			return std::string("Rat");
		case Element::EINFINITY:
			return std::string("Inf");
		case Element::COMPLEX:
			return std::string("Cplx");
		// bin
		case Element::BOOLEAN:
			return std::string("T/F");
		case Element::BINARY8:
			return std::string("Byte");
		case Element::BINARY16:
			return std::string("Word");
		case Element::BINARY32:
			return std::string("Dwrd");
		case Element::BINARY64:
			return std::string("Qwrd");
		// set
		case Element::ETUPLE:
			switch (GET_ETUPLE_TYPE(elm)) {
				case ETuple::TupleType::ROW:
					return std::string("Tp.R");
				case ETuple::TupleType::COLUMN:
					return std::string("Tp.C");
				default:
					return std::string("Tp?");
			}
			break;
		case Element::MATRIX:
			return std::string("Mat");
		default:
			return std::string("ERR!");
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / ELEMENT TO STRING (regulate)
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::elementToString(const CalculationConfig &cfg, const SpElement &elm, const int &len) const {
	if (nullptr == elm) {
		return std::string("NULLPTR");
	}
	if (len < CONSOLE_DOTS) {
		return std::string("ERROR");
	}
	std::string value_string = elementToString(cfg, elm);
	if (value_string.length() > (std::size_t)len) {
		//    "long_long_long_string"
		// -> "long_long_l..."
		auto itr = value_string.begin() + (len - CONSOLE_DOTS);
		for (int cnt = 0; cnt < CONSOLE_DOTS; ++cnt) {
			*itr = '.';
			++itr;
		}
		value_string.erase(itr, value_string.end());
	}
	return value_string;
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / ELEMENT TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::elementToString(const CalculationConfig &cfg, const SpElement &elm) const {
	if (nullptr == elm) {
		return std::string("NULLPTR");
	}
	if (elm->hasError()) {
		return std::string("Technical error");
	}
	switch (elm->getType()) {
		// com
		case Element::ERROR:
			return errorToString(cfg, elm);
		case Element::ESTRING:
			return estringToString(cfg, elm);
		// std
		case Element::INTEGER:
			return integerToString(cfg, elm);
		case Element::FLOATING:
			return floatingToString(cfg, elm);
		case Element::RATIONAL:
			return rationalToString(cfg, elm);
		case Element::EINFINITY:
			return einfinityToString(cfg, elm);
		case Element::COMPLEX:
			return complexToString(cfg, elm);
		// bin
		case Element::BOOLEAN:
			return booleanToString(cfg, elm);
		case Element::BINARY8:
			return binary8ToString(cfg, elm);
		case Element::BINARY16:
			return binary16ToString(cfg, elm);
		case Element::BINARY32:
			return binary32ToString(cfg, elm);
		case Element::BINARY64:
			return binary64ToString(cfg, elm);
		// set
		case Element::ETUPLE:
			return etupleToString(cfg, elm);
		case Element::MATRIX:
			return matrixToString(cfg, elm);
		default:
			throw TechnicalError("Unexpected type!", __FUNCTION__);
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / COMPLEX ARGUMENT TO STRING
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::complexArgumentToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	switch (elm->getType()) {
		case Element::INTEGER: {
			auto num = GET_INTEGER_DATA(elm);
			const FloatingDisplayConfig &fcfg = refFloatingDisplayConfig();
			int digits = 0;
			switch (fcfg.getDisplayMode()) {
				case FloatingDisplayConfig::STANDARD:
					os << num;
					return os.str();
				case FloatingDisplayConfig::FIXED:
					digits = fcfg.getFixDigits();
					break;
				case FloatingDisplayConfig::SCIENTIFIC:
					digits = fcfg.getSciDigits() - 1;
					if (num > 100.0L) {
						digits -= 2;
					}
					else if (num > 10.0L) {
						digits -= 1;
					}
					break;
				case FloatingDisplayConfig::ENGINEERING:
					digits = fcfg.getEngDigits() - 1;
					if (num > 100.0L) {
						digits -= 2;
					}
					else if (num > 10.0L) {
						digits -= 1;
					}
					break;
				default:
					break;
			}
			if (digits < 0) {
				digits = 0;
			}
			os << floatToFixedString((floating_t)num, digits);
			break;
		}
		case Element::FLOATING: {
			auto num = GET_FLOATING_DATA(elm);
			const FloatingDisplayConfig &fcfg = refFloatingDisplayConfig();
			int digits = 0;
			switch (fcfg.getDisplayMode()) {
				case FloatingDisplayConfig::STANDARD:
					digits = fcfg.getStdDigits() - 1;
					if (num > 100.0L) {
						digits -= 2;
					}
					else if (num > 10.0L) {
						digits -= 1;
					}
					break;
				case FloatingDisplayConfig::FIXED:
					digits = fcfg.getFixDigits();
					break;
				case FloatingDisplayConfig::SCIENTIFIC:
					digits = fcfg.getSciDigits() - 1;
					if (num > 100.0L) {
						digits -= 2;
					}
					else if (num > 10.0L) {
						digits -= 1;
					}
					break;
				case FloatingDisplayConfig::ENGINEERING:
					digits = fcfg.getEngDigits() - 1;
					if (num > 100.0L) {
						digits -= 2;
					}
					else if (num > 10.0L) {
						digits -= 1;
					}
					break;
				default:
					break;
			}
			if (digits < 0) {
				digits = 0;
			}
			os << floatToFixedString((floating_t)num, digits);
			break;
		}
		case Element::RATIONAL: {
			auto rtemp = GET_RATIONAL_DATA(elm);
			return complexArgumentToString(cfg, GEN_FLOATING(rtemp.getFloating()));
		}
		default:
			throw TechnicalError("Unexpected type!", __FUNCTION__);
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / ERROR TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::errorToString(const CalculationConfig &cfg, const SpElement &elm) const {
	return GET_ERROR_DATA(elm);
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / ESTRING TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::estringToString(const CalculationConfig &cfg, const SpElement &elm) const {
	return GET_ESTRING_DATA(elm);
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / EINFINITY TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::einfinityToString(const CalculationConfig &cfg, const SpElement &elm) const {
	int sign = GET_EINFINITY_DATA(elm);
	if (sign > 0) {
		return std::string("+Infinity");
	}
	else if (sign < 0) {
		return std::string("-Infinity");
	}
	else {
		return std::string("Complex Infinity");
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / INTEGER TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::integerToString(const CalculationConfig &cfg, const SpElement &elm) const {
	GeneralProcessor proc;
	std::ostringstream os;
	auto num = GET_INTEGER_DATA(elm);
	if (getEulerFlag()) {
		_euler = false;
		if (0 == num) {
			os << 0;
		}
		else {
			os << integerToString(cfg, proc.abs(elm));
			os << " exp(+i";
			switch (cfg.getAngleMode()) {
				case CalculationConfig::AngleMode::RADIAN: {
					if (num > 0) {
						os << integerToString(cfg, GEN_INTEGER(0));
					}
					else {
						if (_piRad) {
							os << " Pi";
						}
						else {
							os << complexArgumentToString(cfg, GEN_FLOATING(GeneralProcessor::PI));
						}
					}
					break;
				}
				case CalculationConfig::AngleMode::DEGREE:
					if (num > 0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						os << complexArgumentToString(cfg, GEN_INTEGER(180));
					}
					os << 'd';
					break;
				case CalculationConfig::AngleMode::GRADE:
					if (num > 0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						os << complexArgumentToString(cfg, GEN_INTEGER(200));
					}
					os << 'g';
					break;
				default:
					break;
			}
			os << ')';
		}
		_euler = true;
		return os.str();
	}
	const FloatingDisplayConfig &fcfg = refFloatingDisplayConfig();
	switch (fcfg.getDisplayMode()) {
		case FloatingDisplayConfig::STANDARD:
			os << num;
			break;
		default:
			return floatingToString(cfg, GEN_FLOATING((floating_t)num));
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / FLOATING TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::floatingToString(const CalculationConfig &cfg, const SpElement &elm) const {
	GeneralProcessor proc;
	std::ostringstream os;
	floating_t num = GET_FLOATING_DATA(elm);
	os << std::uppercase;
	if (getEulerFlag()) {
		_euler = false;
		if (0.0 == num) {
			os << floatingToString(cfg, elm);
		}
		else {
			os << floatingToString(cfg, proc.abs(elm));
			os << " exp(+i";
			switch (cfg.getAngleMode()) {
				case CalculationConfig::AngleMode::RADIAN:
					if (num > 0.0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						if (_piRad) {
							os << " Pi";
						}
						else {
							os << complexArgumentToString(cfg, GEN_FLOATING(GeneralProcessor::PI));
						}
					}
					break;
				case CalculationConfig::AngleMode::DEGREE:
					if (num > 0.0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						os << complexArgumentToString(cfg, GEN_INTEGER(180));
					}
					os << 'd';
					break;
				case CalculationConfig::AngleMode::GRADE:
					if (num > 0.0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						os << complexArgumentToString(cfg, GEN_INTEGER(200));
					}
					os << 'g';
					break;
				default:
					break;
			}
			os << ')';
		}
		_euler = true;
		return os.str();
	}
	if (std::isinf(num)) {
		if (num < 0.0) {
			os << "-INFINITY";
		}
		else {
			os << "+INFINITY";
		}
	}
	else if (std::isnan(num)) {
		os << "ERROR (NaN)";
	}
	else {
		const FloatingDisplayConfig &fcfg = refFloatingDisplayConfig();
		switch (fcfg.getDisplayMode()) {
			case FloatingDisplayConfig::STANDARD:
				os << floatToStandardString(num, fcfg.getStdDigits());
				break;
			case FloatingDisplayConfig::FIXED:
				os << floatToFixedString(num, fcfg.getFixDigits());
				break;
			case FloatingDisplayConfig::SCIENTIFIC:
				os << floatToScientificString(num, fcfg.getSciDigits());
				break;
			case FloatingDisplayConfig::ENGINEERING:
				os << floatToEngineeringString(num, fcfg.getEngDigits());
				break;
			default:
				throw TechnicalError("Unknown floating display mode", __FUNCTION__);
		}
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / RATIONAL TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::rationalToString(const CalculationConfig &cfg, const SpElement &elm) const {
	GeneralProcessor proc;
	std::ostringstream os;
	rational_t rtemp = GET_RATIONAL_DATA(elm);
	if (getEulerFlag()) {
		_euler = false;
		integer_t num = rtemp.getNum();
		if (0 == num) {
			os << rtemp;
		}
		else {
			os << rationalToString(cfg, proc.abs(elm));
			os << " exp(+i";
			switch (cfg.getAngleMode()) {
				case CalculationConfig::AngleMode::RADIAN:
					if (num > 0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						if (_piRad) {
							os << " Pi";
						}
						else {
							os << complexArgumentToString(cfg, GEN_FLOATING(GeneralProcessor::PI));
						}
					}
					break;
				case CalculationConfig::AngleMode::DEGREE:
					if (num > 0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						os << complexArgumentToString(cfg, GEN_INTEGER(180));
					}
					os << 'd';
					break;
				case CalculationConfig::AngleMode::GRADE:
					if (num > 0) {
						os << complexArgumentToString(cfg, GEN_INTEGER(0));
					}
					else {
						os << complexArgumentToString(cfg, GEN_INTEGER(200));
					}
					os << 'g';
					break;
				default:
					break;
			}
			os << ')';
		}
		_euler = true;
		return os.str();
	}
	const FloatingDisplayConfig &fcfg = refFloatingDisplayConfig();
	switch (fcfg.getDisplayMode()) {
		case FloatingDisplayConfig::STANDARD: {
			bool is_finite_decimal = false;
			switch (getDecimalDisplayMode()) {
				case DecimalDisplayMode::AUTO_DECIMAL: {
					is_finite_decimal = isFiniteDecimalRational(rtemp);
					break;
				}
				case DecimalDisplayMode::FORCE_DECIMAL: {
					is_finite_decimal = true;
					break;
				}
				case DecimalDisplayMode::FORCE_FRACTIONAL: {
					is_finite_decimal = false;
					break;
				}
				default:
					break;
			}
			if (is_finite_decimal) {
				os << floatingToString(cfg, GEN_FLOATING(rtemp.getFloating()));
			}
			else switch (getFractionalDisplayMode()) {
				case FractionalDisplayMode::PROVISIONAL:
					os << rtemp;
					break;
				case FractionalDisplayMode::MIXED: {
					
					auto num = rtemp.getNum();
					auto den = rtemp.getDen();
					if (std::abs(num) >= den) {
						if (num < 0) {
							os << '-';
							num = -num;
						}
						auto ipart = num / den;
						auto new_num = num % den;
						os << ipart << '.' << new_num << '/' << den;
					}
					else {
						os << rtemp;
					}
					break;
				}
				default:
					os << rtemp;
					break;
			}
			break;
		}
		default:
			os << floatingToString(cfg, GEN_FLOATING(rtemp.getFloating()));
			break;
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / COMPLEX TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::complexToString(const CalculationConfig &cfg, const SpElement &elm) const {
	if (getEulerFlag()) {
		return complexToEulerString(cfg, elm);
	}
	else {
		return complexToReImString(cfg, elm);
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / COMPLEX TO STRING (a + ib)
// [ Update ]
// Nov 11, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::complexToReImString(const CalculationConfig &cfg, const SpElement &elm) const {
	GeneralProcessor proc;
	proc.resetFlags();
	std::ostringstream os;
	SpElement real = GET_COMPLEX_RE(elm);
	SpElement imag = GET_COMPLEX_IM(elm);
	bool is_pure_imag = false;
	bool is_one = false;
	if (real->isType(Element::INTEGER)) {
		if (0 == GET_INTEGER_DATA(real)) {
			is_pure_imag = true;
		}
	}
	if (imag->isType(Element::INTEGER)) {
		switch (GET_INTEGER_DATA(imag)) {
			case -1:
				// fall through
			case 1:
				is_one = true;
			default:
				break;
		}
	}
	if (!is_pure_imag) {
		os << elementToString(cfg, real);
	}
	if (proc.isNegative(imag) || proc.isNegativeZero(imag)) {
		os << (is_pure_imag ? "-i" : " - i");
		if (!is_one) {
			os << elementToString(cfg, proc.abs(imag));
		}
	}
	else {
		os << (is_pure_imag ? "i" : " + i");
		if (!is_one) {
			os << elementToString(cfg, proc.abs(imag));
		}
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / COMPLEX TO STRING (r exp(i arg))
// [ Update ]
// Jul 10, 2017
//====--------------------------------------------------------------------==////
std::string StringEngine::complexToEulerString(const CalculationConfig &cfg, const SpElement &elm) const {
	GeneralProcessor proc;
	if (proc.isZero(elm)) {
		return complexToReImString(cfg, elm);
	}
	proc.resetFlags();
	std::ostringstream os;
	SpElement absolute = proc.abs(elm);
	SpElement argument;
	switch (cfg.getAngleMode()) {
		case CalculationConfig::AngleMode::DEGREE:
			argument = proc.argDegree(elm);
			break;
		case CalculationConfig::AngleMode::RADIAN:
			argument = proc.argRadian(elm);
			break;
		case CalculationConfig::AngleMode::GRADE:
			argument = proc.argGrade(elm);
			break;
		default:
			throw TechnicalError("Unknown angle mode", __FUNCTION__);
	}
	if (!proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
		bool flag_backup = _euler;
		_euler = false;
		bool is_neg = proc.isNegative(argument) || proc.isNegativeZero(argument);
		if (_piRad) {
			argument = proc.div(argument, proc.pi());
		}
		os << elementToString(cfg, absolute);
		os << " exp(" << (is_neg ? "-i" : "+i");
		os << complexArgumentToString(cfg, proc.abs(argument));
		switch (cfg.getAngleMode()) {
			case CalculationConfig::AngleMode::DEGREE:
				os << 'd';
				break;
			case CalculationConfig::AngleMode::RADIAN:
				if (_piRad) {
					os << " Pi";
				}
				break;
			case CalculationConfig::AngleMode::GRADE:
				os << 'g';
				break;
			default:
				break;
		}
		os << ')';
		_euler = flag_backup;
	}
	else {
		return complexToReImString(cfg, elm);
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / BOOLEAN TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::booleanToString(const CalculationConfig &cfg, const SpElement &elm) const {
	if (GET_BOOLEAN_DATA(elm)) {
		return std::string("T");
	}
	else {
		return std::string("F");
	}
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / BINARY8 TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::binary8ToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	const uint8_t num = GET_BYTE_DATA(elm);
	switch (getNumberBaseMode()) {
		case StringEngine::NumberBaseMode::BINARY: {
			uint8_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			os << "0b";
			while (0 != pos) {
				if (pos & num) {
					os << '1';
				}
				else {
					os << '0';
				}
				pos >>= 1;
			}
			break;
		}
		case StringEngine::NumberBaseMode::OCTAL:
			os << std::oct;
			os << '0' << (unsigned short)num;
			break;
		case StringEngine::NumberBaseMode::SIGNED_DECIMAL:
			os << (short)(int8_t)num;
			break;
		case StringEngine::NumberBaseMode::UNSIGNED_DECIMAL:
			os << (unsigned short)num;
			break;
		case StringEngine::NumberBaseMode::HEXADECIMAL:
			os << "0x";
			os << std::hex << std::uppercase << std::setfill('0') << std::setw(2);
			os << (unsigned short)num;
			break;
		default:
			throw TechnicalError("Unknown base!", __FUNCTION__);
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / BINARY16 TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::binary16ToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	const uint16_t num = GET_WORD_DATA(elm);
	switch (getNumberBaseMode()) {
		case StringEngine::NumberBaseMode::BINARY: {
			uint16_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			os << "0b";
			while (0 != pos) {
				if (pos & num) {
					os << '1';
				}
				else {
					os << '0';
				}
				pos >>= 1;
			}
			break;
		}
		case StringEngine::NumberBaseMode::OCTAL:
			os << std::oct;
			os << '0' << num;
			break;
		case StringEngine::NumberBaseMode::SIGNED_DECIMAL:
			os << (int16_t)num;
			break;
		case StringEngine::NumberBaseMode::UNSIGNED_DECIMAL:
			os << num;
			break;
		case StringEngine::NumberBaseMode::HEXADECIMAL:
			os << "0x";
			os << std::hex << std::uppercase << std::setfill('0') << std::setw(4);
			os << num;
			break;
		default:
			throw TechnicalError("Unknown base!", __FUNCTION__);
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / BINARY32 TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::binary32ToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	const uint32_t num = GET_DWORD_DATA(elm);
	switch (getNumberBaseMode()) {
		case StringEngine::NumberBaseMode::BINARY: {
			uint32_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			os << "0b";
			while (0 != pos) {
				if (pos & num) {
					os << '1';
				}
				else {
					os << '0';
				}
				pos >>= 1;
			}
			break;
		}
		case StringEngine::NumberBaseMode::OCTAL:
			os << std::oct;
			os << '0' << num;
			break;
		case StringEngine::NumberBaseMode::SIGNED_DECIMAL:
			os << (int32_t)num;
			break;
		case StringEngine::NumberBaseMode::UNSIGNED_DECIMAL:
			os << num;
			break;
		case StringEngine::NumberBaseMode::HEXADECIMAL:
			os << "0x";
			os << std::hex << std::uppercase << std::setfill('0') << std::setw(8);
			os << num;
			break;
		default:
			throw TechnicalError("Unknown base!", __FUNCTION__);
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / BINARY64 TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::binary64ToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	const uint64_t num = GET_QWORD_DATA(elm);
	switch (getNumberBaseMode()) {
		case StringEngine::NumberBaseMode::BINARY: {
			uint64_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			os << "0b";
			while (0 != pos) {
				if (pos & num) {
					os << '1';
				}
				else {
					os << '0';
				}
				pos >>= 1;
			}
			break;
		}
		case StringEngine::NumberBaseMode::OCTAL:
			os << std::oct;
			os << '0' << num;
			break;
		case StringEngine::NumberBaseMode::SIGNED_DECIMAL:
			os << (int64_t)num;
			break;
		case StringEngine::NumberBaseMode::UNSIGNED_DECIMAL:
			os << num;
			break;
		case StringEngine::NumberBaseMode::HEXADECIMAL:
			os << "0x";
			os << std::hex << std::uppercase << std::setfill('0') << std::setw(16);
			os << num;
			break;
		default:
			throw TechnicalError("Unknown base!", __FUNCTION__);
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / ETUPLE TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::etupleToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	std::size_t size = GET_ETUPLE_SIZE(elm);
	switch (GET_ETUPLE_TYPE(elm)) {
		case ETuple::TupleType::ROW:
			os << '[';
			break;
		case ETuple::TupleType::COLUMN:
			os << '(';
			break;
		default:
			os << '_';
			break;
	}
	if (size > 0) {
		os << elementToString(cfg, GET_ETUPLE_DATA(elm, 0));
	}
	for (std::size_t ucnt = 1; ucnt < size; ++ucnt) {
		os << ", ";
		os << elementToString(cfg, GET_ETUPLE_DATA(elm, ucnt));
	}
	switch (GET_ETUPLE_TYPE(elm)) {
		case ETuple::TupleType::ROW:
			os << ']';
			break;
		case ETuple::TupleType::COLUMN:
			os << ')';
			break;
		default:
			os << '_';
			break;
	}
	return os.str();
}

////==--------------------------------------------------------------------====//
// STRING ENGINE / MATRIX TO STRING
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
std::string StringEngine::matrixToString(const CalculationConfig &cfg, const SpElement &elm) const {
	std::ostringstream os;
	const std::size_t size_m = GET_MATRIX_SIZE_M(elm);
	const std::size_t size_n = GET_MATRIX_SIZE_N(elm);
	os << '[';
	if (size_m > 0) {
		os << '[';
		if (size_n > 0) {
			os << elementToString(cfg, GET_MATRIX_DATA(elm, 0, 0));
		}
		for (std::size_t cnt_x = 1; cnt_x < size_n; ++cnt_x) {
			os << ", ";
			os << elementToString(cfg, GET_MATRIX_DATA(elm, 0, cnt_x));
		}
		os << ']';
	}
	for (std::size_t cnt_y = 1; cnt_y < size_m; ++cnt_y) {
		os << ", [";
		if (size_n > 0) {
			os << elementToString(cfg, GET_MATRIX_DATA(elm, cnt_y, 0));
		}
		for (std::size_t cnt_x = 1; cnt_x < size_n; ++cnt_x) {
			os << ", ";
			os << elementToString(cfg, GET_MATRIX_DATA(elm, cnt_y, cnt_x));
		}
		os << ']';
	}
	os << ']';
	return os.str();
}

} // namespace engine
