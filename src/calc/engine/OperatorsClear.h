#ifndef _OPERATORS_CLEAR_H_
#define _OPERATORS_CLEAR_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class AllClearOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_AC");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			auto &reg = stackEngine.refRegister();
			bool registerEmpty = true;
			for (auto &&x : reg) {
				if (nullptr != x) {
					registerEmpty = false;
				}
			}
			if ((0 != stack.size()) || (!registerEmpty)) {
				stack.clear();
				for (auto &&x : reg) {
					x = SpElement(nullptr);
				}
				return false;
			}
			else {
				stackEngine.setErrorMessage("SR_EMPTY");
				return true;
			}
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class StackClearOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SC");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			if (0 != stack.size()) {
				stack.clear();
				return false;
			}
			else {
				stackEngine.setErrorMessage("S_EMPTY");
				return true;
			}
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class RegisterClearOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RC");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &reg = stackEngine.refRegister();
			bool registerEmpty = true;
			for (auto &&x : reg) {
				if (nullptr != x) {
					registerEmpty = false;
				}
			}
			if (!registerEmpty) {
				for (auto &&x : reg) {
					x = SpElement(nullptr);
				}
				return false;
			}
			else {
				stackEngine.setErrorMessage("R_EMPTY");
				return true;
			}
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

} // namespace engine

#endif // _OPERATORS_CLEAR_H_
