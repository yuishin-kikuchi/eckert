#ifndef _OPERATORS_ENGINEERING_H_
#define _OPERATORS_ENGINEERING_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"
#include <limits>

namespace engine {

class RadixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RDX");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			stack.push(GEN_INTEGER(std::numeric_limits<floating_t>::radix));
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class EpsilonOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_EPS");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			stack.push(GEN_FLOATING(std::numeric_limits<floating_t>::epsilon()));
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class TpixOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_TPIX");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.mul(p_ex, proc.mul(proc.pi(), GEN_INTEGER(2)));
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

class DtpiOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DTPI");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.div(p_ex, proc.mul(proc.pi(), GEN_INTEGER(2)));
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

class ParallelOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PARA");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isKindOf(Element::NUMERIC_TYPE) && p_ex->isKindOf(Element::NUMERIC_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.inv(proc.add(proc.inv(p_ey), proc.inv(p_ex)));
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

class TodbOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_TODB");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isKindOf(Element::NUMERIC_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.mul(GEN_INTEGER(10), proc.log10(proc.abs(p_ex)));
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
			return 1;
		}
};

class DbtoOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DBTO");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isKindOf(Element::SCALAR_TYPE)) {
					SpElement p_etemp;
					try {
						p_etemp = proc.pow10(proc.div(p_ex, GEN_INTEGER(10)));
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
			return 1;
		}
};

} // namespace engine

#endif // _OPERATORS_ENGINEERING_H_
