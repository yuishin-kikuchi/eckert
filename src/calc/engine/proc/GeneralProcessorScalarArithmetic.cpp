#include "GeneralProcessor.h"
#include "base/math/floatToRational.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ADD
// [ description ]
// ADD function for 2 scalars
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::addScalar(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::INTEGER:
			//===  INTEGER + ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  INTEGER + INTEGER  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					try {
						auto temp = util::add(int_y, int_x);
						setInteger(p_etemp, temp);
					}
					catch (...) {
						floating_t ftemp
						 = (floating_t)int_y + (floating_t)int_x;
						setFlags(GeneralProcessor::INT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::FLOATING: {
					//==  INTEGER + FLOATING  ==//
					integer_t flt_y = GET_INTEGER_DATA(p_ey);
					floating_t int_x = GET_FLOATING_DATA(p_ex);
					floating_t ftemp = flt_y + (floating_t)int_x;
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  INTEGER + RATIONAL  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					rational_t rtemp_x = GET_RATIONAL_DATA(p_ex);
					try {
						rational_t rtemp_ans = int_y + rtemp_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						floating_t ftemp
						 = (floating_t)int_y + rtemp_x.getFloating();
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  INTEGER + EINFINITY  ==//
					return addInfinity(p_ey, p_ex);
				}
				default:
					//==  INTEGER + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::FLOATING:
			//===  FLOATING + ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  FLOATING + INTEGER  ==//
					floating_t ftemp = GET_FLOATING_DATA(p_ey) + GET_INTEGER_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::FLOATING: {
					//==  FLOATING + FLOATING  ==//
					floating_t ftemp = GET_FLOATING_DATA(p_ey) + GET_FLOATING_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  FLOATING + RATIONAL  ==//
					rational_t rat_x = GET_RATIONAL_DATA(p_ex);
					floating_t ftemp
					 = GET_FLOATING_DATA(p_ey) + rat_x.getFloating();
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::EINFINITY: {
					//==  FLOATING + EINFINITY  ==//
					return addInfinity(p_ey, p_ex);
				}
				default:
					//==  FLOATING + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::RATIONAL:
			//===  RATIONAL + ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  RATIONAL + INTEGER ==//
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					rational_t rtemp_y = GET_RATIONAL_DATA(p_ey);
					try {
						rational_t rtemp_ans = rtemp_y + int_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						floating_t ftemp
						 = rtemp_y.getFloating() + (floating_t)int_x;
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::FLOATING: {
					//==  RATIONAL + FLOATING ==//
					floating_t ftemp
					 = GET_RATIONAL_DATA(p_ey).getFloating() + GET_FLOATING_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  RATIONAL + RATIONAL ==//
					rational_t rtemp_y = GET_RATIONAL_DATA(p_ey);
					rational_t rtemp_x = GET_RATIONAL_DATA(p_ex);
					try {
						rational_t rtemp_ans = rtemp_y + rtemp_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						floating_t ftemp
						 = rtemp_y.getFloating() + rtemp_x.getFloating();
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  RATIONAL + EINFINITY  ==//
					return addInfinity(p_ey, p_ex);
				}
				default:
					//==  RATIONAL + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::EINFINITY: {
			//==  EINFINITY + ANY  ==//
			return addInfinity(p_ey, p_ex);
		}
		default:
			//===  Unexpected + ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SUBTRACT
// [ description ]
// SUBTRACT function for 2 scalars
// [ Update ]
// May 04, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::subScalar(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::INTEGER:
			//===  INTEGER - ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  INTEGER - INTEGER  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					try {
						auto temp = util::sub(int_y, int_x);
						setInteger(p_etemp, temp);
					}
					catch (...) {
						floating_t ftemp
						 = (floating_t)int_y - (floating_t)int_x;
						setFlags(GeneralProcessor::INT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::FLOATING: {
					//==  INTEGER - FLOATING  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					floating_t flt_x = GET_FLOATING_DATA(p_ex);
					floating_t ftemp = (floating_t)int_y - flt_x;
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  INTEGER - RATIONAL  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					rational_t rtemp_x = GET_RATIONAL_DATA(p_ex);
					try {
						rational_t rtemp_ans = int_y - rtemp_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						floating_t ftemp
						 = (floating_t)int_y - rtemp_x.getFloating();
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  INTEGER - EINFINITY  ==//
					return subInfinity(p_ey, p_ex);
				}
				default:
					//==  INTEGER - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::FLOATING:
			//===  FLOATING - ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  FLOATING - INTEGER  ==//
					floating_t flt_y = GET_FLOATING_DATA(p_ey);
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					floating_t ftemp = flt_y - (floating_t)int_x;
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::FLOATING: {
					//==  FLOATING - FLOATING  ==//
					floating_t ftemp = GET_FLOATING_DATA(p_ey) - GET_FLOATING_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  FLOATING - RATIONAL  ==//
					rational_t rat_x = GET_RATIONAL_DATA(p_ex);
					floating_t ftemp
					 = GET_FLOATING_DATA(p_ey) - rat_x.getFloating();
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::EINFINITY: {
					//==  FLOATING - EINFINITY  ==//
					return subInfinity(p_ey, p_ex);
				}
				default:
					//==  FLOATING - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::RATIONAL:
			//===  RATIONAL - ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  RATIONAL - INTEGER ==//
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					rational_t rtemp_y = GET_RATIONAL_DATA(p_ey);
					try {
						rational_t rtemp_ans = rtemp_y - int_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						floating_t ftemp
						 = rtemp_y.getFloating() - (floating_t)int_x;
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::FLOATING: {
					//==  RATIONAL - FLOATING ==//
					floating_t ftemp
					 = GET_RATIONAL_DATA(p_ey).getFloating() - GET_FLOATING_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  RATIONAL - RATIONAL ==//
					rational_t rtemp_y = GET_RATIONAL_DATA(p_ey);
					rational_t rtemp_x = GET_RATIONAL_DATA(p_ex);
					try {
						rational_t rtemp_ans = rtemp_y - rtemp_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						floating_t ftemp
						 = rtemp_y.getFloating() - rtemp_x.getFloating();
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  RATIONAL - EINFINITY  ==//
					return subInfinity(p_ey, p_ex);
				}
				default:
					//==  RATIONAL - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::EINFINITY: {
			//==  EINFINITY - ANY  ==//
			return subInfinity(p_ey, p_ex);
		}
		default:
			//===  Unexpected - ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MULTIPLY
// [ description ]
// MULTIPLY function for 2 scalars
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mulScalar(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
	case Element::INTEGER:
		//===  INTEGER * ???  ===//
		switch (x_type) {
			case Element::INTEGER: {
				//==  INTEGER * INTEGER  ==//
				integer_t int_y = GET_INTEGER_DATA(p_ey);
				integer_t int_x = GET_INTEGER_DATA(p_ex);
				try {
					auto temp = util::mul(int_y, int_x);
					setInteger(p_etemp, temp);
				}
				catch (...) {
					floating_t ftemp
					 = (floating_t)int_y * (floating_t)int_x;
					setFlags(GeneralProcessor::INT_OVERFLOW);
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			case Element::FLOATING: {
				//==  INTEGER * FLOATING  ==//
				integer_t int_y = GET_INTEGER_DATA(p_ey);
				floating_t flt_x = GET_FLOATING_DATA(p_ex);
				if (0 == int_y) {
					setInteger(p_etemp, 0);
				}
				else {
					floating_t ftemp = (floating_t)int_y * flt_x;
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			case Element::RATIONAL: {
				//==  INTEGER * RATIONAL  ==//
				integer_t int_y = GET_INTEGER_DATA(p_ey);
				rational_t rat_x = GET_RATIONAL_DATA(p_ex);
				try {
					rational_t rtemp_ans = int_y * rat_x;
					setRational(p_etemp, rtemp_ans);
				}
				catch (...) {
					floating_t ftemp = int_y * rat_x.getFloating();
					setFlags(GeneralProcessor::RAT_OVERFLOW);
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			case Element::EINFINITY: {
				//==  INTEGER * EINFINITY  ==//
				return mulInfinity(p_ey, p_ex);
			}
			default:
				//==  INTEGER * Unexpected  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
		break;
	case Element::FLOATING:
		//===  FLOATING * ???  ===//
		switch (x_type) {
			case Element::INTEGER: {
				//==  FLOATING * INTEGER  ==//
				floating_t flt_y = GET_FLOATING_DATA(p_ey);
				integer_t int_x = GET_INTEGER_DATA(p_ex);
				if (0 == int_x) {
					setInteger(p_etemp, 0);
				}
				else {
					floating_t ftemp = flt_y * (floating_t)int_x;
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			case Element::FLOATING: {
				//==  FLOATING * FLOATING  ==//
				floating_t ftemp = GET_FLOATING_DATA(p_ey) * GET_FLOATING_DATA(p_ex);
				setFloating(p_etemp, ftemp);
				break;
			}
			case Element::RATIONAL: {
				//==  FLOATING * RATIONAL  ==//
				floating_t ftemp = GET_FLOATING_DATA(p_ey) * GET_RATIONAL_DATA(p_ex).getFloating();
				setFloating(p_etemp, ftemp);
				break;
			}
			case Element::EINFINITY: {
				//==  FLOATING * EINFINITY  ==//
				return mulInfinity(p_ey, p_ex);
			}
			default:
				//==  FLOATING * Unexpected  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
		break;
	case Element::RATIONAL:
		//===  RATIONAL * ???  ===//
		switch (x_type) {
			case Element::INTEGER: {
				//==  RATIONAL * INTEGER ==//
				rational_t rat_y = GET_RATIONAL_DATA(p_ey);
				integer_t int_x = GET_INTEGER_DATA(p_ex);
				try {
					rational_t rtemp = rat_y * int_x;
					setRational(p_etemp, rtemp);
				}
				catch (...) {
					floating_t ftemp = rat_y.getFloating() * (floating_t)int_x;
					setFlags(GeneralProcessor::RAT_OVERFLOW);
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			case Element::FLOATING: {
				//==  RATIONAL * FLOATING ==//
				floating_t ftemp = GET_RATIONAL_DATA(p_ey).getFloating() * GET_FLOATING_DATA(p_ex);
				setFloating(p_etemp, ftemp);
				break;
			}
			case Element::RATIONAL: {
				//==  RATIONAL * RATIONAL ==//
				rational_t rat_y = GET_RATIONAL_DATA(p_ey);
				rational_t rat_x = GET_RATIONAL_DATA(p_ex);
				try {
					rational_t rtemp = rat_y * rat_x;
					setRational(p_etemp, rtemp);
				}
				catch (...) {
					floating_t ftemp = rat_y.getFloating() * rat_x.getFloating();
					setFlags(GeneralProcessor::RAT_OVERFLOW);
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			case Element::EINFINITY: {
				//==  RATIONAL * EINFINITY  ==//
				return mulInfinity(p_ey, p_ex);
			}
			default:
				//==  RATIONAL * Unexpected  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::EINFINITY: {
			//==  EINFINITY * ANY  ==//
			return mulInfinity(p_ey, p_ex);
		}
		default:
			//===  Unexpected * ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DIVIDE
// [ description ]
// DIVIDE function for 2 scalars
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::divScalar(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// check division by zero
	if (isZero(p_ex)) {
		throw InvalidValue("DIV_ZERO", __FUNCTION__);
	}
	else if (isZero(p_ey)) {
		return p_ey;
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
	case Element::INTEGER:
		//===  INTEGER / ???  ===//
		switch (x_type) {
			case Element::INTEGER: {
				//==  INTEGER / INTEGER  ==//
				integer_t int_y = GET_INTEGER_DATA(p_ey);
				integer_t int_x = GET_INTEGER_DATA(p_ex);
				if (!util::checkDiv(int_y, int_x)) {
					if (0 != int_y % int_x) {
						setRational(p_etemp, int_y, int_x);
					}
					else {
						integer_t temp = int_y / int_x;
						setInteger(p_etemp, temp);
					}
				}
				else {
					floating_t flt_y = (floating_t)int_y;
					floating_t flt_x = (floating_t)int_x;
					setFlags(GeneralProcessor::INT_OVERFLOW);
					setFloating(p_etemp, flt_y / flt_x);
				}
				break;
			}
			case Element::FLOATING: {
				//==  INTEGER / FLOATING  ==//
				integer_t int_y = GET_INTEGER_DATA(p_ey);
				floating_t flt_x = GET_FLOATING_DATA(p_ex);
				floating_t ftemp = (floating_t)int_y / flt_x;
				setFloating(p_etemp, ftemp);
				break;
			}
			case Element::RATIONAL: {
				//==  INTEGER / RATIONAL  ==//
				integer_t int_y = GET_INTEGER_DATA(p_ey);
				rational_t rat_x = GET_RATIONAL_DATA(p_ex);
				try {
					rational_t rtemp_ans = int_y / rat_x;
					setRational(p_etemp, rtemp_ans);
				}
				catch (...) {
					// if error, calculate as floating
					setFlags(GeneralProcessor::RAT_OVERFLOW);
					floating_t ftemp = int_y / rat_x.getFloating();
					setFloating(p_etemp, ftemp);	
				}
				break;
			}
			case Element::EINFINITY: {
				//==  INTEGER / EINFINITY  ==//
				return divInfinity(p_ey, p_ex);
			}
			default:
				//==  INTEGER / Unexpected  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::FLOATING:
			//===  FLOATING / ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  FLOATING / INTEGER  ==//
					floating_t ftemp = GET_FLOATING_DATA(p_ey) / GET_INTEGER_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::FLOATING: {
					//==  FLOATING / FLOATING  ==//
					floating_t ftemp = GET_FLOATING_DATA(p_ey) / GET_FLOATING_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  FLOATING / RATIONAL  ==//
					floating_t ftemp
					 = GET_FLOATING_DATA(p_ey) / GET_RATIONAL_DATA(p_ex).getFloating();
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::EINFINITY: {
					//==  FLOATING / EINFINITY  ==//
					return divInfinity(p_ey, p_ex);
				}
				default:
					//==  FLOATING / Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::RATIONAL:
			//===  RATIONAL / ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  RATIONAL / INTEGER ==//
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					rational_t rat_y = GET_RATIONAL_DATA(p_ey);
					try {
						rational_t rtemp_ans = rat_y / int_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						floating_t ftemp
						 = rat_y.getFloating() / (floating_t)int_x;
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::FLOATING: {
					//==  RATIONAL / FLOATING ==//
					floating_t ftemp
					 = GET_RATIONAL_DATA(p_ey).getFloating() / GET_FLOATING_DATA(p_ex);
					setFloating(p_etemp, ftemp);
					break;
				}
				case Element::RATIONAL: {
					//==  RATIONAL / RATIONAL ==//
					rational_t rat_y = GET_RATIONAL_DATA(p_ey);
					rational_t rat_x = GET_RATIONAL_DATA(p_ex);
					try {
						rational_t rtemp_ans = rat_y / rat_x;
						setRational(p_etemp, rtemp_ans);
					}
					catch (...) {
						setFlags(GeneralProcessor::RAT_OVERFLOW);
						floating_t ftemp
						 = rat_y.getFloating() / rat_x.getFloating();
						setFloating(p_etemp, ftemp);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  RATIONAL / EINFINITY  ==//
					return divInfinity(p_ey, p_ex);
				}
				default:
					//==  RATIONAL / Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::EINFINITY: {
			//==  EINFINITY / ANY  ==//
			return divInfinity(p_ey, p_ex);
		}
		default:
			//===  Unexpected / ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MODULO
// [ description ]
// MODULO function for 2 integers
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mod(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
		//===  mod(INTEGER, INTEGER)  ===//
		integer_t int_y = GET_INTEGER_DATA(p_ey);
		integer_t int_x = GET_INTEGER_DATA(p_ex);
		//  Truncated division adopted  //
		if (0 != int_x) {
			integer_t r = 0;
			if (int_y < 0) {
				if (int_x < 0) { // neg mod neg
					if (!util::checkNeg(int_x)) {
						if (util::checkNeg(int_y)) {
							int_y -= int_x;
						}
						r = -((-int_y) % (-int_x));
					}
					else {
						if (int_y == int_x) {
							r = 0;
						}
						else {
							r = int_y;
						}
					}
				}
				else { // neg mod pos
					if (util::checkNeg(int_y)) {
						int_y += int_x;
					}
					r = -((-int_y) % int_x);
				}
			}
			else {
				if (int_x < 0) { // pos mod neg
					if (!util::checkNeg(int_x)) {
						r = int_y % (-int_x);
					}
					else {
						r = int_y;
					}
				}
				else { // pos mod pos
					r = int_y % int_x;
				}
			}
			setInteger(p_etemp, r);
		}
		else {
			throw BadArgument("DIV_ZERO", __FUNCTION__);
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / QUOTIENT
// [ description ]
// QUOTIENT function for 2 integers
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::quot(const SpElement &p_ey, const SpElement &p_ex) {
	using util = SafetyIntegerCalculator;
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
		//===  quot(INTEGER, INTEGER)  ===//
		integer_t int_y = GET_INTEGER_DATA(p_ey);
		integer_t int_x = GET_INTEGER_DATA(p_ex);
		//  Truncated division adopted  //
		if (0 != int_x) {
			integer_t q = 0;
			if (util::checkDiv(int_y, int_x)) {
				setFlags(GeneralProcessor::INT_OVERFLOW);
				setFloating(p_etemp, (floating_t)int_y / (floating_t)int_x);
			}
			else if (int_y < 0) {
				if (int_x < 0) { // neg / neg
					if (!util::checkNeg(int_x)) {
						if (util::checkNeg(int_y)) {
							q = 1;
							int_y -= int_x;
						}
						q += (-int_y) / (-int_x);
					}
					else {
						if (int_y == int_x) {
							q = 1;
						}
						else {
							q = 0;
						}
					}
				}
				else { // neg / pos
					if (util::checkNeg(int_y)) {
						q = -1;
						int_y += int_x;
					}
					q -= (-int_y) / int_x;
				}
				setInteger(p_etemp, q);
			}
			else {
				if (int_x < 0) { // pos / neg
					if (!util::checkNeg(int_x)) {
						q = -(int_y / (-int_x));
					}
					else {
						q = 0;
					}
				}
				else { // pos / pos
					q = int_y / int_x;
				}
				setInteger(p_etemp, q);
			}
		}
		else {
			throw BadArgument("DIV_ZERO", __FUNCTION__);
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
