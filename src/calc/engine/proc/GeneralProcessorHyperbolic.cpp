#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SINH
// [ description ]
// SINH function for scalar
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::sinh(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  sinh(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			floating_t ftemp = std::sinh((floating_t)int_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::FLOATING: {
			//===  sinh(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::sinh(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  sinh(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::sinh(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  sinh(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			// real = sinh(a) * cos(b)
			p_real = mulScalar(sinh(a), cosRadian(b));
			// imag = cosh(a) * sin(b)
			p_imag = mulScalar(cosh(a), sinRadian(b));
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
// ECKERT PROCESSOR / COSH
// [ description ]
// COSH function for scalar
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::cosh(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  cosh(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			floating_t ftemp = std::cosh((floating_t)int_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::FLOATING: {
			//===  cosh(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::cosh(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  cosh(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::cosh(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  cosh(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			// real = cosh(a) * cos(b)
			p_real = mulScalar(cosh(a), cosRadian(b));
			// imag = sinh(a) * sin(b)
			p_imag = mulScalar(sinh(a), sinRadian(b));
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
// ECKERT PROCESSOR / TANH
// [ description ]
// TANH function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::tanh(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  tanh(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			floating_t ftemp = std::tanh((floating_t)int_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::FLOATING: {
			//===  tanh(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::tanh(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  tanh(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::tanh(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  tanh(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			// divisor = cosh(2a) + cos(2b)
			SpElement divisor
			 = add(cosh(mulScalar(GEN_INTEGER(2), a)),
			       cosRadian(mulScalar(GEN_INTEGER(2), b)));
			// real = sinh(2a) / divisor
			p_real = divScalar(
				GeneralProcessor::sinh(mulScalar(GEN_INTEGER(2), a)), divisor
			);
			// imag = sin(2b) / divisor
			p_imag = divScalar(
				GeneralProcessor::sinRadian(mulScalar(GEN_INTEGER(2), b)), divisor
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
// ECKERT PROCESSOR / ASINH
// [ description ]
// ASINH function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::asinh(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  asinh(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			floating_t ftemp = ::asinh((floating_t)int_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::FLOATING: {
			//===  asinh(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = ::asinh(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  asinh(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = ::asinh(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  asinh(COMPLEX)  ===//
			// asinh(Z) = ln(Z + sqrt(Z^2 + 1))
			p_etemp = loge(add(p_ex, sqrt(add(mul(p_ex, p_ex), GEN_INTEGER(1)))));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ACOSH
// [ description ]
// ACOSH function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::acosh(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  acosh(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (1 <= int_x) {
				floating_t ftemp = ::acosh((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  acosh(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if (1.0 <= flt_x) {
				floating_t ftemp = ::acosh(flt_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  acosh(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = rat_x.getFloating();
			if (1.0 <= ftemp) {
				ftemp = ::acosh(ftemp);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::COMPLEX: {
			//===  acosh(COMPLEX)  ===//
			// acosh(Z) = ln(Z + sqrt(Z + 1) * sqrt(Z - 1))
			p_etemp
			 = loge(add(p_ex,
			        mul(sqrt(add(p_ex, GEN_INTEGER(1))),
			            sqrt(sub(p_ex, GEN_INTEGER(1)))))
			);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}
catch (BadScalar &) {
	return (
		loge(add(p_ex,
			mul(sqrt(add(p_ex, GEN_INTEGER(1))),
			sqrt(sub(p_ex, GEN_INTEGER(1)))))
		)
	);
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ATANH
// [ description ]
// ATANH function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::atanh(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  atanh(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 < int_x) && (int_x < 1)) {
				floating_t ftemp = ::atanh((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			else if ((1 == int_x) || (-1 == int_x)) {
				throw InvalidValue("BAD_VAL", __FUNCTION__);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  atanh(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 < flt_x) && (flt_x < 1.0)) {
				floating_t ftemp = ::atanh(flt_x);
				setFloating(p_etemp, ftemp);
			}
			else if ((1.0 == flt_x) || (-1.0 == flt_x)) {
				throw InvalidValue("BAD_VAL", __FUNCTION__);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  atanh(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 < ftemp) && (ftemp < 1.0)) {
				ftemp = ::atanh(ftemp);
				setFloating(p_etemp, ftemp);
			}
			else if ((1.0 == ftemp) || (-1.0 == ftemp)) {
				throw InvalidValue("BAD_VAL", __FUNCTION__);
			}
			else {
				throw BadScalar("CPX_OFF", __FUNCTION__);
			}
			break;
		}
		case Element::COMPLEX: {
			//===  atanh(COMPLEX)  ===//
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			if (isZero(b)) {
				// Z != 1 || Z != -1
				switch (a->getType()) {
				case Element::INTEGER: {
					integer_t int_x = GET_INTEGER_DATA(a);
					if ((1 == int_x) || (-1 == int_x)) {
						throw InvalidValue("BAD_VAL", __FUNCTION__);
					}
					break;
				}
				case Element::FLOATING: {
					floating_t flt_x = GET_FLOATING_DATA(a);
					if ((1.0 == flt_x) || (-1.0 == flt_x)) {
						throw InvalidValue("BAD_VAL", __FUNCTION__);
					}
					break;
				}
				case Element:: RATIONAL: {
					floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
					if ((1.0 == ftemp) || (-1.0 == ftemp)) {
						throw InvalidValue("BAD_VAL", __FUNCTION__);
					}
					break;
				}
				default:
					break;
				}
			}
			// atanh(Z) = ln((1 + Z) / (1 - Z)) / 2
			SpElement logarithm
			 = loge(div(add(GEN_INTEGER(1), p_ex), sub(GEN_INTEGER(1), p_ex)));
			p_etemp = div(logarithm, GEN_INTEGER(2));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}
catch (BadScalar &) {
	SpElement logarithm
	 = loge(div(add(GEN_INTEGER(1), p_ex), sub(GEN_INTEGER(1), p_ex)));
	return div(logarithm, GEN_INTEGER(2));
}

} // namespace engine
