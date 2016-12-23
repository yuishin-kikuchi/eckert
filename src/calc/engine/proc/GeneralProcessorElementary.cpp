#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / NEGATE
// [ description ]
// NEGATE value for scalar
// [ Update ]
// Oct 07, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::neg(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  neg(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (!SafetyIntegerCalculator::checkNeg(int_x)) {
				setInteger(p_etemp, -int_x);
			}
			else {
				floating_t ftemp = (floating_t)int_x;
				setFlags(GeneralProcessor::INT_OVERFLOW);
				setFloating(p_etemp, -ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  neg(FLOATING)  ===//
			floating_t ftemp = GET_FLOATING_DATA(p_ex);
			setFloating(p_etemp, -ftemp);
			break;
		}
		case Element::RATIONAL: {
			//===  neg(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			if (rat_x.isError()) {
				setError(p_etemp, "NAN");
			}
			else {
				rational_t rtemp = -rat_x;
				if (!rtemp.isError()) {
					setRational(p_etemp, rtemp);
				}
				else {
					floating_t ftemp = -rat_x.getFloating();
					setFlags(GeneralProcessor::RAT_OVERFLOW);
					setFloating(p_etemp, ftemp);
				}
				break;
			}
			break;
		}
		case Element::COMPLEX :{
			//==  neg(COMPLEX)  ==//
			SpElement p_real = neg(GET_COMPLEX_RE(p_ex));
			SpElement p_imag = neg(GET_COMPLEX_IM(p_ex));
			setComplex(p_etemp, p_real, p_imag);
			break;
		}
		case Element::EINFINITY: {
			//===  neg(EINFINITY)  ===//
			int sign = GET_EINFINITY_DATA(p_ex);
			setInfinity(p_etemp, -sign);
			break;
		}
		case Element::BINARY8: {
			//==  neg(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BYTE(~byte_x + 1);
			break;
		}
		case Element::BINARY16: {
			//==  neg(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(~word_x + 1);
			break;
		}
		case Element::BINARY32: {
			//==  neg(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(~dword_x + 1);
			break;
		}
		case Element::BINARY64: {
			//==  neg(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(~qword_x + 1);
			break;
		}
		case Element::ETUPLE: {
			//==  neg(ETUPLE)  ==//
			const auto &vec = GET_ETUPLE_RAW(p_ex);
			auto ttype = GET_ETUPLE_TYPE(p_ex);
			std::size_t len = vec.size();
			std::vector<SpElement> dst(len);
			for (std::size_t pos = 0; pos < len; ++pos) {
				dst.at(pos) = neg(vec.at(pos));
			}
			p_etemp = GEN_ETUPLE2(dst, ttype);
			break;
		}
		case Element::MATRIX: {
			//==  neg(MATRIX)  ==//
			std::size_t size_m = GET_MATRIX_SIZE_M(p_ex);
			std::size_t size_n = GET_MATRIX_SIZE_N(p_ex);
			std::vector<std::vector<SpElement>> mat;
			mat.resize(size_m);
			for (std::size_t scan_y = 0; scan_y < size_m; ++scan_y) {
				const auto &vec = CAST_INTO_MATRIX(p_ex)->getVector(scan_y);
				auto &row = mat.at(scan_y);
				row.resize(size_n);
				for (std::size_t scan_x = 0; scan_x < size_n; ++scan_x) {
					row.at(scan_x) = neg(vec.at(scan_x));
				}
			}
			p_etemp = GEN_MATRIX(mat);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ABSOLUTE
// [ description ]
// ABSOLUTE value for scalar
// [ Update ]
// Nov 12, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::abs(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  abs(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (!SafetyIntegerCalculator::checkNeg(int_x)) {
				if (int_x < 0) {
					setInteger(p_etemp, -int_x);
				}
				else {
					setInteger(p_etemp, int_x);
				}
			}
			else {
				setFlags(GeneralProcessor::INT_OVERFLOW);
				floating_t ftemp = (floating_t)int_x;
				setFloating(p_etemp, -ftemp);
			}
			break;
		}
		case Element::FLOATING: {
			//===  abs(FLOATING)  ===//
			floating_t ftemp = GET_FLOATING_DATA(p_ex);
			setFloating(p_etemp, std::abs(ftemp));
			break;
		}
		case Element::RATIONAL: {
			//===  abs(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			if (rat_x.isError()) {
				setError(p_etemp, "NAN");
			}
			else if (0 <= rat_x.getNum()) {
				setRational(p_etemp, rat_x);
			}
			else {
				rational_t rtemp = -rat_x;
				if (!rtemp.isError()) {
					setRational(p_etemp, rtemp);
				}
				else {
					floating_t ftemp = -rat_x.getFloating();
					setFlags(GeneralProcessor::RAT_OVERFLOW);
					setFloating(p_etemp, ftemp);
				}
			}
			break;
		}
		case Element::EINFINITY: {
			//===  abs(EINFINITY)  ===//
			setError(p_etemp, "NAN");
			break;
		}
		case Element::COMPLEX: {
			//===  abs(COMPLEX)  ===//
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			p_etemp = hypot(a, b);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / INVERT
// [ description ]
// INVERT value for scalar
// [ Update ]
// Dec 05, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::inv(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	if (isZero(p_ex)) {
		throw BadArgument("DIV_ZERO", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  inv(INTEGER)  ===//
			integer_t int_x = GET_INTEGER_DATA(p_ex);
			if (!SafetyIntegerCalculator::checkNeg(int_x)) {
				if (int_x < 0) {
					setRational(p_etemp, -1, -int_x);
				}
				else {
					setRational(p_etemp, 1, int_x);
				}
			}
			else {
				setFlags(GeneralProcessor::INT_OVERFLOW);
				setFloating(p_etemp, 1.0 / (floating_t)int_x);
			}
			break;
		}
		case Element::FLOATING: {
			//===  inv(FLOATING)  ===//
			floating_t flt_x = GET_FLOATING_DATA(p_ex);
			setFloating(p_etemp, 1.0 / flt_x);
			break;
		}
		case Element::RATIONAL: {
			//===  inv(RATIONAL)  ===//
			rational_t rat_x = GET_RATIONAL_DATA(p_ex);
			rational_t rtemp = rat_x.inv();
			if (!rtemp.isError()) {
				if (rtemp.isInteger()) {
					setInteger(p_etemp, rtemp.getNum());
				}
				else {
					setRational(p_etemp, rtemp);
				}
			}
			else {
				setFloating(p_etemp, 1.0 / rat_x.getFloating());
			}
			break;
		}
		case Element::EINFINITY: {
			//===  inv(EINFINITY)  ===//
			setInteger(p_etemp, 0);
			break;
		}
		case Element::COMPLEX: {
			//===  inv(COMPLEX)  ===//
			SpElement p_real;
			SpElement p_imag;
			auto a = GET_COMPLEX_RE(p_ex);
			auto b = GET_COMPLEX_IM(p_ex);
			// sq = a^2 + b^2
			p_etemp = addScalar(
				mulScalar(a, a),
				mulScalar(b, b)
			);
			// real = a / sq
			p_real = divScalar(a, p_etemp);
			// imag = -b / sq
			p_imag = neg(div(b, p_etemp));
			setComplex(p_etemp, p_real, p_imag);
			break;
		}
		case Element::MATRIX: {
			//===  inv(EINFINITY)  ===//
			p_etemp = invMatrix(p_ex);
			break;
		}
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CUBIC ROOT
// [ description ]
// CUBIC ROOT for scalar
// [ Update ]
// Apr 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::sqrt(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (isNegative(p_ex)) {
		setComplex(p_etemp, GEN_INTEGER(0), nthRoot(neg(p_ex), GEN_INTEGER(2)));
	}
	else {
		p_etemp = nthRoot(p_ex, GEN_INTEGER(2));
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CUBIC ROOT
// [ description ]
// CUBIC ROOT for scalar
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::cbrt(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//===  cbrt(INTEGER)  ===//
			p_etemp = nthRoot(p_ex, GEN_INTEGER(3));
			break;
		}
		case Element::FLOATING: {
			//===  cbrt(FLOATING)  ===//
				floating_t flt_x = GET_FLOATING_DATA(p_ex);
				floating_t dtemp = ::cbrt(flt_x);
				setFloating(p_etemp, dtemp);
			break;
		}
		case Element::RATIONAL: {
			//===  cbrt(RATIONAL)  ===//
			p_etemp = nthRoot(p_ex, GEN_INTEGER(3));
			break;
		}
		case Element::COMPLEX: {
			//===  cbrt(COMPLEX)  ===//
			p_etemp = nthRoot(p_ex, GEN_INTEGER(3));
			break;
		}
		default:
			//===  Unsupported  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / HYPOT
// [ description ]
// HYPOT function for 2 scalars
// [ Update ]
// Nov 12, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::hypot(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	//==   Scalar check  ==//
	if (!p_ey->isKindOf(Element::SCALAR_TYPE) || !p_ex->isKindOf(Element::SCALAR_TYPE)) {
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	SpElement insideRoot = add(square(p_ey), square(p_ex));
	SpElement p_etemp = sqrt(insideRoot);
	return p_etemp;
}

} // namespace engine
