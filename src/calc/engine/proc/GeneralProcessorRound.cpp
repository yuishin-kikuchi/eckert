#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / FLOOR
// [ description ]
// FLOOR function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::floor(const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  floor(INTEGER)  ===//
			p_etemp = p_ex;
			break;
		}
		case Element::FLOATING: {
			//===  floor(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if (!util::checkRange<integer_t, floating_t>(flt_x)) {
				integer_t temp = (integer_t)std::floor(flt_x);
				setInteger(p_etemp, temp);
			}
			else {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  floor(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = rat_x.getFloating();
			if (!util::checkRange<integer_t, floating_t>(ftemp)) {
				integer_t temp = (integer_t)std::floor(ftemp);
				setInteger(p_etemp, temp);
			}
			else {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
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
// ECKERT PROCESSOR / CEILING
// [ description ]
// CEILING function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::ceil(const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  ceil(INTEGER)  ===//
			p_etemp = p_ex;
			break;
		}
		case Element::FLOATING: {
			//===  ceil(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if (!util::checkRange<integer_t, floating_t>(flt_x)) {
				integer_t temp = (integer_t)std::ceil(flt_x);
				setInteger(p_etemp, temp);
			}
			else {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  ceil(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = rat_x.getFloating();
			if (!util::checkRange<integer_t, floating_t>(ftemp)) {
				integer_t temp = (integer_t)std::ceil(ftemp);
				setInteger(p_etemp, temp);
			}
			else {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
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
// ECKERT PROCESSOR / ROUND
// [ description ]
// ROUND function for scalar
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::round(const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  round(INTEGER)  ===//
			p_etemp = p_ex;
			break;
		}
		case Element::FLOATING: {
			//===  round(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if (!util::checkRange<integer_t, floating_t>(flt_x)) {
				integer_t temp = (integer_t)::round(flt_x);
				setInteger(p_etemp, temp);
			}
			else {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  round(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			floating_t ftemp = rat_x.getFloating();
			if (!util::checkRange<integer_t, floating_t>(ftemp)) {
				integer_t temp = (integer_t)::round(ftemp);
				setInteger(p_etemp, temp);
			}
			else {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
