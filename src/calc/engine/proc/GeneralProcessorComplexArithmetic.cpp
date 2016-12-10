#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ADD
// [ description ]
// ADD function for 2 complex numbers
// (a + ib) + (c + id) = (a + c) + i(b + d)
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::addComplex(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	bool y_cplx = p_ey->isType(Element::COMPLEX);
	bool x_cplx = p_ex->isType(Element::COMPLEX);
	if (y_cplx && x_cplx) {
		//==  COMPLEX + COMPLEX  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// real = a + c
		p_real = addScalar(a, c);
		// imag = b + d
		p_imag = addScalar(b, d);
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (y_cplx) {
		//==  COMPLEX + ANY  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = p_ex;
		// real = a + c
		p_real = addScalar(a, c);
		// imag = b
		p_imag = b->clone();
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (x_cplx) {
		//==  ANY + COMPLEX  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = p_ey;
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// real = a + c
		p_real = addScalar(a, c);
		// imag = d
		p_imag = d->clone();
		setComplex(p_etemp, p_real, p_imag);
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SUBTRACT
// [ description ]
// Subtract function for 2 complex numbers
// (a + ib) - (c + id) = (a - c) + i(b - d)
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::subComplex(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	bool y_cplx = p_ey->isType(Element::COMPLEX);
	bool x_cplx = p_ex->isType(Element::COMPLEX);
	if (y_cplx && x_cplx) {
		//==  Complex - Complex  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// real = a - c
		p_real = subScalar(a, c);
		// imag = b - d
		p_imag = subScalar(b, d);
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (y_cplx) {
		//==  Complex - ANY  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = p_ex;
		// real = a - c
		p_real = subScalar(a, c);
		// imag = b
		p_imag = b->clone();
		// optimize complex
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (x_cplx) {
	//==  ANY - Complex  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = p_ey;
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// real = a - c
		p_real = subScalar(a, c);
		// imag = -d
		p_imag = neg(d);
		setComplex(p_etemp, p_real, p_imag);
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MULTIPLY
// [ description ]
// MULTIPLY function for 2 complex numbers
// (a + ib) * (c + id) = (ac - bd) + i(ad + bc)
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mulComplex(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	bool y_cplx = p_ey->isType(Element::COMPLEX);
	bool x_cplx = p_ex->isType(Element::COMPLEX);
	if (y_cplx && x_cplx) {
		//==  COMPLEX * COMPLEX  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// real = (ac - bd)
		p_real = subScalar(
			mulScalar(a, c), mulScalar(b, d)
		);
		// imag = (ad + bc)
		p_imag = addScalar(
			mulScalar(a, d), mulScalar(b, c)
		);
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (y_cplx) {
		//==  COMPLEX * ANY  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = p_ex;
		// real = ac
		p_real = mulScalar(a, c);
		// imag = bc
		p_imag = mulScalar(b, c);
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (x_cplx) {
		//==  ANY * COMPLEX  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = p_ey;
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// real = ac
		p_real = mulScalar(a, c);
		// imag = ad
		p_imag = mulScalar(a, d);
		setComplex(p_etemp, p_real, p_imag);
	}
	else {
		//==  Unexpected  ==//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DIVIDE
// [ description ]
// DIVIDE function for 2 complex numbers
// (a + ib) / (c + id) = ((ac + bd) / sq) + i((bc - ad) / sq)
// sq = c^2 + d^2
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::divComplex(const SpElement &p_ey, const SpElement &p_ex) {
	// check division by zero
	if (isZero(p_ex)) {
		throw InvalidValue("DIV_ZERO", __FUNCTION__);
	}
	else if (isZero(p_ey)) {
		return p_ey;
	}
	SpElement p_etemp;
	bool y_cplx = p_ey->isType(Element::COMPLEX);
	bool x_cplx = p_ex->isType(Element::COMPLEX);
	if (y_cplx && x_cplx) {
		//==  COMPLEX / COMPLEX  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// sq = c^2 + d^2
		p_etemp = addScalar(
			mulScalar(c, c), mulScalar(d, d)
		);
		// real = (ac + bd) / sq
		p_real = addScalar(
			mulScalar(a, c), mulScalar(b, d)
		);
		p_real = divScalar(p_real, p_etemp);
		// imag = (bc - ad) / sq
		p_imag = subScalar(
			mulScalar(b, c), mulScalar(a, d)
		);
		p_imag = divScalar(p_imag, p_etemp);
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (y_cplx) {
		//==  COMPLEX / ANY  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = GET_COMPLEX_RE(p_ey);
		auto b = GET_COMPLEX_IM(p_ey);
		auto c = p_ex;
		// real = a/c
		p_real = divScalar(a, c);
		// imag = b/c
		p_imag = divScalar(b, c);
		setComplex(p_etemp, p_real, p_imag);
	}
	else if (x_cplx) {
		//==  ANY / COMPLEX  ==//
		SpElement p_real;
		SpElement p_imag;
		auto a = p_ey;
		auto c = GET_COMPLEX_RE(p_ex);
		auto d = GET_COMPLEX_IM(p_ex);
		// sq = c^2 + d^2
		p_etemp = addScalar(
			mulScalar(c, c), mulScalar(d, d)
		);
		// real = ac / sq
		p_real = divScalar(
			mulScalar(a, c), p_etemp
		);
		// imag = -ad / sq
		p_imag = neg(
			divScalar(mulScalar(a, d), p_etemp)
		);
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
