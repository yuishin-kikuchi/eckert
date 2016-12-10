#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / POWER
// [ description ]
// POWER function for 2 scalars
// [ Update ]
// May 02, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::pow(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	try {
		if (p_ex->isType(Element::INTEGER)) {
			p_etemp = nthPow(p_ey, p_ex);
		}
		else {
			p_etemp = powScalar(p_ey, p_ex);
		}
	}
	catch (InvalidValue &) {
		throw;
	}
	catch (BadArgument &) {
		if (p_ey->isType(Element::ERROR) || p_ex->isType(Element::ERROR)) {
			setError(p_etemp, "ERROR");
		}
		else {
			p_etemp = powComplex(p_ey, p_ex);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / EXPONENT
// [ description ]
// EXPONENT for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::exp(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  exp(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 != int_x) {
				floating_t ftemp = std::exp((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				// exp(0) = 1
				setInteger(p_etemp, 1);
			}
			break;
		}
		case Element::FLOATING: {
			//===  exp(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = std::exp(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  exp(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = std::exp(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::COMPLEX: {
			//===  exp(COMPLEX)  ===//
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			setComplex(p_etemp, cosRadian(b), sinRadian(b));
			p_etemp = mul(p_etemp, exp(a));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / TEN TO THER POWER
// [ description ]
// TEN TO THER POWER for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::pow10(const SpElement &p_ex) {
	return pow(GEN_INTEGER(10), p_ex);
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / BINARY POWER
// [ description ]
// BINARY POWER for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::pow2(const SpElement &p_ex) {
	return pow(GEN_INTEGER(2), p_ex);
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / NATURAL LOGARITHM
// [ description ]
// NATURAL LOGARITHM for scalar
// [ Update ]
// Nov 10, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::loge(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (isZero(p_ex)) {
		throw InvalidValue("BAD_VAL", __FUNCTION__);
	}
	else if (isNegative(p_ex)) {
		throw BadScalar("CPX_OFF", __FUNCTION__);
	}
	else {
		switch (p_ex->getType()) {
			case Element::INTEGER: {
				//===  loge(INTEGER)  ===//
				integer_t int_x = GET_INTEGER_DATA(p_ex);
				if (1 == int_x) {
					setInteger(p_etemp, 0);
				}
				else {
					floating_t dtemp = std::log((floating_t)int_x);
					setFloating(p_etemp, dtemp);
				}
				break;
			}
			case Element::FLOATING: {
				//===  loge(FLOATING)  ===//
				floating_t flt_x = GET_FLOATING_DATA(p_ex);
				floating_t dtemp = std::log(flt_x);
				setFloating(p_etemp, dtemp);
				break;
			}
			case Element::RATIONAL: {
				//===  loge(RATIONAL)  ===//
				rational_t rat_x = GET_RATIONAL_DATA(p_ex);
				floating_t dtemp = std::log(rat_x.getFloating());
				setFloating(p_etemp, dtemp);
				break;
			}
			case Element::COMPLEX: {
				//===  loge(COMPLEX)  ===//
				SpElement p_real;
				SpElement p_imag;
				// real = ln(abs(a + ib))
				p_real = loge(abs(p_ex));
				// imag = arg(a + ib)
				p_imag = argRadian(p_ex);
				setComplex(p_etemp, p_real, p_imag);
				break;
			}
			default:
				//===  Unexpected  ===//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
	}
	return p_etemp;
}
catch (BadScalar &) {
	SpElement p_etemp;
	SpElement p_real = loge(abs(p_ex));
	SpElement p_imag = argRadian(p_ex);
	setComplex(p_etemp, p_real, p_imag);
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COMMON LOGARITHM
// [ description ]
// COMMON LOGARITHM for scalar
// [ Update ]
// Nov 10, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::log10(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (isZero(p_ex)) {
		throw InvalidValue("BAD_VAL", __FUNCTION__);
	}
	else if (isNegative(p_ex)) {
		throw BadScalar("CPX_OFF", __FUNCTION__);
	}
	else {
		switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  log10(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (1 == int_x) {
				setInteger(p_etemp, 0);
			}
			else {
				floating_t dtemp = ::log10((floating_t)int_x);
				setFloating(p_etemp, dtemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  log10(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t dtemp = ::log10(flt_x);
			setFloating(p_etemp, dtemp);
			break;
		}
		case Element::RATIONAL: {
			//===  log10(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t dtemp = ::log10(rat_x.getFloating());
			setFloating(p_etemp, dtemp);
			break;
		}
		case Element::COMPLEX: {
			//===  log10(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			// real = ln(abs(a + ib))
			p_real = loge(abs(p_ex));
			// imag = arg(a + ib)
			p_imag = argRadian(p_ex);
			setComplex(p_etemp, p_real, p_imag);
			p_etemp =  div(p_etemp, GEN_FLOATING(::log(10.0L)));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
	}
	return p_etemp;
}
catch (BadScalar &) {
	SpElement p_etemp;
	SpElement p_real = loge(abs(p_ex));
	SpElement p_imag = argRadian(p_ex);
	setComplex(p_etemp, p_real, p_imag);
	return div(p_etemp, GEN_FLOATING(::log(10.0L)));
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / BINARY LOGARITHM
// [ description ]
// BINARY LOGARITHM for scalar
// [ Update ]
// Nov 10, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::log2(const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (isZero(p_ex)) {
		throw InvalidValue("BAD_VAL", __FUNCTION__);
	}
	else if (isNegative(p_ex)) {
		throw BadScalar("CPX_OFF", __FUNCTION__);
	}
	else {
		switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  log2(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (1 == int_x) {
				setInteger(p_etemp, 0);
			}
			else {
				floating_t dtemp = ::log2((floating_t)int_x);
				setFloating(p_etemp, dtemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  log2(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t dtemp = ::log2(flt_x);
			setFloating(p_etemp, dtemp);
			break;
		}
		case Element::RATIONAL: {
			//===  log2(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t dtemp = ::log2(rat_x.getFloating());
			setFloating(p_etemp, dtemp);
			break;
		}
		case Element::COMPLEX: {
			//===  log2(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			// real = ln(abs(a + ib))
			p_real = loge(abs(p_ex));
			// imag = arg(a + ib)
			p_imag = argRadian(p_ex);
			setComplex(p_etemp, p_real, p_imag);
			p_etemp =  div(p_etemp, GEN_FLOATING(::log(2.0L)));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
	}
	return p_etemp;
}
catch (BadScalar &) {
	SpElement p_etemp;
	SpElement p_real = loge(abs(p_ex));
	SpElement p_imag = argRadian(p_ex);
	setComplex(p_etemp, p_real, p_imag);
	return div(p_etemp, GEN_FLOATING(::log(2.0L)));
}

} // namespace engine
