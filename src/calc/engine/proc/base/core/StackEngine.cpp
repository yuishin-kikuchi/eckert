#include "StackEngine.h"
#include "StackOperator.h"

namespace engine {

bool StackEngine::acceptOperator(const StackOperatorPtr &op) {
	if (nullptr != op) {
		return op->operate(*this);
	}
	else {
		return true;
	}
};

bool StackEngine::acceptOperator(const StackOperator *op) {
	if (nullptr != op) {
		return op->operate(*this);
	}
	else {
		return true;
	}
};

} // namespace engine
