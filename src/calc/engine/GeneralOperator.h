#ifndef _GENERAL_OPERATOR_H_
#define _GENERAL_OPERATOR_H_

#include <string>
#include "proc/base/core/StackCalculator.h"
#include "proc/GeneralProcessor.h"

////==--------------------------------------------------------------------====//
// GENERAL OPERATOR
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class GeneralOperator : public StackOperator {
	private:
		static GeneralProcessor _proc;
	public:
		virtual bool operate(StackEngine &stackEngine) const = 0;
		virtual std::size_t getRequiredCount() const = 0;
		static GeneralProcessor& getGeneralProcessor() {
			return _proc;
		}
		static void checkFlags(StackEngine &stackEngine) {
			if (_proc.checkFlags(engine::GeneralProcessor::ERROR_FLAG)) {
				stackEngine.setErrorMessage("ERR_CALC");
			}
			else if (_proc.checkFlags(engine::GeneralProcessor::FLT_OVERFLOW)) {
				stackEngine.setErrorMessage("FLT_OF");
			}
			else if (_proc.checkFlags(engine::GeneralProcessor::RAT_OVERFLOW)) {
				stackEngine.setErrorMessage("RAT_OF");
			}
			else if (_proc.checkFlags(engine::GeneralProcessor::INT_OVERFLOW)) {
				stackEngine.setErrorMessage("INT_OF");
			}
			else {
				stackEngine.setErrorMessage("NO_ERROR");
			}
		}
		bool hasEnoughItems(StackEngine &stackEngine) const;
		static bool getSizetValue(std::size_t &num, const SpElement &elem);
};

} // namespace engine

#endif // ifndef _GENERAL_OPERATOR_H_
