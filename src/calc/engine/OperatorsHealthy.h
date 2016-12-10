#ifndef _OPERATORS_HEALTHY_H_
#define _OPERATORS_HEALTHY_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class DiscomfortIndexOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DCM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					auto temp1 = proc.mul(GEN_FLOATING(0.81L), p_ey);
					auto temp2 = proc.sub(proc.mul(GEN_FLOATING(0.99L), p_ey), GEN_FLOATING(14.3L));
					temp2 = proc.mul(proc.mul(GEN_FLOATING(0.01L), p_ex), temp2);
					p_etemp = proc.add(temp1, temp2);
					p_etemp = proc.add(p_etemp, GEN_FLOATING(46.3L));
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

class BmiOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_BMI");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					auto temp = proc.mul(p_ey, GEN_FLOATING(0.01L));
					p_etemp = proc.div(p_ex, proc.square(temp));
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

} // namespace engine

#endif // _OPERATORS_HEALTHY_H_
