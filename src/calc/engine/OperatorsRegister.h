#ifndef _OPERATORS_REGISTER_H_
#define _OPERATORS_REGISTER_H_

#include "GeneralOperator.h"

namespace engine {

class RegisterOperator : public GeneralOperator {
	private:
		std::size_t _pos;
		SpElement _elm;
	public:
		virtual bool operate(StackEngine &stackEngine) const = 0;
		virtual std::size_t getRequiredCount() const = 0;
		void setPos(const std::size_t &pos) {
			_pos = pos;
		}
		void setElement(const SpElement &elm) {
			_elm = elm;
		}
		std::size_t getPos() const {
			return _pos;
		}
		SpElement getElement() const {
			return _elm;
		}
};

class RegStoreOperator : public RegisterOperator {
	public:
		explicit RegStoreOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_STO");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto &reg = stackEngine.refRegister();
				SpElement p_ex = stack.fetch(0);
				reg.at(getPos()) = p_ex;
				stack.drop(1);
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

class RegLoadOperator : public RegisterOperator {
	public:
		explicit RegLoadOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_LD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto &reg = stackEngine.refRegister();
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					stack.push(elm);
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class RegDelOperator : public RegisterOperator {
	public:
		explicit RegDelOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_DEL");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &reg = stackEngine.refRegister();
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = SpElement(nullptr);
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class RegIncOperator : public RegisterOperator {
	public:
		explicit RegIncOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_INC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &reg = stackEngine.refRegister();
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = proc.inc(elm);
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class RegDecOperator : public RegisterOperator {
	public:
		explicit RegDecOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_DEC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &reg = stackEngine.refRegister();
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = proc.dec(elm);
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class RegAddOperator : public RegisterOperator {
	public:
		explicit RegAddOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_ADD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto &reg = stackEngine.refRegister();
				SpElement p_ex = stack.fetch(0);
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = proc.add(elm, p_ex);
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

class RegSubOperator : public RegisterOperator {
	public:
		explicit RegSubOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_SUB");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto &reg = stackEngine.refRegister();
				SpElement p_ex = stack.fetch(0);
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = proc.sub(elm, p_ex);
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

class RegMulOperator : public RegisterOperator {
	public:
		explicit RegMulOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_MUL");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto &reg = stackEngine.refRegister();
				SpElement p_ex = stack.fetch(0);
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = proc.mul(elm, p_ex);
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

class RegDivOperator : public RegisterOperator {
	public:
		explicit RegDivOperator(const std::size_t &pos) {
			setPos(pos);
		}
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("R_DIV");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				auto &reg = stackEngine.refRegister();
				SpElement p_ex = stack.fetch(0);
				SpElement elm = reg.at(getPos());
				if (nullptr == elm) {
					stackEngine.setErrorMessage("REG_ND");
					return true;
				}
				else {
					reg.at(getPos()) = proc.div(elm, p_ex);
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

#endif // ifndef _OPERATORS_REGISTER_H_
