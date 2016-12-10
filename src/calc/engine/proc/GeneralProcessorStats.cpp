#include "GeneralProcessor.h"
#include <cmath>

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / GAMMA FUNCTION
// [ description ]
// GAMMA FUNCTION for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::trueGamma(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  gamma(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 < int_x) {
				p_etemp = fact(dec(p_ex));
			}
			else {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  gamma(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((std::floor(flt_x) == std::ceil(flt_x)) && (flt_x < 0)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else {
				floating_t ftemp = ::tgamma(flt_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  gamma(RATIONAL)  ===//
			floating_t flt_x = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((std::floor(flt_x) == std::ceil(flt_x)) && (flt_x < 0)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else {
				floating_t ftemp = ::tgamma(flt_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / NATURAL LOGARITHM OF GAMMA FUNCTION
// [ description ]
// GAMMA FUNCTION for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::lnGamma(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  lgamma(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 < int_x) {
				floating_t ftemp = ::lgamma((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			else {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  lgamma(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((std::floor(flt_x) == std::ceil(flt_x)) && (flt_x < 0)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else {
				floating_t ftemp = ::lgamma(flt_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  lgamma(RATIONAL)  ===//
			floating_t flt_x = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((std::floor(flt_x) == std::ceil(flt_x)) && (flt_x < 0)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else {
				floating_t ftemp = ::lgamma(flt_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ERROR FUNCTION
// [ description ]
// ERROR FUNCTION for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::erf(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  erf(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 == int_x) {
				setInteger(p_etemp, 0);
			}
			else {
				floating_t ftemp = ::erf((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  erf(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = ::erf(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  erf(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = ::erf(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COMPLEMENTARY ERROR FUNCTION
// [ description ]
// COMPLEMENTARY ERROR FUNCTION for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::erfc(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  erfc(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (0 == int_x) {
				setInteger(p_etemp, 1);
			}
			else {
				floating_t ftemp = ::erfc((floating_t)int_x);
				setFloating(p_etemp, ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  erfc(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			floating_t ftemp = ::erfc(flt_x);
			setFloating(p_etemp, ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  erfc(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = ::erfc(rat_x.getFloating());
			setFloating(p_etemp, ftemp);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
