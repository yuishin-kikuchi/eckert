#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SIN (radian)
// [ description ]
// SIN function for scalar (radian)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::sinRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  sinRadian(INTEGER)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 == int_x) {
				setInteger(p_etemp, 0);
			}
			else {
				floating_t ftemp = std::sin((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  sinRadian(FLOATING)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::sin(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  sinRadian(RATIONAL)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::sin(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  sinRadian(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			// real = sin(a) * cosh(b)
			p_real = mulScalar(sinRadian(a), cosh(b));
			// imag = cos(a) * sinh(b)
			p_imag = mulScalar(cosRadian(a), sinh(b));
			setComplex(p_etemp, p_real, p_imag);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COS (radian)
// [ description ]
// COS function for scalar (radian)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::cosRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  cosRadian(INTEGER)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 == int_x) {
				setInteger(p_etemp, 1);
			}
			else {
				floating_t ftemp = std::cos((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  cosRadian(FLOATING)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::cos(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  cosRadian(RATIONAL)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::cos(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  cosRadian(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			// real = cos(a) * cosh(b)
			p_real = mulScalar(cosRadian(a), cosh(b));
			// imag = sin(a) * sinh(b)
			p_imag = mulScalar(sinRadian(a), sinh(b));
			setComplex(p_etemp, p_real, p_imag);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / TAN (radian)
// [ description ]
// TAN function for scalar (radian)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::tanRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  tanRadian(INTEGER)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 == int_x) {
				setInteger(p_etemp, 0);
			}
			else {
				floating_t ftemp = std::tan((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  tanRadian(FLOATING)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			/* value check */
			floating_t absolute = std::abs(flt_x);
			integer_t quot = (integer_t)::round(2 * absolute / PI);
			if (quot & 0x01) {
				if (std::abs(PI * quot / 2.0 - absolute) < std::numeric_limits<floating_t>::epsilon() * 10) {
					throw InvalidValue("BAD_VAL", __FUNCTION__);
				}
			}
			floating_t ftemp = std::tan(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  tanRadian(RATIONAL)  ===//
			if (!isInEpsilonInverse(p_ex)) {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			// value check
			floating_t flt_x = rat_x.getFloating();
			floating_t absolute = std::abs(flt_x);
			integer_t quot = (integer_t)::round(2 * absolute / PI);
			if (quot & 0x01) {
				if (std::abs(PI * quot / 2.0 - absolute) < std::numeric_limits<floating_t>::epsilon() * 10) {
					throw BadArgument("BAD_VAL", __FUNCTION__);
				}
			}
			floating_t ftemp = std::tan(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  tanRadian(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			auto cosr_a = cosRadian(a);
			auto sinh_b = sinh(b);
			// divisor = 2 * (cos^2(a) + sinh^2(b))
			SpElement divisor = mulScalar(
				GEN_INTEGER(2),
				add(mul(cosr_a, cosr_a), mul(sinh_b, sinh_b))
			);
			// real = sin(2a) / divisor
			p_real = div(
				sinRadian(mul(GEN_INTEGER(2), a)),
				divisor
			);
			// imag = sinh(2b) / divisor
			p_imag = div(
				sinh(mul(GEN_INTEGER(2), b)),
				divisor
			);
			setComplex(p_etemp, p_real, p_imag);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ASIN (radian)
// [ description ]
// ASIN function for scalar (radian)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::asinRadian(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  asinRadian(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 <= int_x) && (int_x <= 1)) {
				floating_t ftemp = std::asin((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  asinRadian(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 <= flt_x) && (flt_x <= 1.0)) {
				floating_t ftemp = std::asin(flt_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  asinRadian(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 <= ftemp) && (ftemp <= 1.0)) {
				ftemp = std::asin(ftemp);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::COMPLEX: {
			//===  asinRadian(COMPLEX)  ===//
			//==  acosRadian(COMPLEX)  ==//
			// asin(Z) = -i * ln(sqrt(1-Z^2) + i*Z)
			SpElement root = sqrt(sub(GEN_INTEGER(1), square(p_ex)));
			SpElement logarithm = loge(add(root, mul(POS_IMAGINARY, p_ex)));
			p_etemp = mul(NEG_IMAGINARY, logarithm);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}
catch (BadScalar &) {
	SpElement root = sqrt(sub(GEN_INTEGER(1), square(p_ex)));
	SpElement logarithm = loge(add(root, mul(POS_IMAGINARY, p_ex)));
	return mul(POS_IMAGINARY, logarithm);
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ACOS (radian)
// [ description ]
// ACOS function for scalar (radian)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::acosRadian(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  acosRadian(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 <= int_x) && (int_x <= 1)) {
				floating_t ftemp = std::acos((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  acosRadian(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 <= flt_x) && (flt_x <= 1.0)) {
				floating_t ftemp = std::acos(flt_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  acosRadian(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 <= ftemp) && (ftemp <= 1.0)) {
				ftemp = std::acos(ftemp);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::COMPLEX: {
			//===  acosRadian(COMPLEX)  ===//
			// acos(Z) = -i * ln(Z + i*sqrt(1 - Z^2))
			SpElement root = sqrt(sub(GEN_INTEGER(1), square(p_ex)));
			SpElement logarithm = loge(add(p_ex, mul(POS_IMAGINARY, root)));
			p_etemp = mul(NEG_IMAGINARY, logarithm);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}
catch (BadScalar &) {
	SpElement root = sqrt(sub(GEN_INTEGER(1), square(p_ex)));
	SpElement logarithm = loge(add(p_ex, mul(POS_IMAGINARY, root)));
	return mul(NEG_IMAGINARY, logarithm);
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ATAN (radian)
// [ description ]
// ATAN function for scalar (radian)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::atanRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  atanRadian(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 == int_x) {
				setInteger(p_etemp, 0);
			}
			else {
				floating_t ftemp = std::atan((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  atanRadian(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::atan(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  atanRadian(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::atan(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::EINFINITY: {
			//===  atanRadian(EINFINITY)  ===//
			int sign = GET_EINFINITY_DATA(p_ex);
			if (sign > 0) {
				p_etemp = GEN_FLOATING(PI / 2.0);
			}
			else if (sign < 0) {
				p_etemp = GEN_FLOATING(-PI / 2.0);
			}
			else {
				setError(p_etemp, "IND");
			}
			break;
		}
		case Element::COMPLEX: {
			//===  atanRadian(COMPLEX)  ===//
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			if (isZero(a)) {
				// Z == i or Z == -i
				switch (b->getType()) {
					case Element::INTEGER: {
						integer_t int_x = GET_INTEGER_DATA(b);
						if ((1 == int_x) || (-1 == int_x)) {
							throw InvalidValue("BAD_VAL", __FUNCTION__);
						}
						break;
					}
					case Element::FLOATING: {
						floating_t flt_x = GET_FLOATING_DATA(b);
						if ((1.0 == flt_x) || (-1.0 == flt_x)) {
							throw InvalidValue("BAD_VAL", __FUNCTION__);
						}
						break;
					}
					case Element:: RATIONAL: {
						rational_t rat_x = GET_RATIONAL_DATA(b);
						floating_t ftemp = rat_x.getFloating();
						if ((1.0 == ftemp) || (-1.0 == ftemp)) {
							throw InvalidValue("BAD_VAL", __FUNCTION__);
						}
						break;
					}
					default:
						break;
				}
			}
			// atan(Z) = i/2 * ln((i + Z) / (i - Z))
			p_etemp = loge(div(add(POS_IMAGINARY, p_ex), sub(POS_IMAGINARY, p_ex)));
			p_etemp = mul(p_etemp, div(POS_IMAGINARY, GEN_INTEGER(2)));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
