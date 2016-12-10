#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SIN (Grade)
// [ description ]
// SIN function for scalar (Grade)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::sinGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  sinGrade(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			integer_t temp = int_x % 400;
			if (temp < 0) {
				temp += 400;
			}
			Quadrant quad = static_cast<Quadrant>(temp / 100);
			bool is_neg = false;
			switch (quad) {
				case Quadrant::FIRST:
					is_neg = false;
					break;
				case Quadrant::SECOND:
					is_neg = false;
					temp = 200 - temp;
					break;
				case Quadrant::THIRD:
					is_neg = true;
					temp = temp - 200;
					break;
				case Quadrant::FORTH:
					is_neg = true;
					temp = 400 - temp;
					break;
				default:
					break;
			}
			switch (temp) {
				case 0:
					setInteger(p_etemp, 0);
					break;
				case 50:
					p_etemp = div(sqrt(GEN_INTEGER(2)), GEN_INTEGER(2));
					break;
				case 100:
					setInteger(p_etemp, 1);
					break;
				default: {
					p_etemp = sinRadian(gradeToRadian(GEN_INTEGER(temp)));
					break;
			}
			} // end of switch
			if (is_neg) {
				p_etemp = neg(p_etemp);
			}
			break;
		}
		case Element::FLOATING:
			//===  sinGrade(FLOATING)  ===//
			// fall through
		case Element::RATIONAL: {
			//===  sinGrade(RATIONAL)  ===//
			p_etemp = gradeToRadian(p_ex);
			if (!isInEpsilonInverse(p_etemp)) {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			p_etemp = sinRadian(p_etemp);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COS (grade)
// [ description ]
// COS function for scalar (grade)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::cosGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  cosGrade(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			integer_t temp = int_x % 400;
			if (temp < 0) {
				temp += 400;
			}
			Quadrant quad = static_cast<Quadrant>(temp / 100);
			bool is_neg = false;
			switch (quad) {
				case Quadrant::FIRST:
					is_neg = false;
					break;
				case Quadrant::SECOND:
					is_neg = true;
					temp = 200 - temp;
					break;
				case Quadrant::THIRD:
					is_neg = true;
					temp = temp - 200;
					break;
				case Quadrant::FORTH:
					is_neg = false;
					temp = 400 - temp;
					break;
				default:
					break;
			}
			switch (temp) {
				case 0:
					setInteger(p_etemp, 1);
					break;
				case 50:
					p_etemp = div(sqrt(GEN_INTEGER(2)), GEN_INTEGER(2));
					break;
				case 100:
					setInteger(p_etemp, 0);
					break;
				default: {
					p_etemp = cosRadian(gradeToRadian(GEN_INTEGER(temp)));
					break;
			}
			} // end of switch
			if (is_neg) {
				p_etemp = neg(p_etemp);
			}
			break;
		}
		case Element::FLOATING:
			//===  cosGrade(FLOATING)  ===//
			// fall through
		case Element::RATIONAL: {
			//===  cosGrade(RATIONAL)  ===//
			p_etemp = gradeToRadian(p_ex);
			if (!isInEpsilonInverse(p_etemp)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			p_etemp = cosRadian(p_etemp);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / TAN (Grade)
// [ description ]
// TAN function for scalar (Grade)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::tanGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  tanGrade(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			integer_t temp = int_x % 400;
			if (temp < 0) {
				temp += 400;
			}
			Quadrant quad = static_cast<Quadrant>(temp / 100);
			bool is_neg = false;
			switch (quad) {
				case Quadrant::FIRST:
					is_neg = false;
					break;
				case Quadrant::SECOND:
					is_neg = true;
					temp = 200 - temp;
					break;
				case Quadrant::THIRD:
					is_neg = false;
					temp = temp - 200;
					break;
				case Quadrant::FORTH:
					is_neg = true;
					temp = 400 - temp;
					break;
				default:
					break;
			}
			switch (temp) {
				case 0:
					setInteger(p_etemp, 0);
					break;
				case 50:
					setInteger(p_etemp, 1);
					break;
				case 100:
					throw BadArgument("BAD_VAL", __FUNCTION__);
				default:
					p_etemp = tanRadian(degreeToRadian(GEN_INTEGER(temp)));
					break;
			} // end of switch
			if (is_neg) {
				p_etemp = neg(p_etemp);
			}
			break;
		}
		case Element::FLOATING:
			//===  tanGrade(FLOATING)  ===//
			// fall through
		case Element::RATIONAL: {
			//===  tanGrade(RATIONAL)  ===//
			p_etemp = gradeToRadian(p_ex);
			if (!isInEpsilonInverse(p_etemp)) {
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			p_etemp = tanRadian(p_etemp);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ASIN (grade)
// [ description ]
// ASIN function for scalar (grade)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::asinGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  asinGrade(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 <= int_x) && (int_x <= 1)) {
				p_etemp = radianToGrade(asinRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  asinGrade(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 <= flt_x) && (flt_x <= 1.0)) {
				p_etemp = radianToGrade(asinRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  asinGrade(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 <= ftemp) && (ftemp <= 1.0)) {
				p_etemp = radianToGrade(asinRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
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
// ECKERT PROCESSOR / ACOS (grade)
// [ description ]
// ACOS function for scalar (grade)
// [ Scope ]
// GeneralProcessor
// [ Interface ]
// SpElement GeneralProcessor::acosGrade(const SpElement &p_ex)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::acosGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  acosGrade(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 <= int_x) && (int_x <= 1)) {
				p_etemp = radianToGrade(acosRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  acosGrade(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 <= flt_x) && (flt_x <= 1.0)) {
				p_etemp = radianToGrade(acosRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  acosGrade(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 <= ftemp) && (ftemp <= 1.0)) {
				p_etemp = radianToGrade(acosRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
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
// ECKERT PROCESSOR / ATAN (grade)
// [ description ]
// ATAN function for scalar (grade)
// [ Update ]
// Jan 29, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::atanGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  atanGrade(INTEGER)  ===//
			if (1 == GET_INTEGER_DATA(p_ex)) {
				p_etemp = GEN_INTEGER(50);
			}
			else {
				p_etemp = radianToGrade(atanRadian(p_ex));
			}
			break;
		}
		case Element::FLOATING: {
			//===  atanGrade(FLOATING)  ===//
			p_etemp = radianToGrade(atanRadian(p_ex));
			break;
		}
		case Element::RATIONAL: {
			//===  atanGrade(RATIONAL)  ===//
			p_etemp = radianToGrade(atanRadian(p_ex));
			break;
		}
		case Element::EINFINITY: {
			//===  atanGrade(EINFINITY)  ===//
			int sign = GET_EINFINITY_DATA(p_ex);
			if (sign > 0) {
				p_etemp = GEN_INTEGER(100);
			}
			else if (sign < 0) {
				p_etemp = GEN_INTEGER(-100);
			}
			else {
				setError(p_etemp, "IND");
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
