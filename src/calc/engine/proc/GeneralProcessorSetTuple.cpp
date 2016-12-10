#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / INNER PRODUCT
// [ description ]
// INNER PRODUCT function for 2 tuples
// [ Update ]
// Jun 08, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::innerProduct(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::ETUPLE) && p_ex->isType(Element::ETUPLE)) {
		//==  Inner_prod(ETUPLE, ETUPLE)  ==//
		std::size_t y_size = GET_ETUPLE_SIZE(p_ey);
		std::size_t x_size = GET_ETUPLE_SIZE(p_ex);
		if (y_size == x_size) {
			if (0 == y_size) {
				throw BadArgument("BAD_TSIZ", __FUNCTION__);
			}
			setExceptions(FLT_OVERFLOW);
			try {
				const auto &yf = GET_ETUPLE_DATA(p_ey, 0);
				const auto &xf = GET_ETUPLE_DATA(p_ex, 0);
				SpElement conj_xf;
				try {
					conj_xf = conj(xf);
				}
				catch (BadArgument &) {
					conj_xf = xf;
				}
				SpElement elm = mul(yf, conj_xf);
				for (std::size_t ucnt = 1; ucnt < y_size; ++ucnt) {
					const auto &y = GET_ETUPLE_DATA(p_ey, ucnt);
					const auto &x = GET_ETUPLE_DATA(p_ex, ucnt);
					SpElement conj_x;
					try {
						conj_x = conj(x);
					}
					catch (BadArgument &) {
						conj_x = x;
					}
					elm = add(elm, mul(y, conj_x));
				}
				p_etemp = elm;
			}
			catch (FlagException &) {
				resetExceptions();
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			catch (...) {
				resetExceptions();
				throw;
			}
			resetExceptions();
		}
		else {
			throw BadArgument("BAD_TSIZ", __FUNCTION__);
		}
	}
	else {
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / OUTER PRODUCT
// [ description ]
// OUTER PRODUCT function for 2 tuples
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::outerProduct(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ey->isType(Element::ETUPLE) && p_ex->isType(Element::ETUPLE)) {
		//==  Outer_prod(ETUPLE, ETUPLE)  ==//
		std::size_t y_size = GET_ETUPLE_SIZE(p_ey);
		std::size_t x_size = GET_ETUPLE_SIZE(p_ex);
		auto y_ttype = GET_ETUPLE_TYPE(p_ey);
		auto x_ttype = GET_ETUPLE_TYPE(p_ex);
		if ((3 == y_size) && (3 == x_size) && (y_ttype == x_ttype)) {
			const auto &vec_y = CAST_INTO_ETUPLE(p_ey)->getVector();
			const auto &vec_x = CAST_INTO_ETUPLE(p_ex)->getVector();
			std::vector<SpElement> tuple;
			tuple.resize(3);
			setExceptions(FLT_OVERFLOW);
			try {
				tuple.at(0) = sub(mul(vec_y.at(1), vec_x.at(2)), mul(vec_x.at(1), vec_y.at(2)));
				tuple.at(1) = sub(mul(vec_x.at(0), vec_y.at(2)), mul(vec_y.at(0), vec_x.at(2)));
				tuple.at(2) = sub(mul(vec_y.at(0), vec_x.at(1)), mul(vec_x.at(0), vec_y.at(1)));
				p_etemp = GEN_ETUPLE2(tuple, GET_ETUPLE_TYPE(p_ey));
			}
			catch (FlagException &) {
				resetExceptions();
				throw InvalidValue("TOO_LRGE", __FUNCTION__);
			}
			catch (...) {
				resetExceptions();
				throw;
			}
			resetExceptions();
		}
		else {
			throw BadArgument("BAD_TSIZ", __FUNCTION__);
		}
	}
	else {
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / NORM
// [ description ]
// NORM for complex or tuple
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::norm(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::COMPLEX: {
			//===  norm(COMPLEX)  ===//
			p_etemp = abs(p_ex);
			break;
		}
		case Element::ETUPLE: {
			//===  norm(ETUPLE)  ===//
			p_etemp = sqrt(innerProduct(p_ex, p_ex));
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SQUARED NORM
// [ description ]
// SQUARED NORM for complex or tuple
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::normSq(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::COMPLEX: {
			//===  normsq(COMPLEX)  ===//
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			p_etemp = add(mul(a, a), mul(b, b));
			break;
		}
		case Element::ETUPLE: {
			//===  normsq(ETUPLE)  ===//
			p_etemp = innerProduct(p_ex, p_ex);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / Lp-norm
// [ description ]
// Lp-norm for tuple
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::lpNorm(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ey->getType()) {
	case Element::ETUPLE: {
		//===  lpnorm(ETUPLE, ???)  ===//
		switch (p_ex->getType()) {
			case Element::INTEGER: {
				//==  lpnorm(ETUPLE, INTEGER)  ==//
				std::size_t size = GET_ETUPLE_SIZE(p_ey);
				auto itemp = GET_INTEGER_DATA(p_ex);
				if (itemp < 1) {
					throw BadArgument("BAD_VAL");
				}
				p_etemp = GEN_INTEGER(0);
				setExceptions(FLT_OVERFLOW);
				try {
					for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
						const auto &y = GET_ETUPLE_DATA(p_ey, ucnt);
						p_etemp = add(p_etemp, nthPow(y, p_ex));
					}
					p_etemp = nthRoot(p_etemp, p_ex);
				}
				catch (FlagException &) {
					resetExceptions();
					throw InvalidValue("TOO_LRGE", __FUNCTION__);
				}
				catch (...) {
					resetExceptions();
					throw;
				}
				resetExceptions();
				break;
			}
			default:
				//==  lpnorm(ETUPLE, Unexpected)  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		}
		default:
			//===  Unexpected, ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MAX NORM
// [ description ]
// MAX NORM for tuple
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::maxNorm(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
	case Element::ETUPLE: {
		//===  maxnorm(ETUPLE)  ===//
		SpElement &p_max = p_etemp;
		p_max = GEN_INTEGER(-1);
		std::size_t size = GET_ETUPLE_SIZE(p_ex);
		for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
			const auto &x = GET_ETUPLE_DATA(p_ex, ucnt);
			const auto temp = abs(x);
			if (isNegative(sub(p_max, temp))) {
				p_max = abs(x);
			}
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
