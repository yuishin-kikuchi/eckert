#include "NumericCheck.h"

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / METRIC PREFIX TO SYMBOL
//====--------------------------------------------------------------------==////
const std::map<NumericCheck::MetricPrefix, std::string>
NumericCheck::prefixSymbol = {
	{ NumericCheck::MetricPrefix::YOCTO, "y" },
	{ NumericCheck::MetricPrefix::ZEPTO, "z" },
	{ NumericCheck::MetricPrefix::ATTO, "a" },
	{ NumericCheck::MetricPrefix::FEMTO, "f" },
	{ NumericCheck::MetricPrefix::PICO, "p" },
	{ NumericCheck::MetricPrefix::NANO, "n" },
	{ NumericCheck::MetricPrefix::MICRO, "u" },
	{ NumericCheck::MetricPrefix::MILLI, "m" },
	{ NumericCheck::MetricPrefix::CENTI, "c" },
	{ NumericCheck::MetricPrefix::DECI, "d" },
	{ NumericCheck::MetricPrefix::DECA, "da" },
	{ NumericCheck::MetricPrefix::HECTO, "h" },
	{ NumericCheck::MetricPrefix::KILO, "k" },
	{ NumericCheck::MetricPrefix::MEGA, "M" },
	{ NumericCheck::MetricPrefix::GIGA, "G" },
	{ NumericCheck::MetricPrefix::TERA, "T" },
	{ NumericCheck::MetricPrefix::PETA, "P" },
	{ NumericCheck::MetricPrefix::EXA, "E" },
	{ NumericCheck::MetricPrefix::ZETTA, "Z" },
	{ NumericCheck::MetricPrefix::YOTTA, "Y" },
	{ NumericCheck::MetricPrefix::KIBI, "Ki" },
	{ NumericCheck::MetricPrefix::MEBI, "Mi" },
	{ NumericCheck::MetricPrefix::GIBI, "Gi" },
	{ NumericCheck::MetricPrefix::TEBI, "Ti" },
	{ NumericCheck::MetricPrefix::PEBI, "Pi" },
	{ NumericCheck::MetricPrefix::EXBI, "Ei" },
	{ NumericCheck::MetricPrefix::ZEBI, "Zi" },
	{ NumericCheck::MetricPrefix::YOBI, "Yi" },
};

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / REMOVE IMAGINARY
//====--------------------------------------------------------------------==////
void NumericCheck::removeImag(std::string &r_strToken) {
	std::string::size_type pos = 0;
	switch (r_strToken.size()) {
		case 0:
			// fall through
		case 1:
			return;
		case 2:
			switch (r_strToken.at(pos)) {
				case '+':
					// fall through
				case '-':
					return;
				default:
					break;
			}
			break;
		default:
			break;
	}
	switch (r_strToken.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	switch (r_strToken.at(pos)) {
		case 'I':
			// fall through
		case 'i':
			r_strToken.erase(pos, 1);
			break;
		default:
			switch (r_strToken.at(r_strToken.length() - 1)) {
			case 'I':
				// fall through
			case 'i':
				r_strToken.erase(r_strToken.length() - 1, 1);
				break;
			default:
				break;
			}
			break;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / WHAT KIND OF NUMBER
//====--------------------------------------------------------------------==////
NumericCheck::NumberType NumericCheck::whatNumber(const std::string &token) {
	if (isInfinity(token)) {
		return NumericCheck::NumberType::T_INFINITY;
	}
	else if (isInteger(token)) {
		return NumericCheck::NumberType::INTEGER;
	}
	else if (isDecimal(token)) {
		return NumericCheck::NumberType::DECIMAL;
	}
	else if (isExponential(token)) {
		return NumericCheck::NumberType::EXPONENTIAL;
	}
	else if (isImagInteger(token)) {
		return NumericCheck::NumberType::IMAG_INTEGER;
	}
	else if (isImagDecimal(token)) {
		return NumericCheck::NumberType::IMAG_DECIMAL;
	}
	else if (isImagExponential(token)) {
		return NumericCheck::NumberType::IMAG_EXPONENTIAL;
	}
	else {
		return NumericCheck::NumberType::NOT_NUMBER;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / INFINITY CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isInfinity(const std::string &token) {
	std::string upper_token = token;
	for (auto&& x : upper_token) {
		x = std::toupper(x);
	}
	return(
		(!upper_token.compare("INF")) ||
		(!upper_token.compare("+INF")) ||
		(!upper_token.compare("-INF")) ||
		(!upper_token.compare("INFINITY")) ||
		(!upper_token.compare("+INFINITY")) ||
		(!upper_token.compare("-INFINITY"))
	);
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / UNSIGNED CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isUnsigned(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 1) {
		// 1 char at least
		return false;
	}
	while (pos < len) {
		if (!isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	// if no errors, it is integer
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / INTEGER CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isInteger(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 1) {
		// 1 char at least
		return false;
	}
	switch (token.at(pos)) {
		// Only SIGN or DIGIT can be allowed as first char
		case '+':
			// fall through
		case '-':
			++pos;
			if (len == pos) {
				return false;
			}
			break;
		default:
			break;
	}
	while (pos < len) {
		if (!isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	// if no errors, it is integer
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / DECIMAL CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isDecimal(const std::string &token) {
	// spaces cannot be allowed
	bool has_dot = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 2) {
		// 2 char at least
		return false;
	}
	switch (token.at(pos)) {
		// Only SIGN, DOT or DIGIT can be allowed as first char
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	if ('.' == token.at(pos)) {
		has_dot = true;
		++pos;
	}
	if (has_dot && (pos == len)) {
		return false;
	}
	while (pos < len) {
		if ('.' == token.at(pos)) {
			if (has_dot) {
				// only one dot is_ allowed
				return false;
			}
			else {
				// set flag on first time to find dot
				has_dot = true;
			}
		}
		else if (!isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	if (!has_dot) {
		return false;
	}
	// token is integer if it doesn't have dot
	// if no errors, token is fractional
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / EXPONENTIAL NOTATION CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isExponential(const std::string &token) {
	// spaces cannot be allowed
	bool has_dot = false;
	bool has_eex = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 3) {
		// 3 char at least
		return false;
	}
	// exp notation must contain more than 2 chras
	switch (token.at(pos)) {
		// Only SIGN, DOT or DIGIT can be allowed as first char
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(pos)) {
		case 'E':
			// fall through
		case 'e':
			// E as first char is_ not allowed
			return false;
		case '.':
			has_dot = true;
			++pos;
			break;
	}
	if (has_dot) {
		if (len == pos) {
			return false;
		}
		switch (token.at(pos)) {
			case 'E':
				// fall through
			case 'e':
				return false;
			default:
				break;
		}
	}
	while (pos < len) {
		if (has_eex) {
			break;
		}
		switch (token.at(pos)) {
			case 'E':
				// fall through
			case 'e':
				has_eex = true;
				break;
			case '.':
				if (has_dot) {
					return false;
				}
				else {
					has_dot = true;
				}
				break;
			default:
				if (!isdigit(token.at(pos))) {
					return false;
				}
				break;
		}
		++pos;
	}
	if (pos == len) {
		return false;
	}
	switch (token.at(pos)) {
		// Only SIGN, DOT or DIGIT can be allowed as first char
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	if (pos == len) {
		// ending with e is_ not allowed
		return false;
	}
	while (pos < len) {
		if (!isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	if (!has_eex) {
		// if it doesn't have E, it is_ error
		return false;
	}
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IMAGINARY INTEGER CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isImagInteger(const std::string &token) {
	bool has_imag = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 1) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(pos)) {
		case 'I':
			// fall through
		case 'i':
			has_imag = true;
			++pos;
			if (pos == len) {
				return true;
			}
			break;
		default:
			break;
	}
	switch (token.at(len - 1)) {
		case 'I':
			// fall through
		case 'i':
			if (!has_imag) {
				has_imag = true;
				--len;
			}
			else {
				return false;
			}
			break;
		default:
			break;
	}
	if (has_imag) {
		while (pos < len) {
			if (!std::isdigit(token.at(pos))) {
				return false;
			}
			++pos;
		}
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IMAGINARY DECIMAL CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isImagDecimal(const std::string &token) {
	bool has_imag = false;
	bool has_dot = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 3) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(pos)) {
		case 'I':
			// fall through
		case 'i':
			has_imag = true;
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(len - 1)) {
		case 'I':
			// fall through
		case 'i':
			if (!has_imag) {
				has_imag = true;
				--len;
			}
			else {
				return false;
			}
			break;
		default:
			break;
	}
	if (has_imag) {
		if (('.' == token.at(pos)) && (pos + 1 == len)) {
			return false;
		}
		while (pos < len) {
			if ('.' == token.at(pos)) {
				if (has_dot) {
					return false;
				}
				else {
					has_dot = true;
				}
			}
			else if (!std::isdigit(token.at(pos))) {
				return false;
			}
			++pos;
		}
		if (!has_dot) {
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IMAGINARY EXPONENTIAL NOTATION CHECK
//====--------------------------------------------------------------------==////
bool NumericCheck::isImagExponential(const std::string &token) {
	bool has_imag = false;
	bool has_dot = false;
	bool has_eex = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 4) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(pos)) {
		case 'I':
			// fall through
		case 'i':
			has_imag = true;
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(len - 1)) {
		case 'I':
			// fall through
		case 'i':
			if (!has_imag) {
				has_imag = true;
				--len;
			}
			else
				return false;
			break;
		default:
			break;
	}
	if (has_imag) {
		switch (token.at(pos)) {
			case 'E':
				// fall throubh
			case 'e':
				return false;
			case '.':
				has_dot = true;
				++pos;
			default:
				break;
		}
		if (has_dot) {
			switch (token.at(pos)) {
				case 'E':
					// fall through
				case 'e':
					return false;
				default:
					break;
			}
		}
		while (pos < len) {
			switch (token.at(pos)) {
				case 'E':
					// fall through
				case 'e':
					has_eex = true;
					break;
				case '.':
					if (has_dot) {
						return false;
					}
					else {
						has_dot = true;
					}
					break;
				default:
					if (!std::isdigit(token.at(pos))) {
						return false;
					}
					break;
			}
			++pos;
			if (has_eex) {
				break;
			}
		}
		switch (token.at(pos)) {
			case '+':
				// fall through
			case '-':
				++pos;
				break;
			default:
				break;
		}
		if (pos == len) {
			return false;
		}
		while (pos < len) {
			if (!std::isdigit(token.at(pos))) {
				return false;
			}
			++pos;
		}
		if (!has_eex) {
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / WHAT KIND OF NUMBER
//====--------------------------------------------------------------------==////
NumericCheck::NumberType NumericCheck::whatNumber(const std::string &token, NumericCheck::MetricPrefix &mp) {
	if (isInfinity(token)) {
		return NumericCheck::NumberType::T_INFINITY;
	}
	else if (isInteger(token, mp)) {
		return NumericCheck::NumberType::INTEGER;
	}
	else if (isDecimal(token, mp)) {
		return NumericCheck::NumberType::DECIMAL;
	}
	else if (isExponential(token, mp)) {
		return NumericCheck::NumberType::EXPONENTIAL;
	}
	else if (isImagInteger(token, mp)) {
		return NumericCheck::NumberType::IMAG_INTEGER;
	}
	else if (isImagDecimal(token, mp)) {
		return NumericCheck::NumberType::IMAG_DECIMAL;
	}
	else if (isImagExponential(token, mp)) {
		return NumericCheck::NumberType::IMAG_EXPONENTIAL;
	}
	else {
		return NumericCheck::NumberType::NOT_NUMBER;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / INTEGER CHECK WITH CHECKING METRIC PREFIX
//====--------------------------------------------------------------------==////
bool NumericCheck::isInteger(const std::string &token, NumericCheck::MetricPrefix &mp) {
	std::size_t pos = 0;
	std::size_t len = token.length();
	len -= checkPrefix(token, mp);
	if (len < 1) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			if (len == pos) {
				return false;
			}
			break;
		default:
			break;
	}
	while (pos < len) {
		if (!isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / DECIMAL CHECK WITH CHECKING METRIC PREFIX
//====--------------------------------------------------------------------==////
bool NumericCheck::isDecimal(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool has_dot = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	len -= checkPrefix(token, mp);
	if (len < 2) {
		// 2 char at least
		return false;
	}
	pos = 0;
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			if (len == pos) {
				return false;
			}
			break;
		default:
			break;
	}
	if ('.' == token.at(pos)) {
		has_dot = true;
		++pos;
	}
	if (has_dot && (pos == len)) {
		return false;
	}
	while (pos < len) {
		if ('.' == token.at(pos)) {
			if (has_dot) {
				return false;
			}
			else {
				has_dot = true;
			}
		}
		else if (!std::isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	if (!has_dot) {
		return false;
	}
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / EXPONENTIAL NOTATION CHECK WITH CHECKING METRIC PREFIX
//====--------------------------------------------------------------------==////
bool NumericCheck::isExponential(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool has_dot = false;
	bool has_eex = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	len -= checkPrefix(token, mp);
	if (len < 3) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(pos)) {
		case 'E':
			// fall through
		case 'e':
			return false;
		case '.':
			has_dot = true;
			++pos;
			break;
		default:
			break;
	}
	if (has_dot) {
		if (len == pos) {
			return false;
		}
		switch (token.at(pos)) {
			case 'E':
				// fall through
			case 'e':
				return false;
			default:
				break;
		}
	}
	while (pos < len) {
		if (has_eex) {
			break;
		}
		switch (token.at(pos)) {
			case 'E':
				// fall through
			case 'e':
				has_eex = true;
				break;
			case '.':
				if (has_dot) {
					return false;
				}
				else {
					has_dot = true;
				}
				break;
			default:
				if (!std::isdigit(token.at(pos))) {
					return false;
				}
				break;
		}
		++pos;
	}
	if (pos == len) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			break;
		default:
			break;
	}
	if (pos == len) {
		return false;
	}
	while (pos < len) {
		if (!std::isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	if (!has_eex) {
		return false;
	}
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / Check prefix
//====--------------------------------------------------------------------==////
std::size_t NumericCheck::checkPrefix(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool is_prefixed = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	std::size_t size = 0;
	mp = NumericCheck::MetricPrefix::ONE;
	if (len > 1) {
		if (len > 2) {
			pos = len - 1;
			switch (token.at(pos)) {
				case 'i':
					--pos;
					switch (token.at(pos)) {
					case 'k':
						// fall through
					case 'K':
						mp = NumericCheck::MetricPrefix::KIBI;
						is_prefixed = true;
						break;
					case 'm':
						// fall through
					case 'M':
						mp = NumericCheck::MetricPrefix::MEBI;
						is_prefixed = true;
						break;
					case 'g':
						// fall through
					case 'G':
						mp = NumericCheck::MetricPrefix::GIBI;
						is_prefixed = true;
						break;
					case 't':
						// fall through
					case 'T':
						mp = NumericCheck::MetricPrefix::TEBI;
						is_prefixed = true;
						break;
					case 'p':
						// fall through
					case 'P':
						mp = NumericCheck::MetricPrefix::PEBI;
						is_prefixed = true;
						break;
					case 'e':
						// fall through
					case 'E':
						mp = NumericCheck::MetricPrefix::EXBI;
						is_prefixed = true;
						break;
					case 'z':
						// fall through
					case 'Z':
						mp = NumericCheck::MetricPrefix::ZEBI;
						is_prefixed = true;
						break;
					case 'y':
						// fall through
					case 'Y':
						mp = NumericCheck::MetricPrefix::YOBI;
						is_prefixed = true;
						break;
					default:
						break;
					}
					break;
				case 'a':
					--pos;
					if (token.at(pos) == 'd') {
						mp = NumericCheck::MetricPrefix::DECA;
						is_prefixed = true;
					}
					break;
				default:
					break;
			}
			if (is_prefixed) {
				size = 2;
			}
		}
		if (!is_prefixed) {
			pos = len - 1;
			switch (token.at(pos)) {
				case 'y':
					mp = NumericCheck::MetricPrefix::YOCTO;
					is_prefixed = true;
					break;
				case 'z':
					mp = NumericCheck::MetricPrefix::ZEPTO;
					is_prefixed = true;
					break;
				case 'a':
					mp = NumericCheck::MetricPrefix::ATTO;
					is_prefixed = true;
					break;
				case 'f':
					mp = NumericCheck::MetricPrefix::FEMTO;
					is_prefixed = true;
					break;
				case 'p':
					mp = NumericCheck::MetricPrefix::PICO;
					is_prefixed = true;
					break;
				case 'n':
					mp = NumericCheck::MetricPrefix::NANO;
					is_prefixed = true;
					break;
				case 'u':
					mp = NumericCheck::MetricPrefix::MICRO;
					is_prefixed = true;
					break;
				case 'm':
					mp = NumericCheck::MetricPrefix::MILLI;
					is_prefixed = true;
					break;
				case 'c':
					mp = NumericCheck::MetricPrefix::CENTI;
					is_prefixed = true;
					break;
				case 'd':
					mp = NumericCheck::MetricPrefix::DECI;
					is_prefixed = true;
					break;
				case 'h':
					mp = NumericCheck::MetricPrefix::HECTO;
					is_prefixed = true;
					break;
				case 'K':
					// fall through
				case 'k':
					mp = NumericCheck::MetricPrefix::KILO;
					is_prefixed = true;
					break;
				case 'M':
					mp = NumericCheck::MetricPrefix::MEGA;
					is_prefixed = true;
					break;
				case 'G':
					mp = NumericCheck::MetricPrefix::GIGA;
					is_prefixed = true;
					break;
				case 'T':
					mp = NumericCheck::MetricPrefix::TERA;
					is_prefixed = true;
					break;
				case 'P':
					mp = NumericCheck::MetricPrefix::PETA;
					is_prefixed = true;
					break;
				case 'E':
					mp = NumericCheck::MetricPrefix::EXA;
					is_prefixed = true;
					break;
				case 'Z':
					mp = NumericCheck::MetricPrefix::ZETTA;
					is_prefixed = true;
					break;
				case 'Y':
					mp = NumericCheck::MetricPrefix::YOTTA;
					is_prefixed = true;
					break;
				default:
					break;
			}
			if (is_prefixed) {
				size = 1;
			}
		}
	}
	return size;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / Check imaginary integer and prefix
//====--------------------------------------------------------------------==////
bool NumericCheck::isImagInteger(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool has_imag = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	std::size_t prefix_size = 0;
	prefix_size = checkPrefixImag(token, mp);
	if (len - prefix_size < 1) {
		return false;
	}
	switch (token.at(pos)) {
		case '+':
			// fall through
		case '-':
			++pos;
			if (len == pos) {
				return false;
			}
			break;
		default:
			break;
	}
	switch (token.at(pos)) {
		case 'I':
			// fall through
		case 'i':
			has_imag = true;
			++pos;
			if (pos == len) {
				return true;
			}
			else if ((pos == 1) && (prefix_size + 1 == len)) {
				return false;
			}
			break;
		default:
			break;
	}
	switch (token.at(len - 1)) {
		case 'I':
			// fall through
		case 'i':
			if (!has_imag) {
				has_imag = true;
				--len;
			}
			else if (prefix_size != 2) {
				return false;
			}
			break;
		default:
			break;
	}
	if (has_imag) {
		len -= prefix_size;
		while (pos < len) {
			if (!std::isdigit(token.at(pos))) {
				return false;
			}
			++pos;
		}
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / Check imaginary decimal with prefix
//====--------------------------------------------------------------------==////
bool NumericCheck::isImagDecimal(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool has_imag = false;
	bool has_dot = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	std::size_t prefix_size = 0;
	prefix_size = checkPrefixImag(token, mp);
	if (len - prefix_size < 3) {
		return false;
	}
	switch (token.at(pos)) {
			case '+':
				// fall through
			case '-':
				++pos;
				break;
			default:
				break;
		}
		switch (token.at(pos)) {
			case 'I':
				// fall through
			case 'i':
				has_imag = true;
				++pos;
				break;
			default:
				break;
	}
	switch (token.at(len - 1)) {
		case 'I':
			// fall through
		case 'i':
			if (!has_imag) {
				has_imag = true;
				--len;
			}
			else if (prefix_size != 2) {
				return false;
			}
			break;
		default:
			break;
	}
	if (has_imag) {
		len -= prefix_size;
		if (('.' == token.at(pos)) && (pos + 1 == len)) {
			return false;
		}
		while (pos < len) {
			if ('.' == token.at(pos)) {
				if (has_dot) {
					return false;
				}
				else {
					has_dot = true;
				}
			}
			else if (!std::isdigit(token.at(pos))) {
				return false;
			}
			++pos;
		}
		if (!has_dot) {
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / Check imaginary exponential with prefix
//====--------------------------------------------------------------------==////
bool NumericCheck::isImagExponential(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool has_imag = false;
	bool has_dot = false;
	bool has_eex = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	std::size_t prefix_size = 0;
	prefix_size = checkPrefixImag(token, mp);
	if (len - prefix_size < 4) {
		return false;
	}
	switch (token.at(pos)) {
	case '+':
		// fall through
	case '-':
		++pos;
		break;
	default:
		break;
	}
	switch (token.at(pos)) {
		case 'I':
			// fall through
		case 'i':
			has_imag = true;
			++pos;
			break;
		default:
			break;
	}
	switch (token.at(len - 1)) {
		case 'I':
			// fall through
		case 'i':
			if (!has_imag) {
				has_imag = true;
				--len;
			}
			else if (prefix_size != 2) {
				return false;
			}
			break;
		default:
			break;
	}
	if (has_imag) {
		len -= prefix_size;
		switch (token.at(pos)) {
			case 'E':
				// fall through
			case 'e':
				return false;
			case '.':
				has_dot = true;
				++pos;
			default:
				break;
		}
		if (has_dot) {
			switch (token.at(pos)) {
				case 'E':
					// fall through
				case 'e':
					return false;
				default:
					break;
			}
		}
		while (pos < len) {
			switch (token.at(pos)) {
				case 'E':
					// fall through
				case 'e':
					has_eex = true;
					break;
				case '.':
					if (has_dot) {
						return false;
					}
					else {
						has_dot = true;
					}
					break;
				default:
					if (!std::isdigit(token.at(pos))) {
						return false;
					}
					break;
			}
			++pos;
			if (has_eex) {
				break;
			}
		}
		switch (token.at(pos)) {
			case '+':
				// fall through
			case '-':
				++pos;
				break;
			default:
				break;
		}
		if (pos == len) {
			return false;
		}
		while (pos < len) {
			if (!std::isdigit(token.at(pos))) {
				return false;
			}
			++pos;
		}
		if (!has_eex) {
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / Check prefix (imaginary)
//====--------------------------------------------------------------------==////
std::size_t NumericCheck::checkPrefixImag(const std::string &token, NumericCheck::MetricPrefix &mp) {
	bool is_prefixed = false;
	bool has_postfix_i = false;
	std::size_t pos = 0;
	std::size_t len = token.length();
	std::size_t size = 0;
	mp = NumericCheck::MetricPrefix::ONE;
	if (len > 1) {
		pos = len - 1;
		switch (token.at(pos)) {
			case 'i':
				has_postfix_i = true;
				// fall through
			case 'I':
				break;
			default:
				break;
		}
		pos = 0;
		switch (token.at(pos)) {
			case '+':
				// fall through
			case '-':
				pos++;
				break;
			default:
				break;
		}
		switch (token.at(pos)) {
			case 'i':
				// fall through
			case 'I':
				if (has_postfix_i) {
					has_postfix_i = false;
				}
				break;
			default:
				--len;
				break;
		}
	}
	if (len > 1) {
		if (len > 2) {
			pos = len - 1;
			switch (token.at(pos)) {
				case 'i':
					--pos;
					switch (token.at(pos)) {
						case 'k':
							// fall through
						case 'K':
							mp = NumericCheck::MetricPrefix::KIBI;
							is_prefixed = true;
							break;
						case 'm':
							// fall through
						case 'M':
							mp = NumericCheck::MetricPrefix::MEBI;
							is_prefixed = true;
							break;
						case 'g':
							// fall through
						case 'G':
							mp = NumericCheck::MetricPrefix::GIBI;
							is_prefixed = true;
							break;
						case 't':
							// fall through
						case 'T':
							mp = NumericCheck::MetricPrefix::TEBI;
							is_prefixed = true;
							break;
						case 'p':
							// fall through
						case 'P':
							mp = NumericCheck::MetricPrefix::PEBI;
							is_prefixed = true;
							break;
						case 'e':
							// fall through
						case 'E':
							mp = NumericCheck::MetricPrefix::EXBI;
							is_prefixed = true;
							break;
						case 'z':
							// fall through
						case 'Z':
							mp = NumericCheck::MetricPrefix::ZEBI;
							is_prefixed = true;
							break;
						case 'y':
							// fall through
						case 'Y':
							mp = NumericCheck::MetricPrefix::YOBI;
							is_prefixed = true;
							break;
						default:
							break;
					}
					break;
				case 'a':
					--pos;
					if (token.at(pos) == 'd') {
						mp = NumericCheck::MetricPrefix::DECA;
						is_prefixed = true;
					}
					break;
				default:
					break;
			}
			if (is_prefixed) {
				size = 2;
			}
		}
		if (!is_prefixed) {
			pos = len - 1;
			switch (token.at(pos)) {
				case 'y':
					mp = NumericCheck::MetricPrefix::YOCTO;
					is_prefixed = true;
					break;
				case 'z':
					mp = NumericCheck::MetricPrefix::ZEPTO;
					is_prefixed = true;
					break;
				case 'a':
					mp = NumericCheck::MetricPrefix::ATTO;
					is_prefixed = true;
					break;
				case 'f':
					mp = NumericCheck::MetricPrefix::FEMTO;
					is_prefixed = true;
					break;
				case 'p':
					mp = NumericCheck::MetricPrefix::PICO;
					is_prefixed = true;
					break;
				case 'n':
					mp = NumericCheck::MetricPrefix::NANO;
					is_prefixed = true;
					break;
				case 'u':
					mp = NumericCheck::MetricPrefix::MICRO;
					is_prefixed = true;
					break;
				case 'm':
					mp = NumericCheck::MetricPrefix::MILLI;
					is_prefixed = true;
					break;
				case 'c':
					mp = NumericCheck::MetricPrefix::CENTI;
					is_prefixed = true;
					break;
				case 'd':
					mp = NumericCheck::MetricPrefix::DECI;
					is_prefixed = true;
					break;
				case 'h':
					mp = NumericCheck::MetricPrefix::HECTO;
					is_prefixed = true;
					break;
				case 'K':
					// fall through
				case 'k':
					mp = NumericCheck::MetricPrefix::KILO;
					is_prefixed = true;
					break;
				case 'M':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::MEGA;
						is_prefixed = true;
					}
					break;
				case 'G':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::GIGA;
						is_prefixed = true;
					}
					break;
				case 'T':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::TERA;
						is_prefixed = true;
					}
					break;
				case 'P':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::PETA;
						is_prefixed = true;
					}
					break;
				case 'E':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::EXA;
						is_prefixed = true;
					}
					break;
				case 'Z':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::ZETTA;
						is_prefixed = true;
					}
					break;
				case 'Y':
					if (!has_postfix_i) {
						mp = NumericCheck::MetricPrefix::YOTTA;
						is_prefixed = true;
					}
					break;
				default:
					break;
			}
			if (is_prefixed) {
				size = 1;
			}
		}
	}
	return size;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / ERASE PREFIX
//====--------------------------------------------------------------------==////
void NumericCheck::erasePrefix(std::string &str, const NumericCheck::NumberType &type, const NumericCheck::MetricPrefix &prefix) {
	std::size_t len = str.length();
	switch (prefix) {
		case NumericCheck::MetricPrefix::YOCTO:
			// fall through
		case NumericCheck::MetricPrefix::ZEPTO:
			// fall through
		case NumericCheck::MetricPrefix::ATTO:
			// fall through
		case NumericCheck::MetricPrefix::FEMTO:
			// fall through
		case NumericCheck::MetricPrefix::PICO:
			// fall through
		case NumericCheck::MetricPrefix::NANO:
			// fall through
		case NumericCheck::MetricPrefix::MICRO:
			// fall through
		case NumericCheck::MetricPrefix::MILLI:
			// fall through
		case NumericCheck::MetricPrefix::CENTI:
			// fall through
		case NumericCheck::MetricPrefix::DECI:
			// fall through
		case NumericCheck::MetricPrefix::HECTO:
			// fall through
		case NumericCheck::MetricPrefix::KILO:
			// fall through
		case NumericCheck::MetricPrefix::MEGA:
			// fall through
		case NumericCheck::MetricPrefix::GIGA:
			// fall through
		case NumericCheck::MetricPrefix::TERA:
			// fall through
		case NumericCheck::MetricPrefix::PETA:
			// fall through
		case NumericCheck::MetricPrefix::EXA:
			// fall through
		case NumericCheck::MetricPrefix::ZETTA:
			// fall through
		case NumericCheck::MetricPrefix::YOTTA:
			switch (type) {
				case NumericCheck::NumberType::INTEGER:
					// fall through
				case NumericCheck::NumberType::DECIMAL:
					// fall through
				case NumericCheck::NumberType::EXPONENTIAL:
					str.erase(len - 1, 1);
					break;
				case NumericCheck::NumberType::IMAG_INTEGER:
				// fall through
				case NumericCheck::NumberType::IMAG_DECIMAL:
				// fall through
				case NumericCheck::NumberType::IMAG_EXPONENTIAL: {
					// erase prefix
					auto ch = str.at(len - 1);
					if (('i' == ch) || ('I' == ch)) {
						str.erase(len - 2, 1);
					}
					else {
						str.erase(len - 1, 1);
					}
					break;
				}
				default:
					return;
			}
			break;
		case NumericCheck::MetricPrefix::DECA:
			// fall through
		case NumericCheck::MetricPrefix::KIBI:
			// fall through
		case NumericCheck::MetricPrefix::MEBI:
			// fall through
		case NumericCheck::MetricPrefix::GIBI:
			// fall through
		case NumericCheck::MetricPrefix::TEBI:
			// fall through
		case NumericCheck::MetricPrefix::PEBI:
			// fall through
		case NumericCheck::MetricPrefix::EXBI:
			// fall through
		case NumericCheck::MetricPrefix::ZEBI:
			// fall through
		case NumericCheck::MetricPrefix::YOBI:
			switch (type) {
				case NumericCheck::NumberType::INTEGER:
					// fall through
				case NumericCheck::NumberType::DECIMAL:
					// fall through
				case NumericCheck::NumberType::EXPONENTIAL:
					// erase prefix
					str.erase(len - 2, 2);
					break;
				case NumericCheck::NumberType::IMAG_INTEGER:
					// fall through
				case NumericCheck::NumberType::IMAG_DECIMAL:
					// fall through
				case NumericCheck::NumberType::IMAG_EXPONENTIAL: {
					// erase prefix
					auto ch = str.at(len - 2);
					if (('i' == ch) || ('I' == ch)) {
						str.erase(len - 3, 2);
					}
					else {
						str.erase(len - 2, 2);
					}
					break;
				}
				default:
					break;
			}
			break;
		default:
			break;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / WHAT KIND OF DATA
//====--------------------------------------------------------------------==////
NumericCheck::DataType NumericCheck::whatData(const std::string &token) {
	if (isTrue(token)) {
		return NumericCheck::DataType::TRUE;
	}
	else if (isFalse(token)) {
		return NumericCheck::DataType::FALSE;
	}
	else if (isInteger(token)) {
		return NumericCheck::DataType::DECIMAL;
	}
	else if (isPreUnsigned(token)) {
		return NumericCheck::DataType::UNSIGNED;
	}
	else if (isHexadecimal(token)) {
		return NumericCheck::DataType::HEXADECIMAL;
	}
	else if (isBinary(token)) {
		return NumericCheck::DataType::BINARY;
	}
	else if (isZeroOctal(token)) {
		return NumericCheck::DataType::ZERO_OCTAL;
	}
	else if (isOctal(token)) {
		return NumericCheck::DataType::OCTAL;
	}
	else {
		return NumericCheck::DataType::NOT_DATA;
	}
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IS TRUE STRING
//====--------------------------------------------------------------------==////
bool NumericCheck::isTrue(const std::string &token) {
	std::string upper_token = token;
	for (auto&& x : upper_token) {
		x = std::toupper(x);
	}
	return (
		(!upper_token.compare("TRUE")) ||
		(!upper_token.compare("T"))
	);
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IS FALSE STRING
//====--------------------------------------------------------------------==////
bool NumericCheck::isFalse(const std::string &token) {
	std::string upper_token = token;
	for (auto&& x : upper_token) {
		x = std::toupper(x);
	}
	return (
		(!upper_token.compare("FALSE")) ||
		(!upper_token.compare("F"))
	);
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IS UNSIGNED INTEGER STRING
// --------------------------------------------------------------------------
// 12345u
//====--------------------------------------------------------------------==////
bool NumericCheck::isPreUnsigned(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 2) {
		// 2 char at least
		return false;
	}
	switch (token.at(0)) {
	case 'U':
		// fall through
	case 'u':
		++pos;
		break;
	default:
		return false;
	}
	while (pos < len) {
		if (!isdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	// if no errors, it is unsigned integer
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / IS ZERO-START OCTAL STRING
// --------------------------------------------------------------------------
// 01234567
//====--------------------------------------------------------------------==////
bool NumericCheck::isZeroOctal(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 1) {
		// 1 char at least
		return false;
	}
	if ('0' != token.at(pos)) {
		return false;
	}
	++pos;
	while (pos < len) {
		const char &c = token.at(pos);
		if ((c < '0') || (c > '7')) {
			return false;
		}
		++pos;
	}
	// if no errors, it is integer
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / BINARY CHECK
// --------------------------------------------------------------------------
// 0bXXXX
//====--------------------------------------------------------------------==////
bool NumericCheck::isBinary(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 3) {
		return false;
	}
	if ('0' != token.at(pos)) {
		return false;
	}
	++pos;
	if (('B' != token.at(pos)) && ('b' != token.at(pos))) {
		return false;
	}
	++pos;
	while (pos < len) {
		if (('0' != token.at(pos)) && ('1' != token.at(pos))) {
			return false;
		}
		++pos;
	}
	// if no errors, it is binary
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / OCTAL CHECK
// --------------------------------------------------------------------------
// 0oXXXX
//====--------------------------------------------------------------------==////
bool NumericCheck::isOctal(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 3) {
		return false;
	}
	if ('0' != token.at(pos)) {
		return false;
	}
	++pos;
	if (('O' != token.at(pos)) && ('o' != token.at(pos))) {
		return false;
	}
	++pos;
	while (pos < len) {
		if (!(('0' <= token.at(pos)) && (token.at(pos) <= '7'))) {
			return false;
		}
		++pos;
	}
	// if no errors, it is octal
	return true;
}

////==--------------------------------------------------------------------====//
// NUMERIC CHECK / HEXADECIMAL CHECK
// --------------------------------------------------------------------------
// 0xXXXX
//====--------------------------------------------------------------------==////
bool NumericCheck::isHexadecimal(const std::string &token) {
	// spaces cannot be allowed
	std::size_t pos = 0;
	std::size_t len = token.length();
	if (len < 3) {
		return false;
	}
	if ('0' != token.at(pos)) {
		return false;
	}
	++pos;
	if (('X' != token.at(pos)) && ('x' != token.at(pos))) {
		return false;
	}
	++pos;
	while (pos < len) {
		if (!isxdigit(token.at(pos))) {
			return false;
		}
		++pos;
	}
	// if no errors, it is integer
	return true;
}
