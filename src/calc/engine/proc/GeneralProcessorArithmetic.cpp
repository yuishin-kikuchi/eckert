#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ADD
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::add(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	try {
		p_etemp = addScalar(p_ey, p_ex);
	}
	catch (BadArgument &) {
		if (p_ey->isType(Element::ERROR) || p_ex->isType(Element::ERROR)) {
			setError(p_etemp, "ERROR");
		}
		else if (p_ey->isKindOf(Element::SET_TYPE) || p_ex->isKindOf(Element::SET_TYPE)) {
			p_etemp = addSet(p_ey, p_ex);
		}
		else if (p_ey->isType(Element::COMPLEX) || p_ex->isType(Element::COMPLEX)) {
			p_etemp = addComplex(p_ey, p_ex);
		}
		else {
			p_etemp = addBinary(p_ey, p_ex);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SUBTRACT
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::sub(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	try {
		p_etemp = subScalar(p_ey, p_ex);
	}
	catch (BadArgument &) {
		if (p_ey->isType(Element::ERROR) || p_ex->isType(Element::ERROR)) {
			setError(p_etemp, "ERROR");
		}
		else if (p_ey->isKindOf(Element::SET_TYPE) || p_ex->isKindOf(Element::SET_TYPE)) {
			p_etemp = subSet(p_ey, p_ex);
		}
		else if (p_ey->isType(Element::COMPLEX) || p_ex->isType(Element::COMPLEX)) {
			p_etemp = subComplex(p_ey, p_ex);
		}
		else {
			p_etemp = subBinary(p_ey, p_ex);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MULTIPLY
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mul(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	try {
		p_etemp = mulScalar(p_ey, p_ex);
	}
	catch (InvalidValue &) {
		throw;
	}
	catch (BadArgument &) {
		if (p_ey->isType(Element::ERROR) || p_ex->isType(Element::ERROR)) {
			setError(p_etemp, "ERROR");
		}
		else if (p_ey->isKindOf(Element::SET_TYPE) || p_ex->isKindOf(Element::SET_TYPE)) {
			p_etemp = mulSet(p_ey, p_ex);
		}
		else if (p_ey->isType(Element::COMPLEX) || p_ex->isType(Element::COMPLEX)) {
			p_etemp = mulComplex(p_ey, p_ex);
		}
		else {
			p_etemp = mulBinary(p_ey, p_ex);
		}
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DIVIDE
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::div(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	try {
		p_etemp = divScalar(p_ey, p_ex);
	}
	catch (InvalidValue &) {
		throw;
	}
	catch (BadArgument &) {
		if (p_ey->isType(Element::ERROR) || p_ex->isType(Element::ERROR)) {
			setError(p_etemp, "ERROR");
		}
		else if (p_ey->isKindOf(Element::SET_TYPE) || p_ex->isKindOf(Element::SET_TYPE)) {
			p_etemp = divSet(p_ey, p_ex);
		}
		else if (p_ey->isType(Element::COMPLEX) || p_ex->isType(Element::COMPLEX)) {
			p_etemp = divComplex(p_ey, p_ex);
		}
		else {
			p_etemp = divBinary(p_ey, p_ex);
		}
	}
	return p_etemp;
}

} // namespace engine
