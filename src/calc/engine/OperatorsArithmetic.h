#ifndef _OPERATORS_ARITHMETIC_H_
#define _OPERATORS_ARITHMETIC_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class AddOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ADD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.add(p_ey, p_ex);
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

class SubOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SUB");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(p_ey, p_ex);
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

class MulOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MUL");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.mul(p_ey, p_ex);
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

class DivOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DIV");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.div(p_ey, p_ex);
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

class ModOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MOD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.mod(p_ey, p_ex);
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

class QremOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_QREM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_quot;
				SpElement p_rem;
				try {
					p_quot = proc.quot(p_ey, p_ex);
					p_rem = proc.mod(p_ey, p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(2);
				stack.push(p_quot);
				stack.push(p_rem);
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
