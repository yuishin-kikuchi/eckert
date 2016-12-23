#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / REAL PART
// [ description ]
// Get real part
// Re(a + ib) = a
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::re(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::COMPLEX)) {
		//==  Re(a + ib)  ==//
		auto a = GET_COMPLEX_RE(p_ex);
		p_etemp = a;
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / IMAGINARY PART
// [ description ]
// Get imaginary part
// Re(a + ib) = b
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::im(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::COMPLEX)) {
		//==  Re(a + ib)  ==//
		auto b = GET_COMPLEX_IM(p_ex);
		p_etemp = b;
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CONJUGATION
// [ description ]
// Get conjugation
// conj(a + ib) = a - ib
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::conj(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::COMPLEX)) {
		//==  conj(a + ib)  ==//
		auto a = GET_COMPLEX_RE(p_ex);
		auto b = GET_COMPLEX_IM(p_ex);
		setComplex(p_etemp, a, neg(b));
	}
	else if (p_ex->isKindOf(Element::SCALAR_TYPE)) {
		//==  conj(a)  ==//
		p_etemp = p_ex;
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COMPLEX ARGUMENT (Radian)
// [ description ]
// Get complex argument (radian)
// [ Update ]
// Dec 21, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::argRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::COMPLEX)) {
		//===  argRadian(a + ib)  ===//
		auto a = GET_COMPLEX_RE(p_ex);
		auto b = GET_COMPLEX_IM(p_ex);
		if (isZero(p_ex)) {
			//== a, b == 0 then Error ==//
			setError(p_etemp, "IND");
		}
		else if (isPositive(a)) {
			//== a > 0 then atan(b / a) ==//
			p_etemp = atanRadian(divScalar(b, a));
		}
		else if (isZero(a) && isPositive(b)) {
			//== a == 0 and b > 0 then PI/2 ==//
			p_etemp = pi_2();
		}
		else if (isZero(a) && isNegative(b)) {
			//== a == 0 and b < 0 then -PI/2 ==//
			p_etemp = neg(pi_2());
		}
		else if (isNegative(a) && isZero(b)) {
			//== a > 0 and b == 0 then PI ==//
			p_etemp = pi();
		}
		else if (isNegative(a) && isPositive(b)) {
			//== a < 0 and b > 0 then PI - atan(b / a) ==//
			p_etemp = addScalar(pi(), atanRadian(divScalar(b, a)));
		}
		else if (isNegative(a) && isNegative(b)) {
			//== a < 0 and b < 0 then atan(b / a) - PI ==//
			p_etemp = subScalar(atanRadian(divScalar(b, a)), pi());
		}
	}
	else {
		//==  argRadian(OTHER)  ==//
		if (p_ex->isKindOf(Element::SCALAR_TYPE)) {
			if (isZero(p_ex)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else if (isPositive(p_ex)) {
				setInteger(p_etemp, 0);
			}
			else {
				setFloating(p_etemp, PI);
			}
		}
		else {
			//==  argRadian(Not scalar)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COMPLEX ARGUMENT (Degree)
// [ description ]
// Get complex argument (degree)
// [ Update ]
// Dec 21, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::argDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::COMPLEX)) {
		//===  argDegree(a + ib)  ===//
		auto a = GET_COMPLEX_RE(p_ex);
		auto b = GET_COMPLEX_IM(p_ex);
		if (isZero(p_ex)) {
			//== a, b == 0 then Error ==//
			setError(p_etemp, "IND");
		}
		else if (isPositive(a)) {
			//== a > 0 then atan(b / a) ==//
			p_etemp = atanDegree(divScalar(b, a));
		}
		else if (isZero(a) && isPositive(b)) {
			//== a == 0 and b > 0 then 90 ==//
			setInteger(p_etemp, +90);
		}
		else if (isZero(a) && isNegative(b)) {
			//== a == 0 and b < 0 then -90 ==//
			setInteger(p_etemp, -90);
		}
		else if (isNegative(a) && isZero(b)) {
			//== a > 0 and b == 0 then 180 ==//
			setInteger(p_etemp, 180);
		}
		else if (isNegative(a) && isPositive(b)) {
			//== a < 0 and b > 0 then 180 - atan(b / a) ==//
			p_etemp = addScalar(GEN_INTEGER(180), atanDegree(divScalar(b, a)));
		}
		else if (isNegative(a) && isNegative(b)) {
			//== a < 0 and b < 0 then atan(b / a) - 180 ==//
			p_etemp = subScalar(atanDegree(divScalar(b, a)), GEN_INTEGER(180));
		}
	}
	else {
		//==  argDegree(OTHER)  ==//
		if (p_ex->isKindOf(Element::SCALAR_TYPE)) {
			if (isZero(p_ex)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else if (isPositive(p_ex)) {
				setInteger(p_etemp, 0);
			}
			else {
				setInteger(p_etemp, 180);
			}
		}
		else {
			//==  argDegree(Not scalar)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COMPLEX ARGUMENT (Grade)
// [ description ]
// Get complex argument (grade)
// [ Update ]
// Dec 21, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::argGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::COMPLEX)) {
		//===  argGrade(a + ib)  ===//
		auto a = GET_COMPLEX_RE(p_ex);
		auto b = GET_COMPLEX_IM(p_ex);
		if (isZero(p_ex)) {
			//== a, b == 0 then Error ==//
			setError(p_etemp, "IND");
		}
		else if (isPositive(a)) {
			//== a > 0 then atan(b / a) ==//
			p_etemp = atanGrade(divScalar(b, a));
		}
		else if (isZero(a) && isPositive(b)) {
			//== a == 0 and b > 0 then 100 ==//
			setInteger(p_etemp, +100);
		}
		else if (isZero(a) && isNegative(b)) {
			//== a == 0 and b < 0 then -100 ==//
			setInteger(p_etemp, -100);
		}
		else if (isNegative(a) && isZero(b)) {
			//== a > 0 and b == 0 then 200 ==//
			setInteger(p_etemp, 200);
		}
		else if (isNegative(a) && isPositive(b)) {
			//== a < 0 and b > 0 then 200 - atan(b / a) ==//
			p_etemp = addScalar(GEN_INTEGER(200), atanGrade(divScalar(b, a)));
		}
		else if (isNegative(a) && isNegative(b)) {
			//== a < 0 and b < 0 then atan(b / a) - 200 ==//
			p_etemp = subScalar(atanGrade(divScalar(b, a)), GEN_INTEGER(200));
		}
	}
	else {
		//==  argGrade(OTHER)  ==//
		if (p_ex->isKindOf(Element::SCALAR_TYPE)) {
			if (isZero(p_ex)) {
				throw BadArgument("BAD_VAL", __FUNCTION__);
			}
			else if (isPositive(p_ex)) {
				setInteger(p_etemp, 0);
			}
			else {
				setInteger(p_etemp, 200);
			}
		}
		else {
			//==  argGrade(Not scalar)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / POWER
// [ description ]
// POWER for 2 complex numbers
// (a + ib) ^ (c + id) = coeff * [ cos(t) + i sin(t) ]
// [ r = abs(a + ib), t = arg(a + ib),
//   coeff = r^c * exp(-d*t), angle = c*t + d*ln(r) ]
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::powComplex(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	bool y_cplx = p_ey->isType(Element::COMPLEX);
	bool x_cplx = p_ex->isType(Element::COMPLEX);
	if (y_cplx && x_cplx) {
		//==  COMPLEX ^ COMPLEX  ==//
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		SpElement r = abs(p_ey);
		SpElement t = argRadian(p_ey);
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
		// real = cos(angle) * coeff
		SpElement p_real = mulScalar(coeff, cosRadian(angle));
		// imag = sin(angle) * coeff
		SpElement p_imag = mulScalar(coeff, sinRadian(angle));
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (y_cplx) {
		//==  COMPLEX ^ ANY  ==//
		auto c = p_ex;
		SpElement r = abs(p_ey);
		SpElement t = argRadian(p_ey);
		// angle = c*t
		SpElement angle = mul(c, t);
		// coeff = r^c
		SpElement coeff = pow(r, c);
		// real = cos(angle) * coeff
		SpElement p_real = mul(coeff, cosRadian(angle));
		// imag = sin(angle) * coeff
		SpElement p_imag = mul(coeff, sinRadian(angle));
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (x_cplx) {
		//==  ANY ^ COMPLEX  ==//
		auto a = p_ey;
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		SpElement t = isPositive(a) ? GEN_INTEGER(0) : pi();
		SpElement r = abs(a);
		// angle = c*t + d*ln(r)
		SpElement angle = add(
			mul(c, t),
			mul(d, loge(r))
		);
		// coeff = r^c * exp(-d*t)
		SpElement coeff = mul(
			pow(r, c),
			exp(mul(neg(d), t))
		);
		// real = coeff * cos(angle)
		SpElement p_real = mul(coeff, cosRadian(angle));
		// imag = coeff * sin(angle)
		SpElement p_imag = mul(coeff, sinRadian(angle));
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
