#include "GeneralProcessor.h"
#include <limits>
#include <cmath>

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / STATIC MEMBERS
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
const int GeneralProcessor::ZERO = 0;
const int GeneralProcessor::POSITIVE = 1;
const int GeneralProcessor::NEGATIVE = -1;
const floating_t GeneralProcessor::PI = 3.14159265358979323846L;
const floating_t GeneralProcessor::NAPIER = 2.71828182845904523536L;
const floating_t GeneralProcessor::EGAMMA = 0.57721566490153286061L;

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / ERROR SETTER
// [ description ]
// Set error to SpElement
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setError(SpElement &rp_set, const char *str) {
	setFlags(ERROR_FLAG);
	rp_set = GEN_ERROR(str);
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / INTEGER SETTER
// [ description ]
// Set integer to SpElement
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setInteger(SpElement &rp_set, const integer_t &num) {
	rp_set = GEN_INTEGER(num);
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / FLOATING SETTER
// [ description ]
// Set floating to SpElement
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setFloating(SpElement &rp_set, const floating_t &num) {
	// check overflow
	if (std::isinf(num)) {
		setFlags(FLT_OVERFLOW);
		if (num > 0.0) {
			rp_set = GEN_EINFINITY(POSITIVE);
		}
		else {
			rp_set = GEN_EINFINITY(NEGATIVE);
		}
	}
	// check error
	else if (std::isnan(num)) {
		setError(rp_set, "NAN");
	}
	else {
		rp_set = GEN_FLOATING(num);
	}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / RATIONAL SETTER (rational_t)
// [ description ]
// Set rational to SpElement with rational_t
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setRational(SpElement &rp_set, const rational_t &num) {
	switch (num.getDen()) {
		case 0:
			setError(rp_set, "NAN");
			break;
		case 1:
			rp_set = GEN_INTEGER(num.getNum());
			break;
		default:
			rp_set = GEN_RATIONAL(num);
			break;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / RATIONAL SETTER (2 integer_t)
// [ description ]
// Set rational to SpElement with 2 integer_t
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setRational(SpElement &rp_set, const integer_t &numer, const integer_t &denom) {
	using util = SafetyIntegerCalculator;
	integer_t num = numer;
	integer_t den = denom;
	if (denom < 0) {
		if (!util::checkNeg(num) && !util::checkNeg(den)) {
			num = -num;
			den = -den;
		}
		else {
			rp_set = GEN_FLOATING((floating_t)num / (floating_t)den);
			return;
		}
	}
	switch (denom) {
	case 0:
		setError(rp_set, "NAN");
		break;
	case 1:
		rp_set = GEN_INTEGER(num);
		break;
	default:
		rp_set = GEN_RATIONAL2(num, den);
		break;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / INFINITY SETTER
// [ description ]
// Set infinity to SpElement
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setInfinity(SpElement &rp_set, const int &sign) {
	rp_set = GEN_EINFINITY(sign);
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / COMPLEX SETTER
// [ description ]
// Set complex to SpElement
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
void GeneralProcessor::setComplex(SpElement &rp_set, const SpElement &p_real, const SpElement &p_imag) {
	if ((nullptr == p_real) || (nullptr == p_imag)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// check error
	if (p_real->isType(Element::ERROR) || p_imag->isType(Element::ERROR)) {
		rp_set = GEN_ERROR("NAN");
	}
	// check infinity
	else if (p_real->isType(Element::EINFINITY) || p_imag->isType(Element::EINFINITY)) {
		rp_set = GEN_EINFINITY(ZERO);
	}
	// check real
	else if (p_imag->isType(Element::INTEGER)) {
		if (0 == GET_INTEGER_DATA(p_imag)) {
			rp_set = p_real;
		}
		else {
			rp_set = GEN_COMPLEX(p_real, p_imag);
		}
	}
	else {
		rp_set = GEN_COMPLEX(p_real, p_imag);
	}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / IS IN INVERTED EPSILON
// [ description ]
// Judge if the absolute value of the SpElement is in inverted epsilon
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
bool GeneralProcessor::isInEpsilonInverse(const SpElement &p_ex)
try {
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	auto temp = this->abs(p_ex);
	switch (temp->getType()) {
		case Element::INTEGER:
			return ((floating_t)GET_INTEGER_DATA(temp) < 1.0 / std::numeric_limits<floating_t>::epsilon());
		case Element::FLOATING:
			return (GET_FLOATING_DATA(temp) < 1.0 / std::numeric_limits<floating_t>::epsilon());
		case Element::RATIONAL:
			return (GET_RATIONAL_DATA(temp).getFloating() < 1.0 / std::numeric_limits<floating_t>::epsilon());
		default:
			return false;
	}
}
catch (BadArgument &) {
	return false;
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / IS ZERO
// [ description ]
// Judge if the SpElement is zero
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
bool GeneralProcessor::isZero(const SpElement &p_ex) {
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	switch (p_ex->getType()) {
		case Element::INTEGER:
			return (0 == GET_INTEGER_DATA(p_ex));
		case Element::FLOATING:
			return (0.0 == GET_FLOATING_DATA(p_ex));
		case Element::RATIONAL:
			return (0 == GET_RATIONAL_DATA(p_ex).getNum());
		case Element::BINARY8:
			return (0 == GET_BYTE_DATA(p_ex));
		case Element::BINARY16:
			return (0 == GET_WORD_DATA(p_ex));
		case Element::BINARY32:
			return (0 == GET_DWORD_DATA(p_ex));
		case Element::BINARY64:
			return (0 == GET_QWORD_DATA(p_ex));
		case Element::COMPLEX: {
			const auto &a = GET_COMPLEX_RE(p_ex);
			const auto &b = GET_COMPLEX_IM(p_ex);
			return (isZero(a) && isZero(b));
		}
		default:
			return false;
		}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / IS POSITIVE
// [ description ]
// Judge if the SpElement is positive
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
bool GeneralProcessor::isPositive(const SpElement &p_ex) {
	if (nullptr == p_ex) {
		TechnicalError("NULLPTR", __FUNCTION__);
	}
	switch (p_ex->getType()) {
		case Element::INTEGER:
			return (0 < GET_INTEGER_DATA(p_ex));
		case Element::FLOATING: {
			auto flt = GET_FLOATING_DATA(p_ex);
			if (0.0 == flt) {
				if (1.0 / flt > 0.0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return (0.0 < flt);
			}
		}
		case Element::RATIONAL:
			return (0 < GET_RATIONAL_DATA(p_ex).getNum());
		case Element::EINFINITY:
			return (0 < GET_EINFINITY_DATA(p_ex));
		default:
			return false;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / IS NEGATIVE
// [ description ]
// Judge if the SpElement is negative
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
bool GeneralProcessor::isNegative(const SpElement &p_ex) {
	if (nullptr == p_ex) {
		TechnicalError("NULLPTR", __FUNCTION__);
	}
	switch (p_ex->getType()) {
		case Element::INTEGER:
			return (0 > GET_INTEGER_DATA(p_ex));
		case Element::FLOATING: {
			auto flt = GET_FLOATING_DATA(p_ex);
			if (0.0 == flt) {
				if (1.0 / flt < 0.0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return (flt < 0.0);
			}
		}
		case Element::RATIONAL:
			return (0 > GET_RATIONAL_DATA(p_ex).getNum());
		case Element::EINFINITY:
			return (0 > GET_EINFINITY_DATA(p_ex));
		default:
			return false;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / MAKE PI
// [ Update ]
// Nov 20, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::pi() {
	return GEN_FLOATING(PI);
}

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR / MAKE PI/2
// [ Update ]
// Nov 20, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::pi_2() {
	return GEN_FLOATING(PI / 2.0L);
}

} // namespace engine
