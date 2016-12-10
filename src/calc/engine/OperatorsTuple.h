#ifndef _OPERATORS_TUPLE_H_
#define _OPERATORS_TUPLE_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class MakeRowTupleOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MRT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::INTEGER)) {
					integer_t tuple_size = GET_INTEGER_DATA(p_ex);
					if (tuple_size > 0) {
						std::size_t usize = (std::size_t)tuple_size;
						std::vector<SpElement> tuple;
						bool all_numeric = true;
						for (std::size_t ucnt = 0; ucnt < usize; ++ucnt) {
							const auto elm = stack.fetch(usize - ucnt);
							if (elm->isKindOf(Element::NUMERIC_TYPE | Element::BINARY_TYPE)) {
								tuple.push_back(elm);
							}
							else {
								all_numeric = false;
								break;
							}
						}
						if (all_numeric) {
							stack.drop(usize + 1);
							stack.push(GEN_ETUPLE2(tuple, ETuple::TupleType::ROW));
						}
						else {
							stackEngine.setErrorMessage("BAD_ELM");
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

class MakeColumnTupleOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MCT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::INTEGER)) {
					integer_t tuple_size = GET_INTEGER_DATA(p_ex);
					if (tuple_size > 0) {
						std::size_t usize = (std::size_t)tuple_size;
						std::vector<SpElement> tuple;
						bool all_numeric = true;
						for (std::size_t ucnt = 0; ucnt < usize; ++ucnt) {
							const auto elm = stack.fetch(usize - ucnt);
							if (elm->isKindOf(Element::NUMERIC_TYPE | Element::BINARY_TYPE)) {
								tuple.push_back(elm);
							}
							else {
								all_numeric = false;
								break;
							}
						}
						if (all_numeric) {
							stack.drop(usize + 1);
							stack.push(GEN_ETUPLE2(tuple, ETuple::TupleType::COLUMN));
						}
						else {
							stackEngine.setErrorMessage("BAD_ELM");
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

class MakeRowUnitTupleOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MRUT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
					integer_t tuple_size = GET_INTEGER_DATA(p_ey);
					integer_t position = GET_INTEGER_DATA(p_ex);
					if (0 < tuple_size) {
						std::size_t usize = (std::size_t)tuple_size;
						if ((0 < position) && (position <= tuple_size)) {
							std::size_t upos = (std::size_t)position;
							std::vector<SpElement> tuple;
							tuple.resize(usize);
							for (std::size_t ucnt = 0; ucnt < usize; ++ucnt) {
								if (upos == ucnt + 1) {
									tuple.at(ucnt) = GEN_INTEGER(1);
								}
								else {
									tuple.at(ucnt) = GEN_INTEGER(0);
								}
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

class MakeColumnUnitTupleOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MCUT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isType(Element::INTEGER) && p_ex->isType(Element::INTEGER)) {
					integer_t tuple_size = GET_INTEGER_DATA(p_ey);
					integer_t position = GET_INTEGER_DATA(p_ex);
					if (0 < tuple_size) {
						std::size_t usize = (std::size_t)tuple_size;
						if ((0 < position) && (position <= tuple_size)) {
							std::size_t upos = (std::size_t)position;
							std::vector<engine::SpElement> tuple;
							tuple.resize(usize);
							for (std::size_t ucnt = 0; ucnt < usize; ++ucnt) {
								if (upos == ucnt + 1) {
									tuple.at(ucnt) = GEN_INTEGER(1);
								}
								else {
									tuple.at(ucnt) = GEN_INTEGER(0);
								}
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


class InnerProductOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_IPRD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.innerProduct(p_ey, p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(2);
				stack.push(p_etemp);
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

class OuterProductOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_OPRD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.outerProduct(p_ey, p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(2);
				stack.push(p_etemp);
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

class EuclidNormOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_NORM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.norm(p_ex);
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

class EuclidNormSqOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_NSQ");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.normSq(p_ex);
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

class LpNormOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_LPN");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.lpNorm(p_ey, p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(2);
				stack.push(p_etemp);
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

class MaxNormOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MAXN");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.maxNorm(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(2);
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

class CraveOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CRAV");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto p_ex = stack.fetch(0);
				switch (p_ex->getType()) {
					case Element::MATRIX: {
						std::size_t size_m = GET_MATRIX_SIZE_M(p_ex);
						stack.drop(1);
						for (std::size_t scan_y = 0; scan_y < size_m; ++scan_y) {
							const auto &vec = CAST_INTO_MATRIX(p_ex)->getVector(scan_y);
							stack.push(GEN_ETUPLE(vec));
						}
						break;
					}
					case Element::ETUPLE: {
						const auto &tup = GET_ETUPLE_RAW(p_ex);
						std::size_t tuple_size = tup.size();
						stack.drop(1);
						for (std::size_t ucnt = 0; ucnt < tuple_size; ++ucnt) {
							const auto &elm = tup.at(ucnt);
							stack.push(elm);
						}
						break;
					}
					default:
						stackEngine.setErrorMessage("BAD_TYPE");
						return false;
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

} // namespace engine

#endif // _OPERATORS_TUPLE_H_
