#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ADD
// [ description ]
// ADD function for tuple, matrix or complex
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::addSet(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::ETUPLE:
		//===  ETUPLE + ???  ===//
			switch (x_type) {
				case Element::ETUPLE: {
					//==  ETUPLE + ETUPLE  ==//
					const std::size_t size_y = GET_ETUPLE_SIZE(p_ey);
					const std::size_t size_x = GET_ETUPLE_SIZE(p_ex);
					if (size_y == size_x) {
						std::vector<SpElement> tuple;
						tuple.resize(size_y);
						setExceptions(FLT_OVERFLOW);
						try {
							for (std::size_t ucnt = 0; ucnt < size_y; ++ucnt) {
								const auto &elm_y = GET_ETUPLE_DATA(p_ey, ucnt);
								const auto &elm_x = GET_ETUPLE_DATA(p_ex, ucnt);
								tuple.at(ucnt) = this->add(elm_y, elm_x);
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
						p_etemp = GEN_ETUPLE(tuple);
					}
					else {
						throw InvalidValue("BAD_TSIZ", __FUNCTION__);
					}
					break;
				}
				default:
					//==  ETUPLE + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::MATRIX:
			//===  MATRIX + ???  ===//
			switch (x_type) {
				case Element::MATRIX: {
					//==  MATRIX + MATRIX  ==//
					const std::size_t m_of_y = GET_MATRIX_SIZE_M(p_ey);
					const std::size_t n_of_y = GET_MATRIX_SIZE_N(p_ey);
					const std::size_t m_of_x = GET_MATRIX_SIZE_M(p_ex);
					const std::size_t n_of_x = GET_MATRIX_SIZE_N(p_ex);
					if ((m_of_y == m_of_x) && (n_of_y == n_of_x)) {
						std::vector<std::vector<SpElement>> mat;
						mat.resize(m_of_y);
						setExceptions(FLT_OVERFLOW);
						try {
							for (std::size_t scan_y = 0; scan_y < m_of_y; ++scan_y) {
								auto &tuple = mat.at(scan_y);
								tuple.resize(n_of_y);
								for (std::size_t scan_x = 0; scan_x < n_of_y; ++scan_x) {
									const auto &elm_y = GET_MATRIX_DATA(p_ey, scan_y, scan_x);
									const auto &elm_x = GET_MATRIX_DATA(p_ex, scan_y, scan_x);
									tuple.at(scan_x) = add(elm_y, elm_x);
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
						p_etemp = GEN_MATRIX(mat);
					}
					else {
						throw InvalidValue("BAD_MSIZ", __FUNCTION__);
					}
					break;
				}
				default:
					//==  MATRIX + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SUBTRACT
// [ description ]
// SUBTRACT function for tuple, matrix or complex
// [ Update ]
// Feb 01, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::subSet(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::ETUPLE:
			//===  ETUPLE - ???  ===//
			switch (x_type) {
				case Element::ETUPLE: {
				//==  ETUPLE - ETUPLE  ==//
				const std::size_t size_y = GET_ETUPLE_SIZE(p_ey);
				const std::size_t size_x = GET_ETUPLE_SIZE(p_ex);
				if (size_y == size_x) {
					std::vector<SpElement> tuple;
					tuple.resize(size_y);
					setExceptions(FLT_OVERFLOW);
					try {
						for (std::size_t ucnt = 0; ucnt < size_y; ++ucnt) {
							const auto &elm_y = GET_ETUPLE_DATA(p_ey, ucnt);
							const auto &elm_x = GET_ETUPLE_DATA(p_ex, ucnt);
							tuple.at(ucnt) = sub(elm_y, elm_x);
						}
					}
					catch (FlagException &) {
						setExceptions(FLT_OVERFLOW);
						throw InvalidValue("TOO_LRGE", __FUNCTION__);
					}
					catch (...) {
						setExceptions(FLT_OVERFLOW);
						throw;
					}
					setExceptions(FLT_OVERFLOW);
					p_etemp = GEN_ETUPLE(tuple);
				}
				else {
					throw InvalidValue("BAD_TSIZ", __FUNCTION__);
				}
				break;
			}
			default:
				//==  ETUPLE - Unexpected  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::MATRIX:
			//===  MATRIX - ???  ===//
			switch (x_type) {
				case Element::MATRIX: {
					//==  MATRIX - MATRIX  ==//
					const std::size_t m_of_y = GET_MATRIX_SIZE_M(p_ey);
					const std::size_t n_of_y = GET_MATRIX_SIZE_N(p_ey);
					const std::size_t m_of_x = GET_MATRIX_SIZE_M(p_ex);
					const std::size_t n_of_x = GET_MATRIX_SIZE_N(p_ex);
					if ((m_of_y == m_of_x) && (n_of_y == n_of_x)) {
						std::vector<std::vector<SpElement>> mat;
						mat.resize(m_of_y);
						setExceptions(FLT_OVERFLOW);
						try {
							for (std::size_t scan_y = 0; scan_y < m_of_y; ++scan_y) {
								auto &tuple = mat.at(scan_y);
								tuple.resize(n_of_y);
								for (std::size_t scan_x = 0; scan_x < n_of_y; ++scan_x) {
									const auto &lhs = GET_MATRIX_DATA(p_ey, scan_y, scan_x);
									const auto &rhs = GET_MATRIX_DATA(p_ex, scan_y, scan_x);
									tuple.at(scan_x) = sub(lhs, rhs);
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
						p_etemp = GEN_MATRIX(mat);
					}
					else {
						throw InvalidValue("BAD_MSIZ", __FUNCTION__);
					}
					break;
				}
				default:
					//==  MATRIX - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MULTIPLY (set)
// [ description ]
// MULTIPLY function for tuple, matrix or complex
// [ Update ]
// May 18, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mulSet(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
	case Element::ETUPLE:
		//===  ETUPLE * ???  ===//
		switch (x_type) {
			case Element::ETUPLE: {
				//=  ETUPLE * ETUPLE  =//
				std::size_t size_ty = GET_ETUPLE_SIZE(p_ey);
				std::size_t size_tx = GET_ETUPLE_SIZE(p_ex);
				auto dir_y = GET_ETUPLE_TYPE(p_ey);
				auto dir_x = GET_ETUPLE_TYPE(p_ex);
				switch (dir_y) {
					case ETuple::TupleType::COLUMN:
						//=  ETUPLE(col) * ETUPLE  =//
						switch (dir_x) {
							case ETuple::TupleType::COLUMN:
								//=  ETUPLE(col) * ETUPLE(col)  =//
								throw BadArgument("BAD_TYPE", __FUNCTION__);
							case ETuple::TupleType::ROW: {
								//=  ETUPLE(col) * ETUPLE(row)  =//
								std::vector<std::vector<SpElement>> mat;
								mat.resize(size_ty);
								for (std::size_t pos_y = 0; pos_y < size_ty; ++pos_y) {
									auto elm_y = GET_ETUPLE_DATA(p_ey, pos_y);
									auto &vec = mat.at(pos_y);
									for (std::size_t pos_x = 0; pos_x < size_tx; ++pos_x) {
										auto elm_x = GET_ETUPLE_DATA(p_ex, pos_x);
										vec.push_back(mul(elm_y, elm_x));
									}
								}
								p_etemp = GEN_MATRIX(mat);
								break;
							}
							default:
								throw TechnicalError("Unexpected tuple type", __FUNCTION__);
						}
						break;
					case ETuple::TupleType::ROW:
						//=  ETUPLE(row) * ETUPLE  =//
						switch (dir_x) {
							case ETuple::TupleType::COLUMN: {
								//=  ETUPLE(row) * ETUPLE(col)  =//
								return innerProduct(p_ey, p_ex);
								break;
							}
							case ETuple::TupleType::ROW:
								//=  ETUPLE(row) * ETUPLE(row)  =//
								throw BadArgument("BAD_TYPE", __FUNCTION__);
							default:
								throw TechnicalError("Unexpected tuple type", __FUNCTION__);
						}
					default:
						throw TechnicalError("Unexpected tuple type", __FUNCTION__);
				}
				break;
			}
			case Element::MATRIX: {
				//==  ETUPLE * MATRIX  ==//
				std::size_t tuple_size = GET_ETUPLE_SIZE(p_ey);
				std::size_t size_xm = GET_MATRIX_SIZE_M(p_ex);
				std::size_t size_xn = GET_MATRIX_SIZE_N(p_ex);
				switch (GET_ETUPLE_TYPE(p_ey)) {
					case ETuple::TupleType::COLUMN: {
						//=  ETUPLE(col) * MATRIX  =//
						if (1 == size_xm) {
							std::vector<std::vector<SpElement>> mat;
							mat.resize(tuple_size);
							setExceptions(FLT_OVERFLOW);
							try {
								for (std::size_t scan_y = 0; scan_y < tuple_size; ++scan_y) {
									auto &vec = mat.at(scan_y);
									vec.resize(size_xn);
									for (std::size_t ucnt = 0; ucnt < size_xn; ++ucnt) {
										const auto &elm_y = GET_ETUPLE_DATA(p_ey, scan_y);
										const auto &elm_x = GET_MATRIX_DATA(p_ex, 0, ucnt);
										vec.at(ucnt) = mul(elm_y, elm_x);
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
							p_etemp = GEN_MATRIX(mat);
						}
						else {
							throw BadArgument("BAD_MSIZ", __FUNCTION__);
						}
						break;
					}
					case ETuple::TupleType::ROW: {
						//=  ETUPLE(row) * MATRIX  =//
						if (tuple_size == size_xm) {
							std::vector<SpElement> vec;
							vec.resize(size_xn);
							setExceptions(FLT_OVERFLOW);
							try {
								for (std::size_t scan_x = 0; scan_x < size_xn; ++scan_x) {
									const auto &yf = GET_ETUPLE_DATA(p_ey, 0);
									const auto &xf = GET_MATRIX_DATA(p_ex, 0, scan_x);
									SpElement elm = mul(yf, xf);
									for (std::size_t ucnt = 1; ucnt < tuple_size; ++ucnt) {
										const auto &elm_y = GET_ETUPLE_DATA(p_ey, ucnt);
										const auto &elm_x = GET_MATRIX_DATA(p_ex, ucnt, scan_x);
										elm = add(elm, mul(elm_y, elm_x));
										vec.at(scan_x) = elm;
									}
								}
								p_etemp = GEN_ETUPLE2(vec, ETuple::TupleType::ROW);
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
							throw BadArgument("BAD_MSIZ", __FUNCTION__);
						}
						break;
					}
					default:
						throw TechnicalError("Unexpected tuple type", __FUNCTION__);
				}
				break;
			}
			default: {
				//==  ETUPLE * ANY  ==//
				std::size_t size = GET_ETUPLE_SIZE(p_ey);
				auto ttype = GET_ETUPLE_TYPE(p_ey);
				std::vector<SpElement> tuple;
				tuple.resize(size);
				setExceptions(FLT_OVERFLOW);
				try {
					for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
						const auto &elm_y = GET_ETUPLE_DATA(p_ey, ucnt);
						tuple.at(ucnt) = mul(elm_y, p_ex);
					}
					p_etemp = GEN_ETUPLE2(tuple, ttype);
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
			} // end of default
		} // end of etuple * ???
		break;
	case Element::MATRIX:
		//===  MATRIX * ???  ===//
		switch (x_type) {
			case Element::ETUPLE: {
				//==  MATRIX * ETUPLE  ==//
				std::size_t size_ym = GET_MATRIX_SIZE_M(p_ey);
				std::size_t size_yn = GET_MATRIX_SIZE_N(p_ey);
				std::size_t tuple_size = GET_ETUPLE_SIZE(p_ex);
				switch (GET_ETUPLE_TYPE(p_ex)) {
					case ETuple::TupleType::COLUMN: {
						//=  Matrix * Col-Tuple  =//
						if (tuple_size == size_yn) {
							std::vector<SpElement> vec;
							vec.resize(size_ym);
							setExceptions(FLT_OVERFLOW);
							try {
								for (std::size_t scan_y = 0; scan_y < size_ym; ++scan_y) {
									const auto &yf = GET_MATRIX_DATA(p_ey, scan_y, 0);
									const auto &xf = GET_ETUPLE_DATA(p_ex, 0);
									SpElement elm = mul(yf, xf);
									for (std::size_t ucnt = 1; ucnt < size_yn; ++ucnt) {
										const auto &elm_y = GET_MATRIX_DATA(p_ey, scan_y, ucnt);
										const auto &elm_x = GET_ETUPLE_DATA(p_ex, ucnt);
										elm = add(elm, mul(elm_y, elm_x));
									}
									vec.at(scan_y) = elm;
								}
								p_etemp = GEN_ETUPLE2(vec, ETuple::TupleType::COLUMN);
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
							throw BadArgument("BAD_MSIZ", __FUNCTION__);
						}
						break;
					}
					case ETuple::TupleType::ROW: {
						//=  Matrix * Row-Tuple  =//
						if (1 == size_yn) {
							std::vector<std::vector<SpElement>> mat;
							mat.resize(size_ym);
							setExceptions(FLT_OVERFLOW);
							try {
								for (std::size_t scan_y = 0; scan_y < size_ym; ++scan_y) {
									auto &vec = mat.at(scan_y);
									vec.resize(tuple_size);
									for (std::size_t ucnt = 0; ucnt < tuple_size; ++ucnt) {
										const auto &elm_y = GET_MATRIX_DATA(p_ey, scan_y, 0);
										const auto &elm_x = GET_ETUPLE_DATA(p_ex, ucnt);
										vec.at(ucnt) = mul(elm_y, elm_x);
									}
								}
								p_etemp = GEN_MATRIX(mat);
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
							throw BadArgument("BAD_MSIZ", __FUNCTION__);
						}
						break;
					}
					default:
						throw TechnicalError("Unexpected tuple type", __FUNCTION__);
				}
				break;
			}
			case Element::MATRIX: {
				//==  MATRIX * MATRIX  ==//
				std::size_t size_ym = GET_MATRIX_SIZE_M(p_ey);
				std::size_t size_yn = GET_MATRIX_SIZE_N(p_ey);
				std::size_t size_xm = GET_MATRIX_SIZE_M(p_ex);
				std::size_t size_xn = GET_MATRIX_SIZE_N(p_ex);
				if (size_yn == size_xm) {
					std::vector<std::vector<SpElement>> mat;
					mat.resize(size_ym);
					setExceptions(FLT_OVERFLOW);
					try {
						for (std::size_t scan_y = 0; scan_y < size_ym; ++scan_y) {
							auto &vec = mat.at(scan_y);
							vec.resize(size_xn);
							for (std::size_t scan_x = 0; scan_x < size_xn; ++scan_x) {
								const auto &yf = GET_MATRIX_DATA(p_ey, scan_y, 0);
								const auto &xf = GET_MATRIX_DATA(p_ex, 0, scan_x);
								SpElement elm = mul(yf, xf);
								for (std::size_t ucnt = 1; ucnt < size_yn; ++ucnt) {
									const auto &elm_y = GET_MATRIX_DATA(p_ey, scan_y, ucnt);
									const auto &elm_x = GET_MATRIX_DATA(p_ex, ucnt, scan_x);
									elm = add(elm, mul(elm_y, elm_x));
								}
								vec.at(scan_x) = elm;
							}
						}
						p_etemp = GEN_MATRIX(mat);
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
					throw BadArgument("BAD_MSIZ", __FUNCTION__);
				}
				break;
			}
			default: {
				//==  MATRIX * ANY  ==//
				std::size_t size_m = GET_MATRIX_SIZE_M(p_ey);
				std::size_t size_n = GET_MATRIX_SIZE_N(p_ey);
				std::vector<std::vector<SpElement>> mat(size_m);
				setExceptions(FLT_OVERFLOW);
				try {
					for (std::size_t scan_y = 0; scan_y < size_m; ++scan_y) {
						auto &dest_vec = mat.at(scan_y);
						dest_vec.resize(size_n);
						for (std::size_t scan_x = 0; scan_x < size_n; ++scan_x) {
							const auto &lhs = GET_MATRIX_DATA(p_ey, scan_y, scan_x);
							const auto &rhs = p_ex;
							auto &dst = dest_vec.at(scan_x);
							dst = mul(lhs, rhs);
						}
					}
					p_etemp = GEN_MATRIX(mat);
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
			} // end of default
		} // end of matrix * ???
		break;
	default:
		//===  ANY * ???  ===//
		switch (x_type) {
			case Element::ETUPLE: {
				//==  ANY * ETUPLE  ==//
				std::size_t size = GET_ETUPLE_SIZE(p_ex);
				auto ttype = GET_ETUPLE_TYPE(p_ex);
				std::vector<SpElement> tuple;
				tuple.resize(size);
				setExceptions(FLT_OVERFLOW);
				try {
					for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
						const auto &elm_x = GET_ETUPLE_DATA(p_ex, ucnt);
						tuple.at(ucnt) = mul(p_ey, elm_x);
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
				p_etemp = GEN_ETUPLE2(tuple, ttype);
				break;
			}
			case Element::MATRIX: {
				//==  ANY * MATRIX  ==//
				std::size_t size_m = GET_MATRIX_SIZE_M(p_ex);
				std::size_t size_n = GET_MATRIX_SIZE_N(p_ex);
				std::vector<std::vector<SpElement>> mat;
				mat.resize(size_m);
				setExceptions(FLT_OVERFLOW);
				try {
					for (std::size_t scan_y = 0; scan_y < size_m; ++scan_y) {
						auto &vec = mat.at(scan_y);
						vec.resize(size_n);
						for (std::size_t scan_x = 0; scan_x < size_n; ++scan_x) {
							const auto &elm_y = p_ey;
							const auto &elm_x = GET_MATRIX_DATA(p_ex, scan_y, scan_x);
							vec.at(scan_x) = mul(elm_y, elm_x);
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
				p_etemp = GEN_MATRIX(mat);
				break;
			}
			default:
				//==  Unexpected  ==//
				throw BadArgument("BAD_TYPE", __FUNCTION__);
		}
		break;
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DIVIDE
// [ description ]
// DIVIDE function for tuple, matrix or complex
// [ Update ]
// May 02, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::divSet(const SpElement &p_ey, const SpElement &p_ex) {
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	switch (y_type) {
		case Element::ETUPLE: {
			//===  ETUPLE / ANY  ===//
			std::size_t size = GET_ETUPLE_SIZE(p_ey);
			auto ttype = GET_ETUPLE_TYPE(p_ey);
			std::vector<SpElement> tuple;
			tuple.resize(size);
			setExceptions(FLT_OVERFLOW);
			try {
				for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
					const auto &elm_y = GET_ETUPLE_DATA(p_ey, ucnt);
					tuple.at(ucnt) = div(elm_y, p_ex);
				}
				p_etemp = GEN_ETUPLE2(tuple, ttype);
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
		case Element::MATRIX: {
			//===  MATRIX / ANY  ===//
			std::size_t size_m = GET_MATRIX_SIZE_M(p_ey);
			std::size_t size_n = GET_MATRIX_SIZE_N(p_ey);
			std::vector<std::vector<SpElement>> mat;
			mat.resize(size_m);
			setExceptions(FLT_OVERFLOW);
			try {
				for (std::size_t scan_y = 0; scan_y < size_m; ++scan_y) {
					auto &vec = mat.at(scan_y);
					vec.resize(size_n);
					for (std::size_t scan_x = 0; scan_x < size_n; ++scan_x) {
						const auto &elm_y = GET_MATRIX_DATA(p_ey, scan_y, scan_x);
						const auto &elm_x = p_ex;
						vec.at(scan_x) = div(elm_y, elm_x);
					}
				}
				p_etemp = GEN_MATRIX(mat);
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
			//===  Unexpected  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
