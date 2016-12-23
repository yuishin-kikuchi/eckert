#ifndef _OPERATORS_MATRIX_H_
#define _OPERATORS_MATRIX_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class MakeMatrixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MMAT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::INTEGER)) {
					integer_t mat_size = GET_INTEGER_DATA(p_ex);
					if (mat_size > 0) {
						std::size_t items = stack.size();
						std::size_t usize = (std::size_t)mat_size;
						if (usize < items) {
							bool all_tuple = true;
							bool all_same_size = true;
							const auto first = stack.fetch(usize);
							std::size_t tuple_size = 0;
							ETuple::TupleType ttype = ETuple::TupleType::ROW;
							if (!first->isType(engine::Element::ETUPLE)) {
								stackEngine.setErrorMessage("BAD_ELM");
								return true;
							}
							tuple_size = GET_ETUPLE_SIZE(first);
							ttype = GET_ETUPLE_TYPE(first);
							for (std::size_t ucnt = 0; ucnt < usize; ++ucnt) {
								const auto elm = stack.fetch(usize - ucnt);
								if (elm->isType(engine::Element::ETUPLE)) {
									if ((GET_ETUPLE_SIZE(elm) != tuple_size) ||
										(GET_ETUPLE_TYPE(elm) != ttype)) {
										all_same_size = false;
										break;
									}
								}
								else {
									all_tuple = false;
									break;
								}
							}
							if (all_tuple) {
								if (all_same_size) {
									std::vector<std::vector<SpElement>> mat;
									switch (ttype) {
										case ETuple::TupleType::ROW: {
											/**  Make matrix with row tuple  **/
											for (std::size_t ucnt = 0; ucnt < usize; ++ucnt) {
												const auto &elm = stack.fetch(usize - ucnt);
												mat.push_back(CAST_INTO_ETUPLE(elm)->getVector());
											}
											break;
										} // End of ROW
										case ETuple::TupleType::COLUMN: {
											/**  Make matrix with column tuple  **/
											mat.resize(tuple_size);
											for (std::size_t scan_y = 0; scan_y < tuple_size; ++scan_y) {
												auto &vec = mat.at(scan_y);
												vec.resize(usize);
											}
											for (std::size_t scan_x = 0; scan_x < usize; ++scan_x) {
												const auto &elm = stack.fetch(usize - scan_x);
												for (std::size_t scan_y = 0; scan_y < tuple_size; ++scan_y) {
													mat.at(scan_y).at(scan_x) = GET_ETUPLE_DATA(elm, scan_y);
												}
											}
											break;
										} // End of COLUMN
										default:
											stackEngine.setErrorMessage("BAD_TYPE");
											return true;
									} // End of switch
									stack.drop(usize + 1);
									stack.push(GEN_MATRIX(mat));
								}
								else {
									stackEngine.setErrorMessage("BAD_TSIZ");
									return true;
								}
							}
							else {
								stackEngine.setErrorMessage("BAD_ELM");
								return true;
							}
						}
						else {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class MakeUnitMatrixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_UMAT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::INTEGER)) {
					integer_t mat_size = GET_INTEGER_DATA(p_ex);
					if (mat_size > 0) {
						std::size_t usize = (std::size_t)mat_size;
						std::vector<std::vector<SpElement>> mat;
						mat.resize(usize);
						for (std::size_t scan_y = 0; scan_y < usize; ++scan_y) {
							auto &vec = mat.at(scan_y);
							vec.resize(usize);
							for (std::size_t scan_x = 0; scan_x < usize; ++scan_x) {
								if (scan_y == scan_x) {
									vec.at(scan_x) = GEN_INTEGER(1);
								}
								else {
									vec.at(scan_x) = GEN_INTEGER(0);
								}
							}
						}
						stack.drop(1);
						stack.push(GEN_MATRIX(mat));
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class GetElementFromMatrixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MGET");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ez = stack.fetch(2);
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ez->isType(Element::MATRIX) && p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
					integer_t size_m = GET_MATRIX_SIZE_M(p_ez);
					integer_t size_n = GET_MATRIX_SIZE_N(p_ez);
					integer_t pos_i = GET_INTEGER_DATA(p_ey);
					integer_t pos_j = GET_INTEGER_DATA(p_ex);
					if ((0 < pos_i) && (pos_i <= size_m) && (0 < pos_j) && (pos_j <= size_n)) {
						SpElement elm = GET_MATRIX_DATA(p_ez, (std::size_t)pos_i - 1, (std::size_t)pos_j - 1);
						stack.drop(3);
						stack.push(elm);
					}
					else {
						stackEngine.setErrorMessage("BAD_RNG");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 3;
		}
};

class GetRowFromMatrixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MGETR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isType(Element::MATRIX) && p_ex->isType(Element::INTEGER)) {
					integer_t size_m = GET_MATRIX_SIZE_M(p_ey);
					integer_t size_n = GET_MATRIX_SIZE_N(p_ey);
					integer_t pos_i = GET_INTEGER_DATA(p_ex);
					if ((0 < pos_i) && (pos_i <= size_m)) {
						std::vector<engine::SpElement> tuple;
						for (integer_t cnt = 0; cnt < size_n; ++cnt) {
							SpElement elm = GET_MATRIX_DATA(p_ey, (std::size_t)pos_i - 1, (std::size_t)cnt);
							tuple.push_back(elm);
						}
						stack.drop(2);
						stack.push(GEN_ETUPLE2(tuple, ETuple::TupleType::ROW));
					}
					else {
						stackEngine.setErrorMessage("BAD_RNG");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class GetColumnFromMatrixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MGETC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isType(Element::MATRIX) && p_ex->isType(Element::INTEGER)) {
					integer_t size_m = GET_MATRIX_SIZE_M(p_ey);
					integer_t size_n = GET_MATRIX_SIZE_N(p_ey);
					integer_t pos_j = GET_INTEGER_DATA(p_ex);
					if ((0 < pos_j) && (pos_j <= size_n)) {
						std::vector<engine::SpElement> tuple;
						for (integer_t cnt = 0; cnt < size_m; ++cnt) {
							SpElement elm = GET_MATRIX_DATA(p_ey, (std::size_t)cnt, (std::size_t)pos_j - 1);
							tuple.push_back(elm);
						}
						stack.drop(2);
						stack.push(GEN_ETUPLE2(tuple, ETuple::TupleType::COLUMN));
					}
					else {
						stackEngine.setErrorMessage("BAD_RNG");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class TransposeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_TRP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.transpose(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class HermitianTransposeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_HTRP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.hermitianTranspose(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class DeterminantOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DET");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.determinant(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class TraceOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_TRC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.trace(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

} // namespace engine

#endif // _OPERATORS_TUPLE_H_
