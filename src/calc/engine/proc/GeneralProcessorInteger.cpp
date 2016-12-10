#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / INCREMENT
// [ description ]
// INCREMENT integer
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::inc(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
	case Element::INTEGER: {
			//===  inc(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (int_x != std::numeric_limits<integer_t>::max()) {
				++int_x;
				setInteger(p_etemp, int_x);
			}
			else {
				throw InvalidValue("MAX_INT", __FUNCTION__);
			}
			break;
		}
		case Element::BOOLEAN: {
			//===  inc(BINARY8)  ===//
			p_etemp = GEN_BOOLEAN(true);
			break;
		}
		case Element::BINARY8: {
			//===  inc(BINARY8)  ===//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			++byte_x;
			p_etemp = GEN_BYTE(byte_x);
			break;
		}
		case Element::BINARY16: {
			//===  inc(BINARY16)  ===//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			++word_x;
			p_etemp = GEN_WORD(word_x);
			break;
		}
		case Element::BINARY32: {
			//===  inc(BINARY32)  ===//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			++dword_x;
			p_etemp = GEN_DWORD(dword_x);
			break;
		}
		case Element::BINARY64: {
			//===  inc(BINARY64)  ===//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			++qword_x;
			p_etemp = GEN_QWORD(qword_x);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DECREMENT
// [ description ]
// DECREMENT integer
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::dec(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  dec(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (int_x != std::numeric_limits<integer_t>::min()) {
				--int_x;
				setInteger(p_etemp, int_x);
			}
			else {
				throw InvalidValue("MIN_INT", __FUNCTION__);
			}
			break;
		}
		case Element::BINARY8: {
			//===  dec(BINARY8)  ===//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			--byte_x;
			p_etemp = GEN_BYTE(byte_x);
			break;
		}
		case Element::BINARY16: {
			//===  dec(BINARY16)  ===//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			--word_x;
			p_etemp = GEN_WORD(word_x);
			break;
		}
		case Element::BINARY32: {
			//===  dec(BINARY32)  ===//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			--dword_x;
			p_etemp = GEN_DWORD(dword_x);
			break;
		}
		case Element::BINARY64: {
			//===  dec(BINARY64)  ===//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			--qword_x;
			p_etemp = GEN_QWORD(qword_x);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / GCD
// [ description ]
// GCD for 2 integers
// [ Update ]
// Jan 29, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::gcd(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
		//===  gcd(INTEGER, INTEGER)  ===//
		if (isPositive(p_ey) && isPositive(p_ex)) {
			SpElement m;
			SpElement n;
			SpElement temp;
			if (isPositive(sub(p_ey, p_ex))) {
				m = p_ex->clone();
				n = p_ey->clone();
			}
			else {
				m = p_ey->clone();
				n = p_ex->clone();
			}
			while (!isZero(n)) {
				temp = n;
				n = mod(m, n);
				m = temp;
			}
			p_etemp = m;
		}
		else {
			throw BadArgument("BAD_VAL", __FUNCTION__);
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / LCM
// [ description ]
// LCM for 2 integers
// [ Update ]
// Jan 29, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::lcm(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
		//===  lcm(INTEGER, INTEGER)  ===//
		if (isPositive(p_ey) && isPositive(p_ex)) {
			SpElement m;
			SpElement n;
			SpElement temp;
			if (isPositive(sub(p_ey, p_ex))) {
				m = p_ex->clone();
				n = p_ey->clone();
			}
			else {
				m = p_ey->clone();
				n = p_ex->clone();
			}
			while (!isZero(n)) {
				temp = n;
				n = mod(m, n);
				m = temp;
			}
			p_etemp = mul(div(p_ey, m), p_ex);
		}
		else {
			throw BadArgument("BAD_VAL", __FUNCTION__);
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / FACTORIAL
// [ description ]
// Get factorial of integer
// [ Update ]
// Jan 29, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::fact(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::INTEGER)) {
		//===  fact(INTEGER)  ===//
		integer_t int_x = GET_INTEGER_DATA(p_ex);
		if (int_x < 0) {
			throw InvalidValue("BAD_VAL", __FUNCTION__);
		}
		else {
			integer_t mult = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_INTEGER(1);
			// fact(0) = 1
			// fact(1) = 1
			setExceptions(FLT_OVERFLOW);
			try {
				while (mult) {
					SpElement multipler = GEN_INTEGER(mult);
					p_etemp = mul(p_etemp, multipler);
					--mult;
				}
			}
			catch (FlagException &) {
				resetExceptions();
				throw BadArgument("TOO_LRGE" , __FUNCTION__);
			}
			resetExceptions();
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / PERMUTATION
// [ description ]
// PERMUTATION for 2 integers
// [ Update ]
// Jan 29, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::perm(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
		//===  perm(INTEGER, INTEGER)  ===//
		integer_t int_y = GET_INTEGER_DATA(p_ey);
		integer_t int_x = GET_INTEGER_DATA(p_ex);
		if ((int_y >= int_x) && (int_y > 0) && (int_x > -1)) {
			integer_t r = int_x;
			p_etemp = GEN_INTEGER(1);
			setExceptions(FLT_OVERFLOW);
			try {
				integer_t mult = int_y;
				while (r) {
					SpElement multipler = GEN_INTEGER(mult);
					p_etemp = mul(p_etemp, multipler);
					--mult;
					--r;
				}
			}
			catch (FlagException &) {
				resetExceptions();
				throw BadArgument("TOO_LRGE" , __FUNCTION__);
			}
			resetExceptions();
		}
		else {
			throw InvalidValue("BAD_VAL", __FUNCTION__);
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / COMBINATION
// [ description ]
// COMBINATION for 2 integers
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::comb(const SpElement &p_ey, const SpElement &p_ex) {
	return div(perm(p_ey, p_ex), fact(p_ex));
}

} // namespace engine
