#include "StackOperator.h"
#include "StackEngine.h"

namespace engine {

bool StackOperator::operate(StackEngine &stackEngine) const {
	stackEngine.setCommandMessage("FATAL_ERROR");
	stackEngine.setErrorMessage("FATAL_ERROR");
	stackEngine.setAdditionalMessage("FATAL_ERROR");
	return true;
}

} // namespace engine

