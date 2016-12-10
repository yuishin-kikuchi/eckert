#ifndef _OPERATORS_FUNDAMENTAL_H_
#define _OPERATORS_FUNDAMENTAL_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class NegateOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_NEG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.neg(p_ex);
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

class InvertOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_INV");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.inv(p_ex);
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

class AbsoluteOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ABS");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.abs(p_ex);
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

class FloorOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_FLR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.floor(p_ex);
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

class CeilingOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CEIL");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.ceil(p_ex);
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

class RoundOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ROND");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.round(p_ex);
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

class SquareOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SQ");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.square(p_ex);
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

class SquareRootOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SQRT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sqrt(p_ex);
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

class CubicRootOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CBRT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.cbrt(p_ex);
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

class HypotOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_HYPT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.hypot(p_ey, p_ex);
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

class RatioOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RAT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement num;
				SpElement den;
				try {
					auto r = GET_RATIONAL_DATA(p_ex);
					num = GEN_INTEGER(r.getNum());
					den = GEN_INTEGER(r.getDen());
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(num);
				stack.push(den);
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

class PercentOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PERC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isKindOf(Element::SCALAR_TYPE) && p_ex->isKindOf(Element::SCALAR_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.mul(p_ey, proc.div(p_ex, GEN_INTEGER(100)));
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

class DeltaPercentOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DPRC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isKindOf(Element::SCALAR_TYPE) && p_ex->isKindOf(Element::SCALAR_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.div(proc.sub(p_ex, p_ey), p_ey);
						p_etemp = proc.mul(p_etemp, GEN_INTEGER(100));
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

class IncludeTaxOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_INTAX");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isKindOf(Element::SCALAR_TYPE) && p_ex->isKindOf(Element::SCALAR_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.div(proc.add(GEN_INTEGER(100), p_ex), GEN_INTEGER(100));
						p_etemp = proc.mul(p_etemp, p_ey);
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

class ExcludeTaxOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_EXTAX");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isKindOf(Element::SCALAR_TYPE) && p_ex->isKindOf(Element::SCALAR_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.div(GEN_INTEGER(100), proc.add(GEN_INTEGER(100), p_ex));
						p_etemp = proc.mul(p_etemp, p_ey);
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

} // namespace engine

#endif // _OPERATORS_ARITHMETIC_H_
