#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SIN (degree)
// [ description ]
// SIN function for scalar (degree)
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::sinDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  sinDegree(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			integer_t temp = int_x % 360;
			if (temp < 0) {
				temp += 360;
			}
			Quadrant quad = static_cast<Quadrant>(temp / 90);
			bool is_neg = false;
			switch (quad) {
				case Quadrant::FIRST:
					is_neg = false;
					break;
				case Quadrant::SECOND:
					is_neg = false;
					temp = 180 - temp;
					break;
				case Quadrant::THIRD:
					is_neg = true;
					temp = temp - 180;
					break;
				case Quadrant::FORTH:
					is_neg = true;
					temp = 360 - temp;
					break;
				default:
					break;
			}
			switch (temp) {
				case 0:
					setInteger(p_etemp, 0);
					break;
				case 15:
					p_etemp = sub(sqrt(GEN_INTEGER(6)), sqrt(GEN_INTEGER(2)));
					p_etemp = div(p_etemp, GEN_INTEGER(4));
					break;
				case 30:
					setRational(p_etemp, 1, 2);
					break;
				case 45:
					p_etemp = div(sqrt(GEN_INTEGER(2)), GEN_INTEGER(2));
					break;
				case 60:
					p_etemp = div(sqrt(GEN_INTEGER(3)), GEN_INTEGER(2));
					break;
				case 75:
					p_etemp = add(sqrt(GEN_INTEGER(6)), sqrt(GEN_INTEGER(2)));
					p_etemp = div(p_etemp, GEN_INTEGER(4));
					break;
				case 90:
					setInteger(p_etemp, 1);
					break;
				default:
					p_etemp = sinRadian(degreeToRadian(GEN_INTEGER(temp)));
					break;
			} // end of switch
			if (is_neg) {
				p_etemp = neg(p_etemp);
			}
			break;
		}
		case Element::FLOATING:
			//===  sinDegree(FLOATING)  ===//
			// fall through
		case Element::RATIONAL: {
			//===  sinDegree(RATIONAL)  ===//
			p_etemp = degreeToRadian(p_ex);
			if (!isInEpsilonInverse(p_etemp)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
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
// ECKERT PROCESSOR / COS (degree)
// [ description ]
// COS function for scalar (degree)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::cosDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  cosDegree(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			integer_t temp = int_x % 360;
			if (temp < 0) {
				temp += 360;
			}
			Quadrant quad = static_cast<Quadrant>(temp / 90);
			bool is_neg = false;
			switch (quad) {
				case Quadrant::FIRST:
					is_neg = false;
					break;
				case Quadrant::SECOND:
					is_neg = true;
					temp = 180 - temp;
					break;
				case Quadrant::THIRD:
					is_neg = true;
					temp = temp - 180;
					break;
				case Quadrant::FORTH:
					is_neg = false;
					temp = 360 - temp;
					break;
				default:
					break;
			}
			switch (temp) {
				case 0:
					setInteger(p_etemp, 1);
					break;
				case 15:
					p_etemp = add(sqrt(GEN_INTEGER(6)), sqrt(GEN_INTEGER(2)));
					p_etemp = div(p_etemp, GEN_INTEGER(4));
					break;
				case 30:
					p_etemp = div(sqrt(GEN_INTEGER(3)), GEN_INTEGER(2));
					break;
				case 45:
					p_etemp = div(sqrt(GEN_INTEGER(2)), GEN_INTEGER(2));
					break;
				case 60:
					setRational(p_etemp, 1, 2);
					break;
				case 75:
					p_etemp = sub(sqrt(GEN_INTEGER(6)), sqrt(GEN_INTEGER(2)));
					p_etemp = div(p_etemp, GEN_INTEGER(4));
					break;
				case 90:
					setInteger(p_etemp, 0);
					break;
				default:
					p_etemp = cosRadian(degreeToRadian(GEN_INTEGER(temp)));
					break;
			} // end of switch
			if (is_neg) {
				p_etemp = neg(p_etemp);
			}
			break;
		}
		case Element::FLOATING:
			//===  cosDegree(FLOATING)  ===//
			// fall through
		case Element::RATIONAL: {
			//===  cosDegree(RATIONAL)  ===//
			p_etemp = degreeToRadian(p_ex);
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
// ECKERT PROCESSOR / TAN (degree)
// [ description ]
// TAN function for scalar (degree)
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::tanDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  tanDegree(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			integer_t temp = int_x % 360;
			if (temp < 0) {
				temp += 360;
			}
			Quadrant quad = static_cast<Quadrant>(temp / 90);
			bool is_neg = false;
			switch (quad) {
				case Quadrant::FIRST:
					is_neg = false;
					break;
				case Quadrant::SECOND:
					is_neg = true;
					temp = 180 - temp;
					break;
				case Quadrant::THIRD:
					is_neg = false;
					temp = temp - 180;
					break;
				case Quadrant::FORTH:
					is_neg = true;
					temp = 360 - temp;
					break;
				default:
					break;
			}
			switch (temp) {
				case 0:
					setInteger(p_etemp, 0);
					break;
				case 15:
					p_etemp = sub(GEN_INTEGER(2), sqrt(GEN_INTEGER(3)));
					break;
				case 30:
					p_etemp = div(sqrt(GEN_INTEGER(3)), GEN_INTEGER(3));
					break;
				case 45:
					setInteger(p_etemp, 1);
					break;
				case 60:
					p_etemp = sqrt(GEN_INTEGER(3));
					break;
				case 75:
					p_etemp = add(GEN_INTEGER(2), sqrt(GEN_INTEGER(3)));
					break;
				case 90:
					throw BadArgument("BAD_VAL", __FUNCTION__);
				default:
					p_etemp = tanRadian(degreeToRadian(GEN_INTEGER(temp)));
					break;
			}
			if (is_neg) {
				p_etemp = neg(p_etemp);
			}
			break;
		}
		case Element::FLOATING:
			//===  tanDegree(FLOATING)  ===//
			// fall through
		case Element::RATIONAL: {
			//===  tanDegree(RATIONAL)  ===//
			p_etemp = degreeToRadian(p_ex);
			if (!isInEpsilonInverse(p_etemp)) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
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
// ECKERT PROCESSOR / ASIN (degree)
// [ description ]
// ASIN function for scalar (degree)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::asinDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  asinDegree(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 <= int_x) && (int_x <= 1)) {
				p_etemp = radianToDegree(asinRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  asinDegree(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 <= flt_x) && (flt_x <= 1.0)) {
				p_etemp = radianToDegree(asinRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  asinDegree(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 <= ftemp) && (ftemp <= 1.0)) {
				p_etemp = radianToDegree(asinRadian(p_ex));
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
// ECKERT PROCESSOR / ACOS (degree)
// [ description ]
// ACOS function for scalar (degree)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::acosDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  acosDegree(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if ((-1 <= int_x) && (int_x <= 1)) {
				p_etemp = radianToDegree(acosRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::FLOATING: {
			//===  acosDegree(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			if ((-1.0 <= flt_x) && (flt_x <= 1.0)) {
				p_etemp = radianToDegree(acosRadian(p_ex));
			}
			else {
				throw BadArgument("BAD_RNG" , __FUNCTION__);
			}
			break;
		}
		case Element::RATIONAL: {
			//===  acosDegree(RATIONAL)  ===//
			floating_t ftemp = GET_RATIONAL_DATA(p_ex).getFloating();
			if ((-1.0 <= ftemp) && (ftemp <= 1.0)) {
				p_etemp = radianToDegree(acosRadian(p_ex));
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
// ECKERT PROCESSOR / ATAN (degree)
// [ description ]
// ATAN function for scalar (degree)
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::atanDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  atanDegree(INTEGER)  ===//
			if (1 == GET_INTEGER_DATA(p_ex)) {
				p_etemp = GEN_INTEGER(45);
			}
			else {
				p_etemp = radianToDegree(atanRadian(p_ex));
			}
			break;
		}
		case Element::FLOATING: {
			//===  atanDegree(FLOATING)  ===//
			p_etemp = radianToDegree(atanRadian(p_ex));
			break;
		}
		case Element::RATIONAL: {
			//===  atanDegree(RATIONAL)  ===//
			p_etemp = radianToDegree(atanRadian(p_ex));
			break;
		}
		case Element::EINFINITY: {
			//===  atanDegree(EINFINITY)  ===//
			int sign = GET_EINFINITY_DATA(p_ex);
			if (sign > 0) {
				p_etemp = GEN_INTEGER(90);
			}
			else if (sign < 0) {
				p_etemp = GEN_INTEGER(-90);
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
