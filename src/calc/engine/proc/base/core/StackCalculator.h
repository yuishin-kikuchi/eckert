#ifndef _STACK_CALCULATOR_H_
#define _STACK_CALCULATOR_H_

#include "StackEngine.h"
#include "StackOperator.h"
#include <map>
#include <string>

////==--------------------------------------------------------------------====//
// STACK CALCULATOR
// [ Update ]
// May 19, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class StackCalculator {
	protected:
		StackEngine _stackEngine;
		std::map<std::string, StackOperatorPtr> _operators;
	public:
		StackEngine& refStackEngine() {
			return _stackEngine;
		}
		const StackEngine& refStackEngine() const {
			return _stackEngine;
		}
		StackOperatorPtr getOperator(const std::string &str) const {
			return _operators.at(str);
		}
		std::map<std::string, StackOperatorPtr> &refOperators() {
			return _operators;
		}
		const std::map<std::string, StackOperatorPtr> &refOperators() const {
			return _operators;
		}
		void addOperator(const std::string &str, const StackOperatorPtr &op) {
			_operators.insert(std::map<std::string, StackOperatorPtr>::value_type(str, op));
		}
		void resetOperators() {
			_operators.clear();
		}
		virtual bool operate(const std::string &str) = 0;
		bool doesCommandExist(const std::string &str) {
			return (_operators.find(str) != _operators.end());
		}
};

} // namespace engine

#endif // ifndef _STACK_CALCULATOR_H_
