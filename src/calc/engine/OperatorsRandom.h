#ifndef _OPERATORS_RANDOM_H_
#define _OPERATORS_RANDOM_H_

#include "GeneralOperator.h"
#include <random>

namespace engine {

class RandomOperator : public GeneralOperator {
	protected:
		static std::mt19937_64 mt;
	public:
		virtual bool operate(StackEngine &stackEngine) const = 0;
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
		static void init() {
			std::random_device rd;
			mt.seed(rd());
		}
		static void seed(const uint64_t &val) {
			mt.seed(val);
		}
};

class RandomIntegerOperator : public RandomOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RAND");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			uinteger_t temp = mt() >> 1;
			stack.push(GEN_INTEGER((integer_t)temp));
			return false;
		}
};

class RandomFloatingOperator : public RandomOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_FRND");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			std::uniform_real_distribution<floating_t> distribution(0.0, 1.0);
			stack.push(GEN_FLOATING(distribution(mt)));
			return false;
		}
};

} // namespace engine

#endif // ifndef _OPERATORS_RANDOM_H_
