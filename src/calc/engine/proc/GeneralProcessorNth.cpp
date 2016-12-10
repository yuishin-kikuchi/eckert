#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SQUARE
// [ description ]
// calculate SQUARE
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::square(const SpElement &p_ex) {
	return this->mul(p_ex, p_ex);
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / N-th POWER
// [ description ]
// N-th POWER
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::nthPow(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::INTEGER)) {
		bool is_minus = false;
		bool is_minimum = false;
		integer_t exponent = GET_INTEGER_DATA(p_ex);
		if ((exponent < 1) && p_ey->isType(Element::MATRIX)) {
			// MATRIX ^ 0 is UNDEFINED
			throw InvalidValue("BAD_VAL", __FUNCTION__);
		}
		if (0 == exponent) {
			if (isZero(p_ey)) {
				// 0 ^ 0 is UNDEFINED
				throw InvalidValue("ZPOWZ", __FUNCTION__);
			}
		}
		else if (exponent < 0) {
			is_minus = true;
			if (isZero(p_ey)) {
				// 0 ^ NEG is UNDEFINED
				throw InvalidValue("ZPOWN", __FUNCTION__);
			}
			if (util::checkNeg(exponent)) {
				// If the exponent is minimum integer, it cannot be inverted its sign
				// when the machine supports negative integer with two's complement.
				// Thus, increment it in order to make it non-minimum.
				is_minimum = true;
				++exponent;
			}
			exponent = -exponent;
		}
		const auto &base = p_ey;
		auto multipler = p_ey;
		p_etemp = GEN_INTEGER(1);
		while (exponent) {
			// Use binary exponent algorithm to decrease the calculation amount.
			// O(N) -> O(log(N))
			if (exponent & 1u) {
				p_etemp = this->mul(p_etemp, multipler);
			}
			if (exponent >> 1) {
				multipler = this->mul(multipler, multipler);
			}
			exponent >>= 1;
		}
		if (is_minus) {
			if (is_minimum) {
				// If the exponent is minimum integer, multiply once more
				p_etemp = this->mul(p_etemp, base);
			}
			p_etemp = this->inv(p_etemp);
		}
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / N-th ROOT
// [ description ]
// N-th ROOT
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::nthRoot(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::INTEGER)) {
		auto degree = GET_INTEGER_DATA(p_ex);
		bool is_minus = false;
		bool is_minimum = false;
		if (0 == degree) {
			// 0th root
			throw BadArgument("DIV_ZERO", __FUNCTION__);
		}
		if (degree < 0) {
			is_minus = true;
			if (util::checkNeg(degree)) {
				is_minimum = true;
			}
			else {
				degree = -degree;
			}
		}
		if (isZero(p_ey)) {
			//===  nth_root(ZERO)  ===//
			if (is_minus) {
				// 0 ^ NEG is UNDEFINED
				throw InvalidValue("ZPOWN", __FUNCTION__);
			}
			else {
				return p_ey->clone();
			}
		}
		if (isNegative(p_ey)) {
			//===  nth_root(negative scalar)  ===//
			return powComplex(GEN_COMPLEX(p_ey, GEN_INTEGER(0)), inv(p_ex));
		}
		else {
			p_etemp = GEN_INTEGER(1);
			SpElement multipler = p_ey;
			integer_t degree = GET_INTEGER_DATA(p_ex);
			// nth_root(Real)
			switch (p_ey->getType()) {
				case Element::INTEGER: {
					//===  nth_root(INTEGER)  ===//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					floating_t ftemp = 0.0;
					if (is_minimum) {
						ftemp = std::pow(int_y, 1.0 / degree);
						setFloating(p_etemp, ftemp);
					}
					else {
						floating_t approx
						 = std::pow((floating_t)int_y, 1.0 / (floating_t)degree);
						integer_t valcheck = 1;
						integer_t iapprox = (integer_t)::round(approx);
						integer_t imultipler = iapprox;
						while (degree) {
							if (degree & 1u) {
								valcheck *= imultipler;
							}
							imultipler *= imultipler;
							degree >>= 1;
						}
						if (valcheck == int_y) {
							setInteger(p_etemp, iapprox);
						}
						else {
							setFloating(p_etemp, approx);
						}
						if (is_minus) {
							p_etemp = inv(p_etemp);
						}
					}
					break;
				}
				case Element::FLOATING: {
					//===  nth_root(FLOATING)  ===//
					floating_t flt_y = GET_FLOATING_DATA(p_ey);
					floating_t ftemp = std::pow(flt_y, 1.0 / (floating_t)degree);
					setFloating(p_etemp, ftemp);
					if (!is_minimum && is_minus) {
						p_etemp = inv(p_etemp);
					}
					break;
				}
				case Element::RATIONAL: {
					//===  nth_root(RATIONAL)  ===//
					rational_t rat_y = GET_RATIONAL_DATA(p_ey);
					if (is_minimum) {
						floating_t ftemp
						 = std::pow(rat_y.getFloating(), 1.0 / (floating_t)degree);
						setFloating(p_etemp, ftemp);
					}
					else {
						SpElement numer;
						SpElement denom;
						setInteger(numer, rat_y.getNum());
						setInteger(denom, rat_y.getDen());
						p_etemp = div(nthRoot(numer, p_ex), nthRoot(denom, p_ex));
						if (!is_minimum && is_minus) {
							p_etemp = inv(p_etemp);
						}
					}
					break;
				}
				case Element::COMPLEX: {
					//===  nth_root(COMPLEX)  ===//
					auto argument = div(argRadian(p_ey), p_ex);
					auto magnitude = nthRoot(abs(p_ey), p_ex);
					auto p_real = mul(magnitude, cosRadian(argument));
					auto p_imag = mul(magnitude, sinRadian(argument));
					setComplex(p_etemp, p_real, p_imag);
					break;
				}
				default:
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
