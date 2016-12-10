#ifndef _STACK_OPERATOR_H_
#define _STACK_OPERATOR_H_

#include <vector>
#include <string>
#include "BaseElement.h"
#include "stack/ExStack.h"

////==--------------------------------------------------------------------====//
// STACK ENGINE
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////

namespace engine {
	class StackEngine;
	class StackOperator {
		public:
			StackOperator() {}
			StackOperator(const StackOperator &obj) {}
			virtual ~StackOperator() = default;
			virtual bool operate(StackEngine &stackEngine) const;
	};
} // namespace engine

#endif // ifndef _STACK_OPERATOR_H_
