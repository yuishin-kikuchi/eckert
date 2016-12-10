#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DETERMINANT
// [ description ]
// Get determinant
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::determinant(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::MATRIX)) {
		if (CAST_INTO_MATRIX(p_ex)->isSquareMatrix()) {
			const std::size_t size = GET_MATRIX_SIZE_M(p_ex);
			const auto &matrix = GET_MATRIX_RAW(p_ex);
			switch (size) {
			case 0:
				//==  0x0  ==//
				throw TechnicalError("Zero-size matrix", __FUNCTION__);
			case 1: {
				//==  1x1  ==//
				p_etemp = matrix.at(0).at(0);
				break;
			}
			case 2: {
				//==  2x2  ==//
				const auto& a = matrix.at(0).at(0);
				const auto& b = matrix.at(0).at(1);
				const auto& c = matrix.at(1).at(0);
				const auto& d = matrix.at(1).at(1);
				p_etemp = sub(mul(a, d), mul(b, c));
				break;
			}
			case 3: {
				//==  3x3  ==//
				const auto& a = matrix.at(0).at(0);
				const auto& b = matrix.at(0).at(1);
				const auto& c = matrix.at(0).at(2);
				const auto& d = matrix.at(1).at(0);
				const auto& e = matrix.at(1).at(1);
				const auto& f = matrix.at(1).at(2);
				const auto& g = matrix.at(2).at(0);
				const auto& h = matrix.at(2).at(1);
				const auto& i = matrix.at(2).at(2);
				p_etemp = mul(a, mul(e, i));
				p_etemp = add(p_etemp, mul(b, mul(f, g)));
				p_etemp = add(p_etemp, mul(c, mul(d, h)));
				p_etemp = sub(p_etemp, mul(a, mul(f, h)));
				p_etemp = sub(p_etemp, mul(b, mul(d, i)));
				p_etemp = sub(p_etemp, mul(c, mul(e, g)));
				break;
			}
			default: {
				//==  bigger  ==//
				SpElement det = GEN_INTEGER(1);
				std::vector<std::vector<SpElement>> upper;
				upper.resize(size);
				for (std::size_t scan_y = 0; scan_y < size; ++scan_y) {
					// copy matrix
					const auto &mvec = matrix.at(scan_y);
					auto &vec = upper.at(scan_y);
					vec.resize(size);
					for (std::size_t scan_x = 0; scan_x < size; ++scan_x) {
						vec.at(scan_x) = mvec.at(scan_x);
					}
				}
				for (std::size_t scan_y = 0; scan_y < size; ++scan_y) {
					if (isZero(upper.at(scan_y).at(scan_y))) {
						bool det_zero = true;
						for (std::size_t ucnt = scan_y + 1; ucnt < size; ++ucnt) {
							if (!isZero(upper.at(ucnt).at(scan_y))) {
								// swap row tuple
								upper.at(scan_y).swap(upper.at(ucnt));
								det = neg(det);
								det_zero = false;
							}
						}
						if (det_zero) {
							break;
						}
					}
					for (std::size_t scan_x = 0; scan_x < size; ++scan_x) {
						if (scan_y < scan_x) {
							SpElement buf
							 = div(upper.at(scan_x).at(scan_y), upper.at(scan_y).at(scan_y));
							for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
								auto &temp_y = upper.at(scan_x).at(ucnt);
								auto temp_x = mul(upper.at(scan_y).at(ucnt), buf);
								temp_y = sub(temp_y, temp_x);
							}
						}
					}
				}
				for (std::size_t ucnt = 0; ucnt < size; ucnt++) {
					det = mul(det, upper.at(ucnt).at(ucnt));
				}
				if (checkFlags(FLT_OVERFLOW)) {
					throw InvalidValue("TOO_LRGE", __FUNCTION__);
				}
				p_etemp = det;
				break;
			} // end of default (bigger than 3x3)
			} // end of switch
		}
		else {
			throw BadArgument("BAD_MSIZ", __FUNCTION__);
		}
	}
	else {
		//===  Unexpected  ===//
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / INVERT
// [ description ]
// INVERT
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::invMatrix(const SpElement &p_ex) {
	SpElement p_etemp;
	if (p_ex->isType(Element::MATRIX)) {
		if (CAST_INTO_MATRIX(p_ex)->isSquareMatrix()) {
			const std::size_t size = GET_MATRIX_SIZE_M(p_ex);
			const auto &matrix = GET_MATRIX_RAW(p_ex);
			std::vector<std::vector<SpElement>> inverted;
			inverted.resize(size);
			for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
				auto &vec = inverted.at(ucnt);
				vec.resize(size);
			}
			switch (size) {
			case 0:
				//==  0x0  ==//
				throw TechnicalError("Zero-size matrix", __FUNCTION__);
			case 1: {
				//==  1x1  ==//
				if (isZero(matrix.at(0).at(0))) {
					throw BadArgument("DET_ZERO", __FUNCTION__);
				}
				else {
					inverted.at(0).at(0) = inv(matrix.at(0).at(0));
				}
				break;
			}
			case 2: {
				//==  2x2  ==//
				SpElement delta = determinant(p_ex);
				if (isZero(delta)) {
					throw BadArgument("DET_ZERO", __FUNCTION__);
				}
				else {
					setExceptions(FLT_OVERFLOW);
					try {
						const auto& a = matrix.at(0).at(0);
						const auto& b = matrix.at(0).at(1);
						const auto& c = matrix.at(1).at(0);
						const auto& d = matrix.at(1).at(1);
						inverted.at(0).at(0) = div(d, delta);
						inverted.at(0).at(1) = div(neg(b), delta);
						inverted.at(1).at(0) = div(neg(c), delta);
						inverted.at(1).at(1) = div(a, delta);
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
				break;
			}
			case 3: {
				//==  3x3  ==//
				SpElement delta = determinant(p_ex);
				if (isZero(delta)) {
					throw BadArgument("DET_ZERO", __FUNCTION__);
				}
				else {
					setExceptions(FLT_OVERFLOW);
					try {
						const auto& a = matrix.at(0).at(0);
						const auto& b = matrix.at(0).at(1);
						const auto& c = matrix.at(0).at(2);
						const auto& d = matrix.at(1).at(0);
						const auto& e = matrix.at(1).at(1);
						const auto& f = matrix.at(1).at(2);
						const auto& g = matrix.at(2).at(0);
						const auto& h = matrix.at(2).at(1);
						const auto& i = matrix.at(2).at(2);
						inverted.at(0).at(0) = div(sub(mul(e, i), mul(f, h)), delta);
						inverted.at(0).at(1) = div(sub(mul(h, c), mul(i, b)), delta);
						inverted.at(0).at(2) = div(sub(mul(b, f), mul(c, e)), delta);
						inverted.at(1).at(0) = div(sub(mul(g, f), mul(d, i)), delta);
						inverted.at(1).at(1) = div(sub(mul(a, i), mul(g, c)), delta);
						inverted.at(1).at(2) = div(sub(mul(d, c), mul(a, f)), delta);
						inverted.at(2).at(0) = div(sub(mul(d, h), mul(g, e)), delta);
						inverted.at(2).at(1) = div(sub(mul(g, b), mul(a, h)), delta);
						inverted.at(2).at(2) = div(sub(mul(a, e), mul(d, b)), delta);
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
				break;
			}
			default: {
				//==  bigger  ==//
				std::vector<std::vector<SpElement>> tmat;
				inverted.resize(size);
				tmat.resize(size);
				SpElement buf;
				setExceptions(FLT_OVERFLOW);
				try {
					// copy matrix and generate unit matrix
					for (std::size_t scan_y = 0; scan_y < size; ++scan_y) {
						const auto &mvec = matrix.at(scan_y);
						auto &vec = tmat.at(scan_y);
						auto &unit = inverted.at(scan_y);
						vec.resize(size);
						unit.resize(size);
						for (std::size_t scan_x = 0; scan_x < size; ++scan_x) {
							// copy matrix to tmat
							vec.at(scan_x) = mvec.at(scan_x);
							// generate unit matrix
							unit.at(scan_x) = (scan_y == scan_x) ? (GEN_INTEGER(1)) : (GEN_INTEGER(0));
						}
					}
					// swipe out method
					for (std::size_t scan_y = 0; scan_y < size; ++scan_y) {
						// check det is not zero
						if (isZero(tmat.at(scan_y).at(scan_y))) {
							bool det_zero = true;
							for (std::size_t ucnt = scan_y + 1; ucnt < size; ++ucnt) {
								if (!isZero(tmat.at(ucnt).at(scan_y))) {
									// swap row tuple
									tmat.at(scan_y).swap(tmat.at(ucnt));
									inverted.at(scan_y).swap(inverted.at(ucnt));
									det_zero = false;
								}
							}
							if (det_zero) {
								throw InvalidValue("DET_ZERO", __FUNCTION__);
							}
						}
						// normalize
						buf = tmat.at(scan_y).at(scan_y);
						for (std::size_t scan_x = 0; scan_x < size; ++scan_x) {
							auto &temp_m = tmat.at(scan_y).at(scan_x);
							auto &temp_i = inverted.at(scan_y).at(scan_x);
							temp_m = div(temp_m, buf);
							temp_i = div(temp_i, buf);
						}
						// swipe
						for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
							if (scan_y != ucnt) {
								buf = tmat.at(ucnt).at(scan_y);
								for (std::size_t scan_x = 0; scan_x < size; ++scan_x) {
									// subtract
									auto &temp_m = tmat.at(ucnt).at(scan_x);
									auto &temp_i = inverted.at(ucnt).at(scan_x);
									temp_m = sub(temp_m, mul(tmat.at(scan_y).at(scan_x), buf));
									temp_i = sub(temp_i, mul(inverted.at(scan_y).at(scan_x), buf));
								}
							}
						}
					}
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
			} // end of bigger
			} // end of switch
			p_etemp = GEN_MATRIX(inverted);
		}
		else {
			throw BadArgument("BAD_MSIZ", __FUNCTION__);
		}
	}
	else {
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / TRACE
// [ description ]
// TRACE for matrix
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::trace(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	if (p_ex->isType(Element::MATRIX)) {
		if (CAST_INTO_MATRIX(p_ex)->isSquareMatrix()) {
			const std::size_t size = GET_MATRIX_SIZE_M(p_ex);
			p_etemp = GEN_INTEGER(0);
			for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
				p_etemp = add(p_etemp, GET_MATRIX_DATA(p_ex, ucnt, ucnt));
			}
		}
		else {
			throw BadArgument("BAD_MSIZ", __FUNCTION__);
		}
	}
	else {
		throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / TRANSPOSE
// [ description ]
// TRANSPOSE for matrix
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::transpose(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::MATRIX: {
			//===  t(MATRIX)  ===//
			const std::size_t size_m = GET_MATRIX_SIZE_M(p_ex);
			const std::size_t size_n = GET_MATRIX_SIZE_N(p_ex);
			std::vector<std::vector<SpElement>> mat;
			mat.resize(size_n);
			for (std::size_t scan_y = 0; scan_y < size_n; ++scan_y) {
				auto &vec = mat.at(scan_y);
				vec.resize(size_m);
				for (std::size_t scan_x = 0; scan_x < size_m; ++scan_x) {
					vec.at(scan_x) = GET_MATRIX_DATA(p_ex, scan_x, scan_y);
				}
				p_etemp = GEN_MATRIX(mat);
			}
			break;
		}
		case Element::ETUPLE: {
			//===  t(ETUPLE)  ===//
			switch (GET_ETUPLE_TYPE(p_ex)) {
				case ETuple::TupleType::ROW:
					p_etemp = GEN_ETUPLE2(CAST_INTO_ETUPLE(p_ex)->getVector(), ETuple::TupleType::COLUMN);
					break;
				case ETuple::TupleType::COLUMN:
					p_etemp = GEN_ETUPLE2(CAST_INTO_ETUPLE(p_ex)->getVector(), ETuple::TupleType::ROW);
					break;
				default:
					throw TechnicalError("Unknown tuple type", __FUNCTION__);
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
// ECKERT PROCESSOR / HERMITIAN TRANSPOSE
// [ description ]
// HERMITIAN TRANSPOSE for matrix
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::hermitianTranspose(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::MATRIX: {
			//===  th(MATRIX)  ===//
			const std::size_t size_m = GET_MATRIX_SIZE_M(p_ex);
			const std::size_t size_n = GET_MATRIX_SIZE_N(p_ex);
			std::vector<std::vector<SpElement>> mat;
			mat.resize(size_n);
			for (std::size_t scan_y = 0; scan_y < size_n; ++scan_y) {
				auto &vec = mat.at(scan_y);
				vec.resize(size_m);
				for (std::size_t scan_x = 0; scan_x < size_m; ++scan_x) {
					vec.at(scan_x) = conj(GET_MATRIX_DATA(p_ex, scan_x, scan_y));
				}
				p_etemp = GEN_MATRIX(mat);
			}
			break;
		}
		case Element::ETUPLE: {
			//===  th(ETUPLE)  ===//
			switch (GET_ETUPLE_TYPE(p_ex)) {
				case ETuple::TupleType::ROW: {
					std::vector<SpElement> tvec = CAST_INTO_ETUPLE(p_ex)->getVector();
					for (auto &&x : tvec) {
						x = conj(x);
					}
					p_etemp = GEN_ETUPLE2(tvec, ETuple::TupleType::COLUMN);
					break;
				}
				case ETuple::TupleType::COLUMN: {
					std::vector<SpElement> tvec = CAST_INTO_ETUPLE(p_ex)->getVector();
					for (auto &&x : tvec) {
						x = conj(x);
					}
					p_etemp = GEN_ETUPLE2(tvec, ETuple::TupleType::ROW);
					break;
				}
				default:
					throw TechnicalError("Unknown tuple type", __FUNCTION__);
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
