#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ADD INFINITY
// [ description ]
// ADD function for scalar and infinity
// [ Update ]
// Oct 08, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::addInfinity(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::EINFINITY:
			//===  EINFINITY + ???  ===//
			switch (x_type) {
				case Element::INTEGER:
					//==  EINFINITY + INTEGER  ==/
					// fall through
				case Element::FLOATING:
					//==  EINFINITY + FLOATING  ==/
					// fall through
				case Element::RATIONAL: {
					//==  EINFINITY + RATIONAL  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					if (sgn_y > 0) {
						setInfinity(p_etemp, POSITIVE);
					}
					else if (sgn_y < 0) {
						setInfinity(p_etemp, NEGATIVE);
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  EINFINITY + EINFINITY  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					int sgn_x = GET_EINFINITY_DATA(p_ex);
					if (sgn_y > 0) {
						if (sgn_x < 0) {
							setError(p_etemp, "NAN");
						}
						else if (sgn_x > 0) {
							setInfinity(p_etemp, POSITIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (sgn_y < 0) {
						if (sgn_x > 0) {
							setError(p_etemp, "NAN");
						}
						else if (sgn_x < 0) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				default:
					//==  EINFINITY + Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::INTEGER:
			//===  INTEGER + ???  ===//
			// fall through
		case Element::FLOATING:
			//===  FLOATING + ???  ===//
			// fall through
		case Element::RATIONAL:
			//===  RATIONAL + ???  ===//
			switch (x_type) {
			case Element::EINFINITY: {
				//==  SCALAR + EINFINITY  ==/
				int sgn_x = GET_EINFINITY_DATA(p_ex);
				if (sgn_x > 0) {
					setInfinity(p_etemp, POSITIVE);
				}
				else if (sgn_x < 0) {
					setInfinity(p_etemp, NEGATIVE);
				}
				else {
					setInfinity(p_etemp, ZERO);
				}
				break;
			}
			default:
				//==  SCALAR + Unexpected  ==/
				throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected + ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SUBTRACT INFINITY
// [ description ]
// SUBTRACT function for scalar and infinity
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::subInfinity(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::EINFINITY:
			//===  EINFINITY - ???  ===//
			switch (x_type) {
				case Element::INTEGER:
					//==  EINFINITY - INTEGER  ==/
					// fall through
				case Element::FLOATING:
					//==  EINFINITY - FLOATING  ==/
					// fall through
				case Element::RATIONAL: {
					//==  EINFINITY - RATIONAL  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					if (sgn_y > 0) {
						setInfinity(p_etemp, POSITIVE);
					}
					else if (sgn_y < 0) {
						setInfinity(p_etemp, NEGATIVE);
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  EINFINITY - EINFINITY  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					int sgn_x = GET_EINFINITY_DATA(p_ex);
					if (sgn_y > 0) {
						if (sgn_x > 0) {
							setError(p_etemp, "NAN");
						}
						else if (sgn_x < 0) {
							setInfinity(p_etemp, POSITIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (sgn_y < 0) {
						if (sgn_x < 0) {
							setError(p_etemp, "NAN");
						}
						else if (sgn_x > 0) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				default:
					//==  EINFINITY - Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::INTEGER:
			//===  INTEGER - ???  ===//
			// fall through
		case Element::FLOATING:
			//===  FLOATING - ???  ===//
			// fall through
		case Element::RATIONAL:
			//===  RATIONAL - ???  ===//
			switch (x_type) {
				case Element::EINFINITY: {
					//==  SCALAR - EINFINITY  ==/
					int sgn_x = GET_EINFINITY_DATA(p_ex);
					if (sgn_x > 0) {
						setInfinity(p_etemp, NEGATIVE);
					}
					else if (sgn_x < 0) {
						setInfinity(p_etemp, POSITIVE);
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				default:
					//==  SCALAR - Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected - ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MULTIPLY INFINITY
// [ description ]
// MULTIPLY function for scalar and infinity
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mulInfinity(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::EINFINITY:
			//===  EINFINITY * ???  ===//
			switch (x_type) {
				case Element::INTEGER:
					//==  EINFINITY * INTEGER  ==/
					// fall through
				case Element::FLOATING: {
					//==  EINFINITY * FLOATING  ==/
					// fall through
				case Element::RATIONAL: {
					//==  EINFINITY * RATIONAL  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					if (sgn_y > 0) {
						if (isPositive(p_ex)) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (isNegative(p_ex)) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setError(p_etemp, "NAN");
						}
					}
					else if (sgn_y < 0) {
						if (isNegative(p_ex)) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (isPositive(p_ex)) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setError(p_etemp, "NAN");
						}
					}
					else {
						if (isZero(p_ex)) {
							setError(p_etemp, "NAN");
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					break;
				}
				case Element::EINFINITY: {
					//==  EINFINITY * EINFINITY  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					int sgn_x = GET_EINFINITY_DATA(p_ex);
					if (sgn_y > 0) {
						if (sgn_x > 0) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sgn_x < 0) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (sgn_y < 0) {
						if (sgn_x < 0) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sgn_x > 0) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				default:
					//==  EINFINITY * Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		}
		case Element::INTEGER:
			//===  INTEGER * ???  ===//
			// fall through
		case Element::FLOATING:
			//===  FLOATING * ???  ===//
			// fall through
		case Element::RATIONAL:
			//===  RATIONAL * ???  ===//
			switch (x_type) {
				case Element::EINFINITY: {
					//==  SCALAR * EINFINITY  ==/
					int sgn_x = GET_EINFINITY_DATA(p_ex);
					if (isPositive(p_ey)) {
						if (sgn_x > 0) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sgn_x < 0) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (isNegative(p_ey)) {
						if (sgn_x < 0) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sgn_x > 0) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				default:
					//==  SCALAR * Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected * ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DIV INFINITY
// [ description ]
// DIV function for scalar and infinity
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::divInfinity(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::EINFINITY: {
			//===  EINFINITY / ???  ===//
			switch (x_type) {
				case Element::INTEGER:
					//==  EINFINITY / INTEGER  ==/
					// fall through
				case Element::FLOATING:
					//==  EINFINITY / FLOATING  ==/
					// fall through
				case Element::RATIONAL: {
					//==  EINFINITY / RATIONAL  ==/
					int sgn_y = GET_EINFINITY_DATA(p_ey);
					if (sgn_y > 0) {
						if (isPositive(p_ex)) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (isNegative(p_ex)) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (sgn_y < 0) {
						if (isNegative(p_ex)) {
							setInfinity(p_etemp, POSITIVE);
						}
						else if (isPositive(p_ex)) {
							setInfinity(p_etemp, NEGATIVE);
						}
						else {
							setInfinity(p_etemp, ZERO);
						}
					}
					else {
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				case Element::EINFINITY: {
					//==  EINFINITY / EINFINITY  ==/
					setError(p_etemp, "NAN");
					break;
				}
				default:
					//==  EINFINITY / Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		}
		case Element::INTEGER:
			//===  INTEGER / ???  ===//
			// fall through
		case Element::FLOATING:
			//===  FLOATING / ???  ===//
			// fall through
		case Element::RATIONAL:
			//===  RATIONAL / ???  ===//
			switch (x_type) {
				case Element::EINFINITY: {
					//==  SCALAR / EINFINITY  ==/
					setInteger(p_etemp, 0);
					break;
				}
				default:
					//==  SCALAR / Unexpected  ==/
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected / ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / POWER INFINITY
// [ description ]
// POWER function for scalar and infinity
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::powInfinity(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::EINFINITY:
			//===  EINFINITY ^ ???  ===//
			switch (x_type) {
				case Element::INTEGER:
					//==  EINFINITY ^ INTEGER  ==//
					// fall through
				case Element::RATIONAL:
					//==  EINFINITY ^ RATIONAL  ==//
					// fall through
				case Element::FLOATING: {
					//==  EINFINITY ^ FLOATING  ==//
					if (isZero(p_ex)) {
						setError(p_etemp, "NAN");
					}
					else if (isPositive(p_ey)) {
						if (isNegative(p_ex)) {
							// +inf ^ -real = 0
							p_etemp = GEN_INTEGER(0);
						}
						else {
							// +inf ^ +real = +inf
							setInfinity(p_etemp, POSITIVE);
						}
					}
					else if (isNegative(p_ey)) {
						if (isNegative(p_ex)) {
							// -inf ^ -real = 0
							p_etemp = GEN_INTEGER(0);
						}
						else {
							// -inf ^ +real = +inf
							setError(p_etemp, "NAN");
						}
					}
					else {
						// -inf ^ +real = error
						setError(p_etemp, "NAN");
					}
					break;
				}
				case Element::EINFINITY: {
					//==  EINFINITY ^ EINFINITY  ==//
					if (isPositive(p_ey)) {
						if (isNegative(p_ex)) {
							// +inf ^ -inf = error
							setError(p_etemp, "NAN");
						}
						else if (isPositive(p_ex)) {
							// +inf ^ +inf = +inf
							setInfinity(p_etemp, POSITIVE);
						}
						else {
							// inf ^ cinf = cinf
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (isNegative(p_ey)) {
						if (isPositive(p_ex)) {
							// -inf ^ inf = error
							setError(p_etemp, "NAN");
						}
						else if (isNegative(p_ex)) {
							// -inf ^ -inf = error
							setError(p_etemp, "NAN");
						}
						else {
							// -inf ^ cinf = error
							setError(p_etemp, "NAN");
						}
					}
					else {
						// cinf ^ any inf = cinf
						setInfinity(p_etemp, ZERO);
					}
					break;
				}
				case Element::COMPLEX: {
					//==  EINFINITY ^ COMPLEX  ==//
					setInfinity(p_etemp, ZERO);
					break;
				}
				default:
					//==  EINFINITY ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::INTEGER:
			//===  INTEGER ^ ???  ===//
			switch (x_type) {
				case Element::EINFINITY: {
					//==  INTEGER ^ EINFINITY  ==//
					integer_t int_y = GET_INTEGER_DATA(p_ey);
					int sign = GET_EINFINITY_DATA(p_ex);
					if (int_y > 1) {
						if (sign > 0) {
							// +int ^ +inf = +inf
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sign < 0) {
							// +int ^ -inf = 0
							setInteger(p_etemp, 0);
						}
						else {
							// +int ^ cinf = cinf
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (int_y < -1) {
						if (sign > 0) {
							// -int ^ +inf = error
							setError(p_etemp, "NAN");
						}
						else if (sign < 0) {
							// -int ^ -inf = 0
							setInteger(p_etemp, 0);
						}
						else {
							// -int ^ cinf = error
							setError(p_etemp, "NAN");
						}
					}
					else {
						//  1 ^ inf = error
						//  0 ^ inf = error
						// -1 ^ inf = error
						setError(p_etemp, "NAN");
					}
					break;
				}
				default:
					//==  INTEGER ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::RATIONAL:
			//===  RATIONAL ^ ???  ===//
			switch (x_type) {
				case Element::EINFINITY: {
					//==  RATIONAL ^ EINFINITY  ==//
					floating_t flt_y = GET_RATIONAL_DATA(p_ey).getFloating();
					int sign = GET_EINFINITY_DATA(p_ex);
					if ((-1.0 < flt_y) && (flt_y < 1.0)) {
						if (sign > 0) {
							setInteger(p_etemp, 0);
						}
						else {
							setError(p_etemp, "NAN");
						}
					}
					else if (flt_y > 1.0) {
						if (sign > 0) {
							// +flt ^ +inf = +inf
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sign < 0) {
							// +flt ^ -inf = 0
							setInteger(p_etemp, 0);
						}
						else {
							// +flt ^ cinf = cinf
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (flt_y < -1.0) {
						if (sign > 0) {
							// -flt ^ +inf = error
							setError(p_etemp, "NAN");
						}
						else if (sign < 0) {
							// -flt ^ -inf = 0
							setInteger(p_etemp, 0);
						}
						else {
							// -flt ^ cinf = error
							setError(p_etemp, "NAN");
						}
					}
					else {
						setError(p_etemp, "NAN");
					}
					break;
				}
				default:
					//==  RATIONAL ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::FLOATING:
			//===  FLOATING ^ ???  ===//
			switch (x_type) {
				case Element::EINFINITY: {
					//==  FLOATING ^ EINFINITY  ==//
					floating_t flt_y = GET_FLOATING_DATA(p_ey);
					int sign = GET_EINFINITY_DATA(p_ex);
					if ((-1.0 < flt_y) && (flt_y < 1.0)) {
						if (sign > 0) {
							setInteger(p_etemp, 0);
						}
						else {
							setError(p_etemp, "NAN");
						}
					}
					else if (flt_y > 1.0) {
						if (sign > 0) {
							// +flt ^ +inf = +inf
							setInfinity(p_etemp, POSITIVE);
						}
						else if (sign < 0) {
							// +flt ^ -inf = 0
							setInteger(p_etemp, 0);
						}
						else {
							// +flt ^ cinf = cinf
							setInfinity(p_etemp, ZERO);
						}
					}
					else if (flt_y < -1.0) {
						if (sign > 0) {
							// -flt ^ +inf = error
							setError(p_etemp, "NAN");
						}
						else if (sign < 0) {
							// -flt ^ -inf = 0
							setInteger(p_etemp, 0);
						}
						else {
							// -flt ^ cinf = error
							setError(p_etemp, "NAN");
						}
					}
					else {
						setError(p_etemp, "NAN");
					}
					break;
				}
				default:
					//==  Unexpected ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected ^ Any  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
