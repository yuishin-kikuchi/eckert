#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / POWER
// [ description ]
// POWER function for 2 scalars
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::powScalar(const SpElement &p_ey, const SpElement &p_ex)
try {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	if (p_ey->isType(Element::EINFINITY) || p_ex->isType(Element::EINFINITY)) {
		return powInfinity(p_ey, p_ex);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::INTEGER:
			//===  INTEGER ^ ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  INTEGER ^ INTEGER  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					if (0 == int_y) {
						if (0 == int_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (int_x < 0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setInteger(p_etemp, 0);
						}
					}
					else {
						p_etemp = nthPow(p_ey, p_ex);
					}
					break;
				}
				case Element::FLOATING: {
					//==  INTEGER ^ FLOATING  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					floating_t flt_x = GET_FLOATING_DATA(p_ex);
					if (0 == int_y) {
						if (0.0 == flt_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (flt_x < 0.0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setInteger(p_etemp, 0);
						}
					}
					else {
						if (int_y >= 0) {
							// +int ^ flt = real
							floating_t ftemp = 1.0;
							if (0.0 != flt_x) {
								ftemp = std::pow((floating_t)int_y, flt_x);
							}
							setFloating(p_etemp, ftemp);
						}
						else {
							// -int ^ flt = complex
							throw BadScalar("CPX_OFF", __FUNCTION__);
						}
					}
					break;
				}
				case Element::RATIONAL: {
					//==  INTEGER ^ RATIONAL  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					rational_t rat_x = GET_RATIONAL_DATA(p_ex);
					if (0 == int_y) {
						if (0 == rat_x.getNum()) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (rat_x.getNum() < 0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setInteger(p_etemp, 0);
						}
					}
					else {
						if (int_y >= 0) {
							// +int ^ rat = real
							p_etemp = nthRoot(p_ey, GEN_INTEGER(rat_x.getDen()));
							p_etemp = nthPow(p_etemp, GEN_INTEGER(rat_x.getNum()));
						}
						else {
							// -int ^ rat = complex
							throw BadScalar("CPX_OFF", __FUNCTION__);
						}
					}
					break;
				}
				case Element::EINFINITY: {
					//==  INTEGER ^ EINFINITY  ==//
					return powInfinity(p_ey, p_ex);
				}
				default:
					//==  INTEGER ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::FLOATING:
			//===  FLOATING ^ ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  FLOATING ^ INTEGER  ==//
					floating_t flt_y = GET_FLOATING_DATA(p_ey);
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					if (0.0 == flt_y) {
						if (0 == int_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (int_x < 0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setFloating(p_etemp, 0.0);
						}
					}
					else {
						p_etemp = nthPow(p_ey, p_ex);
					}
					break;
				}
				case Element::FLOATING: {
					//==  FLOATING ^ FLOATING  ==//
					floating_t flt_y = GET_FLOATING_DATA(p_ey);
					floating_t flt_x = GET_FLOATING_DATA(p_ex);
					if (0.0 == flt_y) {
						if (0.0 == flt_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (flt_x < 0.0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setFloating(p_etemp, 0.0);
						}
					}
					else {
						floating_t ftemp = 0.0;
						if (flt_y >= 0.0) {
							// +flt ^ flt = real
							if (0.0 != flt_y) {
								ftemp = std::pow(flt_y, flt_x);
							}
							setFloating(p_etemp, ftemp);
						}
						else {
							// -flt ^ flt = complex
							throw BadScalar("CPX_OFF", __FUNCTION__);
						}
					}
					break;
				}
				case Element::RATIONAL: {
					//==  FLOATING ^ RATIONAL  ==//
					floating_t flt_y = GET_FLOATING_DATA(p_ey);
					floating_t flt_x = GET_RATIONAL_DATA(p_ex).getFloating();
					if (0.0 == flt_y) {
						if (0.0 == flt_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (flt_x < 0.0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setFloating(p_etemp, 0.0);
						}
					}
					else {
						floating_t ftemp = 0.0;
						if (flt_y >= 0.0) {
							// +flt ^ rat = real
							if (0.0 != flt_y) {
								ftemp = std::pow(flt_y, flt_x);
							}
							setFloating(p_etemp, ftemp);
						}
						else {
							// -flt ^ rat = complex
							throw BadScalar("CPX_OFF", __FUNCTION__);
						}
					}
					break;
				}
				case Element::EINFINITY: {
					//==  FLOATING ^ EINFINITY  ==//
					return powInfinity(p_ey, p_ex);
				}
				default:
					//==  FLOATING ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::RATIONAL:
			//===  RATIONAL ^ ???  ===//
			switch (x_type) {
				case Element::INTEGER: {
					//==  RATIONAL ^ INTEGER ==//
					rational_t rat_y = GET_RATIONAL_DATA(p_ey);
					integer_t int_x = GET_INTEGER_DATA(p_ex);
					if (0 == rat_y.getNum()) {
						if (0 == int_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (int_x < 0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setInteger(p_etemp, 0);
						}
					}
					else {
						p_etemp = nthPow(p_ey, p_ex);
					}
					break;
				}
				case Element::FLOATING: {
					//==  RATIONAL ^ FLOATING ==//
					floating_t flt_y = GET_RATIONAL_DATA(p_ey).getFloating();
					floating_t flt_x = GET_FLOATING_DATA(p_ex);
					if (0.0 == flt_y) {
						if (0.0 == flt_x) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (flt_x < 0.0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setFloating(p_etemp, 0.0);
						}
					}
					else {
						floating_t ftemp = 0.0;
						if (flt_y >= 0.0) {
							// +rat ^ flt = real
							if (0.0 != flt_y) {
								ftemp = std::pow(flt_y, flt_x);
							}
							setFloating(p_etemp, ftemp);
						}
						else {
							// -rat ^ flt = complex
							throw BadScalar("CPX_OFF", __FUNCTION__);
						}
					}
					break;
				}
				case Element::RATIONAL: {
					//==  RATIONAL ^ RATIONAL ==//
					rational_t rat_y = GET_RATIONAL_DATA(p_ey);
					rational_t rat_x = GET_RATIONAL_DATA(p_ex);
					if (0 == rat_y.getNum()) {
						if (0 == rat_x.getNum()) {
							// 0 ^ 0 is UNDEFINED
							throw InvalidValue("ZPOWZ", __FUNCTION__);
						}
						else if (rat_x.getNum() < 0) {
							// 0 ^ NEG is UNDEFINED
							throw InvalidValue("ZPOWN", __FUNCTION__);
						}
						else {
							setInteger(p_etemp, 0);
						}
					}
					else {
						if (rat_y.getNum() >= 0) {
							// +rat ^ rat = real
							p_etemp = nthRoot(p_ey, GEN_INTEGER(rat_x.getDen()));
							p_etemp = nthPow(p_etemp, GEN_INTEGER(rat_x.getNum()));
						}
						else {
							// -rat ^ rat = complex
							throw BadScalar("CPX_OFF", __FUNCTION__);
						}
					}
					break;
				}
				case Element::EINFINITY: {
					//==  RATIONAL ^ EINFINITY  ==//
					return powInfinity(p_ey, p_ex);
				}
				default:
					//==  RATIONAL ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::EINFINITY: {
			//==  EINFINITY ^ ANY  ==//
			return powInfinity(p_ey, p_ex);
		}
		default:
			//===  Unexpected ^ ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}
catch (BadScalar &) {
	//==  SCALAR ^ SCALAR (Defined in complex system)  ==//
	SpElement p_etemp;
	auto &a = p_ey;
	auto &c = p_ex;
	auto d = GEN_INTEGER(0);
	SpElement t = isPositive(a) ? GEN_INTEGER(0) : pi();
	SpElement r = abs(a);
	// angle = c*t + d*ln(r)
	SpElement angle = addScalar(
		mulScalar(c, t),
		mulScalar(d, loge(r))
	);
	// coeff = r^c * exp(-d*t)
	SpElement coeff = mulScalar(
		pow(r, c),
		exp(mulScalar(neg(d), t))
	);
	// real = coeff * cos(angle)
	SpElement p_real = mul(coeff, cosRadian(angle));
	// imag = coeff * sin(angle)
	SpElement p_imag = mul(coeff, sinRadian(angle));
	// optimize complex
	setComplex(p_etemp, p_real, p_imag);
	return p_etemp;
}

} // namespace engine
