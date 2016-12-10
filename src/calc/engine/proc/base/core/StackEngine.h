#ifndef _STACK_ENGINE_H_
#define _STACK_ENGINE_H_

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
	class StackOperator;
	using StackOperatorPtr = std::shared_ptr<StackOperator>;
	class StackEngine {
		private:
			ExStack<SpElement> _exSpElementStack;
			std::vector<SpElement> _registerVector;
			std::string _commandMessage;
			std::string _errorMessage;
			std::string _additionalMessage;
		public:
			//==  Referers  ==//
			ExStack<SpElement>& refExStack() {
				return _exSpElementStack;
			}
			std::vector<SpElement>& refStack() {
				return _exSpElementStack.refer();
			}
			std::vector<SpElement>& refRegister() {
				return _registerVector;
			}
			//==  Referers (const)  ==//
			const ExStack<SpElement>& refExStack() const {
				return _exSpElementStack;
			}
			const std::vector<SpElement>& refStack() const {
				return _exSpElementStack.refer();
			}
			const std::vector<SpElement>& refRegister() const {
				return _registerVector;
			}
			//==  Getter  ==//
			std::string getCommandMessage() const {
				return _commandMessage;
			}
			std::string getErrorMessage() const {
				return _errorMessage;
			}
			std::string getAdditionalMessage() const {
				return _additionalMessage;
			}
			//==  Setter  ==//
			void setCommandMessage(const std::string &msg) {
				_commandMessage = msg;
			}
			void setErrorMessage(const std::string &msg) {
				_errorMessage = msg;
			}
			void setAdditionalMessage(const std::string &msg) {
				_additionalMessage = msg;
			}
			//==  Accepter  ==//
			bool acceptOperator(const StackOperatorPtr &op);
			bool acceptOperator(const StackOperator *op);
	};
} // namespace engine

#endif // ifndef _STACK_ENGINE_H_
